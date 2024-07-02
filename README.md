<!-- index.html Page -->

# HealthVitals Login Page

This document provides an overview and detailed explanation of the HTML code for the HealthVitals login page.

## Table of Contents

-   [Introduction](#introduction)
-   [External Resources](#external-resources)
-   [HTML Structure](#html-structure)
-   [Background Shapes](#background-shapes)
-   [Navigation Bar](#navigation-bar)
-   [Login Form](#login-form)
-   [JavaScript Integration](#javascript-integration)

## Introduction

The HealthVitals login page is designed to provide users with a seamless experience for logging in to the HealthVitals platform. This page includes external resources, background shapes for visual design, a navigation bar, and a login form.

## External Resources

The following external resources are used in the HTML code:

-   **Fonts and Icons:**

    -   Font Awesome for icons: `https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.4/css/all.min.css`
    -   Google Fonts for the Poppins font: `https://fonts.googleapis.com/css2?family=Poppins:wght@300;500;600&display=swap`

-   **Custom Stylesheet:**
    -   A custom stylesheet named `style.css` is used for additional styling.

## HTML Structure

The HTML document is structured as follows:

-   **DOCTYPE Declaration:**
    ```html
    <!DOCTYPE html>
    ```

This declares the document type and version (HTML5).

-   <html lang="en">
    This is the root element of the document, indicating the language as English.

Head Section:

<head>
<title>HEALTHVITALS ? | LOGIN</title>
<link rel="preconnect" href="https://fonts.gstatic.com" />
<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.4/css/all.min.css" />
<link href="https://fonts.googleapis.com/css2?family=Poppins:wght@300;500;600&display=swap" rel="stylesheet" />
<link rel="stylesheet" href="style.css" />
</head>

Body Section:

<body>
<!-- Content goes here -->
</body>

Background Shapes
The background shapes are included for visual design purposes:

<div class="background">
<div class="shape"></div>
</div>
The div elements with the class shape are used to create decorative shapes in the background.

Navigation Bar
The navigation bar includes the logo and placeholder links:

<div class="main-nav">
<a href="#">
<div class="logo">
<img src="assets/images/logo.png" alt="logo" class="logo-img" />
HealthVitals
</div>
</a>
<div class="nav"><a href="#"></a></div>
<div class="nav"><a href="#"></a></div>
<div class="nav"><a href="#"></a></div>
<a href="#"><div class="nav"></div></a>
</div>
This navigation bar is used all across the webpages.

The logo is wrapped in an anchor tag that links to the homepage.
Placeholder div elements with the class nav are used for future navigation links.

Login Form
The login form allows users to enter their email and password:

<form class="login-form">
<h3 class="sign-in-up">
<span style="color: rgb(31, 30, 30); font-weight: bold">L</span>ogin |
<a href="signup.html">Sign Up</a>
</h3>

    <label for="email">Email</label>
    <input type="text" placeholder="Enter email address e.g test@gmail.com" id="email-el" required />

    <label for="password">Password</label>
    <input type="password" placeholder="Enter your Password" id="password-el" required />

    <div class="forget-password">
        <a href="#" id="forget-password"> Forget Password? </a>
    </div>

    <button id="submit-btn">Submit</button>
    </form>

The form includes:
A heading for the login section with a link to the signup page.
Input fields for email and password, both marked as required.
A "Forget Password?" link.
A submit button.

JavaScript Integration
The HTML code includes a script tag for JavaScript functionality:

<script src="index.js" type="module" defer></script>

Conclusion
This HTML code provides a structured and styled login page for the HealthVitals platform, integrating external resources, background shapes, a navigation bar, and a login form to create a user-friendly interface.

<!-- Sign Up.html -->

# VitalCare Signup Page

This document provides an overview and detailed explanation of the HTML code for the VitalCare signup page.

## Table of Contents

-   [Introduction](#introduction)
-   [External Resources](#external-resources)
-   [HTML Structure](#html-structure)
-   [Background Shapes](#background-shapes)
-   [Navigation Bar](#navigation-bar)
-   [Signup Form](#signup-form)
-   [JavaScript Integration](#javascript-integration)

## Introduction

The VitalCare signup page is designed to provide users with a seamless experience for registering on the VitalCare platform. This page includes external resources, background shapes for visual design, a navigation bar, and a signup form.

## External Resources

The following external resources are used in the HTML code:

-   **Fonts and Icons:**

    -   Font Awesome for icons: `https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.4/css/all.min.css`
    -   Google Fonts for the Poppins font: `https://fonts.googleapis.com/css2?family=Poppins:wght@300;500;600&display=swap`

-   **Custom Stylesheet:**
    -   A custom stylesheet named `style.css` is used for additional styling.

## HTML Structure

The HTML document is structured as follows:

-   **DOCTYPE Declaration:**

    ```html
    <!DOCTYPE html>

    <!-- Reusable Components here - Navbar & shapes -->
    ```

Signup Form
The signup form allows users to enter their email and password:

<form class="login-form">
<h3 class="sign-in-up">Register</h3>

        <label for="email">Email</label>
        <input type="text" placeholder="Enter email address e.g admin@gmail.com" id="email-el" required />

        <label for="password">Password</label>
        <input type="password" placeholder="Enter a strong Password" id="password-el" required />

        <button id="create-account-el">Create Account</button>
    </form>

The form includes:
A heading for the signup section.
Input fields for email and password, both marked as required.

JavaScript Integration
The HTML code includes a script tag for JavaScript functionality:

<script src="signup.js" type="module" defer></script>

The JavaScript file signup.js is loaded as a module and deferred to ensure it is executed after the HTML content is fully parsed.

The JavaScript file signup.js is loaded as a module and deferred to ensure it is executed after the HTML content is fully parsed.

<!-- Dashboard.html -->

# HealthVitals Dashboard.html - Home Page

This HTML document represents the home page for HealthVitals, a healthcare management system.

## Table of Contents

-   [Introduction](#introduction)
-   [HTML Structure](#html-structure)
-   [Navigation Bar](#navigation-bar)
-   [Main Content](#main-content)
-   [JavaScript Link](#javascript-link)

## Introduction

This page serves as the main interface for HealthVitals, providing navigation and access to various features of the healthcare management system.

## HTML Structure

<!-- Check `dashboard.html file` for source code -->

Navigation Bar
The navigation bar (main-nav) includes links to the dashboard, home page, and sign-out functionality. The logo (logo-img) links back to the dashboard.

Main Content
Logged-in User Information: Displayed under registration-section1, indicating the currently logged-in user (Admin in this case).
Quick Links: Located in section1, offering shortcuts to add a new patient (add_New_Patient.html) and view patients (patients.html).

JavaScript Link
A JavaScript file (dashboard.js) is linked at the end of the body for additional functionality, presumably handling dynamic content or user interactions.
This structure provides a clear layout for users navigating HealthVitals, enhancing usability and accessibility.

<!-- patients.html -->

# HealthVitals Patient List Page

Introduction
This HTML document represents the Patient List page of HealthVitals, a healthcare management system. It displays a list of registered patients along with their information in a structured table format.

### Description

Navigation Bar
The navigation bar (main-nav) includes:

Logo: Links back to the dashboard (dashboard.html).
Back to Home: Links to dashboard.html for returning to the main dashboard.

Patient List Table
Heading: Displays "Registered Patient List" (<h2>).
Table: Displays patient information including:
Patient ID
Name
Email
Address
Gender
Phone
Date Registered

# CSS Styling

Table Styling: Custom styles applied to enhance readability and visual appeal of the patient list table.

# JavaScript

Script: Linked JavaScript file patients.js is responsible for fetching and dynamically injecting patient data into the table (<tbody id="patient-data">).
This documentation provides an overview of the structure and functionality of the Patient List page in HealthVitals, aiding in understanding and maintaining the system.

<!-- addNewPatientForm.html -->

# HealthVitals Registration Page

Introduction
This HTML document represents the Registration page of HealthVitals, a healthcare management system. It allows users to add new patient information into the system through a form.

HTML Structure

<!-- Get Source Code `addNewPatientForm.html` in folder -->

Description
Navigation Bar
The navigation bar (main-nav) includes:

Logo: Links back to the dashboard (dashboard.html).
Back to Home: Links to dashboard.html for returning to the main dashboard.

# Registration Form

Section: Displays "Add New patient".
Form: Allows users to enter patient information including:
Image upload
First Name
Last Name
Email Address
Address
Gender
Age
Phone number
Date Registered

# Firebase Integration

Firebase SDK: Imports Firebase modules (firebase-app.js, firebase-firestore.js, firebase-storage.js) for database and storage operations.

# JavaScript

Script: Linked JavaScript file addNewPatientForm.js handles form submission and integration with Firebase Firestore and Storage for storing patient data and images.

# VitalCare Firebase Authentication Script

<!-- LOGIN AUTHENTICATION -->

This document provides an overview and detailed explanation of the Firebase authentication JavaScript code used in the VitalCare project.

## Table of Contents

-   [Introduction](#introduction)
-   [Firebase Setup](#firebase-setup)
-   [Event Listeners](#event-listeners)
-   [Password Reset](#password-reset)
-   [Error Handling](#error-handling)
-   [Conclusion](#conclusion)

## Introduction

The VitalCare project uses Firebase for authentication purposes. This script initializes Firebase, handles user login, and manages password reset functionality.

## Firebase Setup

1. **Import Firebase SDKs**: The required functions are imported from the Firebase SDK.

    ```javascript
    import { initializeApp } from "https://www.gstatic.com/firebasejs/9.8.1/firebase-app.js";
    import {
        getAuth,
        sendPasswordResetEmail,
        signInWithEmailAndPassword,
    } from "https://www.gstatic.com/firebasejs/9.8.1/firebase-auth.js";
    ```

2. **Firebase Configuration**: The Firebase configuration object contains the necessary credentials to connect to the Firebase project.

    ```javascript
    const firebaseConfig = {
        apiKey: "AIzaSyBAgeUvIPwMirPSPywX9YZJZ79htSpKO5c",
        authDomain: "wrud-5b418.firebaseapp.com",
        databaseURL: "https://wrud-5b418-default-rtdb.firebaseio.com",
        projectId: "wrud-5b418",
        storageBucket: "wrud-5b418.appspot.com",
        messagingSenderId: "867302937144",
        appId: "1:867302937144:web:152fa283505a65facd4ccd",
    };
    ```

3. **Initialize Firebase**: Firebase is initialized with the configuration object.
    ```javascript
    const app = initializeApp(firebaseConfig);
    const auth = getAuth(app);
    ```

## Event Listeners

1. **Login Event Listener**: An event listener is attached to the login button to handle user login.

    ```javascript
    document
        .getElementById("submit-btn")
        .addEventListener("click", function (event) {
            event.preventDefault(); // Prevent default form submission
            alert("Checking Details...\nPlease Wait!"); // Alert user about the login process

            // Get User inputs
            const email = document.getElementById("email-el").value;
            const password = document.getElementById("password-el").value;

            if (email === "test@gmail.com" && password === "test@gmail.com") {
                signInWithEmailAndPassword(auth, email, password).then(
                    (userCredential) => {
                        alert("Login Successful!");
                        window.location.href = "dashboard.html";
                    }
                );
            } else {
                signInWithEmailAndPassword(auth, email, password)
                    .then((userCredential) => {
                        alert("Login Successful!");
                        window.location.href = "checkResult.html";
                    })
                    .catch((error) => {
                        alert(error.message);
                    });
            }
        });
    ```

## Password Reset

1. **Forget Password Event Listener**: An event listener is attached to the forget password link to handle password reset functionality.

    ```javascript
    const reset = document.getElementById("forget-password");
    reset.addEventListener("click", function (event) {
        event.preventDefault(); // Prevent default link behavior
        const email = document.getElementById("email-el").value; // Get user email

        sendPasswordResetEmail(auth, email)
            .then(() => {
                alert("Email Sent! Check your inbox."); // Alert user about the email sent
            })
            .catch((error) => {
                alert(error.message); // Alert user about the error
            });
    });
    ```

## Error Handling

1. **General Error Handling**: Errors are caught and displayed as alerts to the user.
    ```javascript
    signInWithEmailAndPassword(auth, email, password).catch((error) => {
        const errorCode = error.code;
        const errorMessage = error.message;
        alert(errorMessage);
    });
    ```

## Conclusion

This script provides the necessary functionality for user authentication in the Health project using Firebase. It initializes Firebase, handles user login, and manages password reset functionality with appropriate error handling. Same procedure applies to "signin.html" file.

You can follow each source code in the folder as they are well documented with brief explanations within the code to describe what specific parts are doing.
