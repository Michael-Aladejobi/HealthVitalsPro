#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <WebServer.h>
#include "time.h"
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include "MAX30100_PulseOximeter.h"
#include <LiquidCrystal_I2C.h>


// Calibration constants from the linear regression
const float slope = 38.30;
const float intercept = 0.00;

// Define the pin for the analog input
const int analogPin = 34; // GPIO pin connected to the voltage output


// Insert your network credentials
#define WIFI_SSID "Ettronics"
#define WIFI_PASSWORD "00000000"

// Insert Firebase project API Key
#define API_KEY "AIzaSyBAgeUvIPwMirPSPywX9YZJZ79htSpKO5c"

// Insert Authorized Email and Corresponding Password
#define USER_EMAIL "test@gmail.com"
#define USER_PASSWORD "test@gmail.com"

// Insert RTDB URL
#define DATABASE_URL "https://wrud-5b418-default-rtdb.firebaseio.com/"

// Define HC-SR04 sensor pins
const int trigPin = 5;
const int echoPin = 18;

// Define button pins
const int heightButtonPin = 19;
const int temperatureButtonPin = 4;
const int uploadResultPin = 15;
const int pulseButtonPin = 13;
const int weightButtonPin = 27;

// Debounce variables
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;  // 50 milliseconds debounce delay

// Create a temperature sensor object
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

// Define Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Variable to save USER UID
String uid;

// Variable to save the distance between U-sensor and the footstool
const float HEIGHT_STAND = 215.50;

// Offset variable to calibrate temperature sensor
const float TEMPERATURE_OFFSET_VALUE = 4;

// Database main path (to be updated in setup with the user UID)
String databasePath;
// Database child nodes
String heightPath = "height";
String tempPath = "temperature";
String pulsePath = "pulse";
String spo2Path = "spo2";
String timePath = "timestamp";
String weightPath = "weight";

// Parent Node (to be updated in every loop)
String parentPath;

unsigned long timestamp;
FirebaseJson json;

// Pulse oximeter variables
#define REPORTING_PERIOD_MS 1000
PulseOximeter pox;
uint32_t tsLastReport = 0;

void onBeatDetected() {
    Serial.println("Beat!");
}

// Timer variables (send new readings every three minutes) 
// Override by Reset Button
//unsigned long sendDataPrevMillis = 0;
//unsigned long timerDelay = 180000; // 3 minutes

WebServer server(80);
String customUserID;

// Variables to store sensor measurements
float heightMeasurement = 0.0;
float temperatureMeasurement = 0.0;
float pulseMeasurement = 0.0;
float spo2Measurement = 0.0;
float weightMeasurement = 0.0;

// Track Current Epoch Time
unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return 0;
  }
  time(&now);
  return now + 3600; // 3600 seconds (1 hour) to my epoch time
}

// Function to get local time as a string, GMT+0
String getFormattedTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return "Failed to obtain time";
  }

  // Add one hour to the obtained time
  timeinfo.tm_hour += 1;

  // Handle cases where hour exceeds 23 by adjusting the day
  if (timeinfo.tm_hour >= 24) {
    timeinfo.tm_hour -= 24;
    timeinfo.tm_mday += 1; // Increment the day
  }

  char timeString[30];
  strftime(timeString, sizeof(timeString), "%d-%m-%Y %H:%M:%S", &timeinfo);
  return String(timeString);
}

// Function to get height from HC-SR04 sensor
float getHeight() {
  // Send a 10us pulse to trigger the sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the echo time in microseconds
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in cm
  float distance = duration * 0.034 / 2.0;
  
  return distance;
}

// Function to get temperature from MLX90614 sensor
float getTemperature() {
  return mlx.readObjectTempC(); // You can choose to use readAmbientTempC() if needed
}

// Initialize WiFi
void initWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println();
  Serial.print("Connected to WiFi with IP: ");
  Serial.println(WiFi.localIP());
}

// CREATE WEBSERVER HOST --init--
void handleRoot() {
  server.send(200, "text/html", R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
      <title>Enter User ID</title>
      <style>
        body {
          padding-left: 20px;
        }
        
        #userID {
            display: block;
            height: 50px;
            width: 50%;
            background-color: rgba(255,255,255,0.07);
            border-radius: 3px;
            padding: 0 10px;
            margin-top: 8px;
            font-size: 14px;
            font-weight: 300;
        }

        ::placeholder{
            color: #e5e5e5;
        }

        .button{
            margin-top: 10px;
            width: 50%;
            background-color: #0f7a73;
            border: 1px solid #0f7a73;
            color: #fff;
            padding: 10px 0;
            font-size: 18px;
            font-weight: 600;
            border-radius: 10px;
            cursor: pointer;
            transition: .3s;
        }
        .button:hover {
            padding: 15px 0;
            transition: .3s;
        }
        
      </style>
    </head>
    <body>
      <h1>Enter User ID to Initialize</h1>
      <form action="/submit" method="POST">
        <input type="text" id="userID" name="userID"><br>
        <input class="button" type="submit" value="Submit">
      </form>
    </body>
    </html>
  )rawliteral");
}

// Handle Submit request/response
void handleSubmit() {
  if (server.hasArg("userID")) {
    customUserID = server.arg("userID");
    customUserID.trim(); // Remove any leading or trailing whitespace
    server.send(200, "text/plain", "User ID received!");
    
    // Immediately update Firebase with the new user ID
    updateFirebaseData();
  } else {
    server.send(400, "text/plain", "User ID not provided");
  }
}

void updateFirebaseData() {
  if (Firebase.ready()) {
    // Get current timestamp
    timestamp = getTime();
    Serial.print("time: ");
    Serial.println(timestamp);

    // Get formatted local time
    String formattedTime = getFormattedTime();
    Serial.print("Formatted time: ");
    Serial.println(formattedTime);
    
    if (customUserID.length() > 0) {
      parentPath = "/UsersData/" + customUserID + "/readings/" + String(timestamp);

      json.set(heightPath, String(heightMeasurement));
      json.set(tempPath, String(temperatureMeasurement));
      json.set(pulsePath, String(pulseMeasurement));
      json.set(spo2Path, String(spo2Measurement));
      json.set(weightPath, String(weightMeasurement));

      json.set(timePath, formattedTime);
      Serial.printf("Set json... %s\n", Firebase.RTDB.setJSON(&fbdo, parentPath.c_str(), &json) ? "ok" : fbdo.errorReason().c_str());
     
    } else {
      Serial.println("Enter Patient ID on Webpage.");
    }
  }
}

LiquidCrystal_I2C lcd(0x27, 16, 2); //LCD code 


void setup() {
  
  Serial.begin(115200);


  lcd.init();                    //LCD code 
  lcd.backlight();               //LCD code   

  lcd.setCursor(0,0);            //LCD code 
  lcd.print("Initializing...");         //LCD code 

  // Initialize HC-SR04 sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize buttons
  pinMode(heightButtonPin, INPUT_PULLUP);
  pinMode(temperatureButtonPin, INPUT_PULLUP);
  pinMode(uploadResultPin, INPUT_PULLUP);
  pinMode(pulseButtonPin, INPUT_PULLUP);
  pinMode(weightButtonPin, INPUT_PULLUP);


  // Initialize temperature sensor
  mlx.begin();

  initWiFi();
  configTime(0, 0, "pool.ntp.org");

  // Assign the api key (required)
  config.api_key = API_KEY;

  // Assign the user sign in credentials
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  // Assign the RTDB URL (required)
  config.database_url = DATABASE_URL;

  Firebase.reconnectWiFi(true);
  fbdo.setResponseSize(4096);

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  // Web server
  server.on("/", handleRoot);
  server.on("/submit", HTTP_POST, handleSubmit);
  server.begin();

  // Initialize the pulse sensor
  if (!pox.begin()) {
    Serial.println("FAILED TO INITIALIZE PULSE OXIMETER");
    for (;;);
  } else {
    Serial.println("Pulse oximeter initialized");
    lcd.setCursor(0,0); 
     lcd.print("                ");

    lcd.setCursor(0,0);            //LCD code 
  lcd.print("Test Result:");         //LCD code 
  }
  pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop() {
  server.handleClient();  
  
  // Update pulse oximeter readings
  pox.update();
  
  // Read height measurement on button press with debounce
  if (digitalRead(heightButtonPin) == LOW) {
    delay(50); // Debounce delay
    if (digitalRead(heightButtonPin) == LOW) {
      heightMeasurement = HEIGHT_STAND - getHeight();
      lcd.setCursor(0, 1);
      lcd.print("                ");
       lcd.setCursor(0, 1);
    lcd.print("Height: " + String(heightMeasurement) + "cm"); 
      Serial.print("Height: ");
      Serial.print(heightMeasurement);
      Serial.println("cm");
        delay(500);
    }
  }

  // Read temperature measurement on button press with debounce
  if (digitalRead(temperatureButtonPin) == LOW) {
    delay(50); // Debounce delay
    if (digitalRead(temperatureButtonPin) == LOW) {
      temperatureMeasurement = getTemperature() + TEMPERATURE_OFFSET_VALUE;
      lcd.setCursor(0, 1);
      lcd.print("                ");
           lcd.setCursor(0, 1);
           lcd.print("Temp: " + String(temperatureMeasurement) + " *c");
      Serial.print("Temperature: ");
      Serial.print(temperatureMeasurement);
      Serial.println(" *C");
        delay(500);
    }
  }
  
  // Read pulse and oxygen measurement on button press with debounce
  if (digitalRead(pulseButtonPin) == LOW) {
    delay(50); // Debounce delay
    if (digitalRead(pulseButtonPin) == LOW) {
      pulseMeasurement = pox.getHeartRate();
      spo2Measurement = pox.getSpO2();
      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print("Pulse: " + String(pulseMeasurement) + " BPM");
      Serial.print("Pulse: ");
      Serial.print(pulseMeasurement);
      Serial.print(" BPM");
      Serial.print(", SpO2: ");
      Serial.print(spo2Measurement);
      Serial.println(" %");
      
    }
      
  }


if (digitalRead(weightButtonPin) == LOW) {
    delay(50); // Debounce delay
    if (digitalRead(weightButtonPin) == LOW) {
      
       
       // Read the analog input (voltage)
  int adcValue = analogRead(analogPin);
  
  // Convert the ADC value to voltage (assuming a 12-bit ADC with 3.3V reference)
  float voltage = adcValue * (3.3 / 4095.0);
  
  float weightMeasurement = (voltage * slope) + intercept;
  lcd.setCursor(0, 1);
      lcd.print("                ");
       lcd.setCursor(0, 1);
    lcd.print("Weight: " + String(weightMeasurement) + " kg"); 
      Serial.print("Weight: ");
      Serial.print(weightMeasurement);
      Serial.println(" kg");
        delay(500);
    }
}


  
  // Upload result on button press with debounce
  if (digitalRead(uploadResultPin) == LOW)
  {
    delay(50); // Debounce delay
    if (digitalRead(uploadResultPin) == LOW) 
    {
      updateFirebaseData();
        delay(500);
        lcd.setCursor(0, 1);
      lcd.print("                ");
         lcd.setCursor(0, 1);
      lcd.print("Data Uploaded");
    }
  }
  
}
