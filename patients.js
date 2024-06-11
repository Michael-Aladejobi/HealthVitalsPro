// Import Firebase modules
import { initializeApp } from "https://www.gstatic.com/firebasejs/9.10.0/firebase-app.js";
import {
    getFirestore,
    collection,
    getDocs,
} from "https://www.gstatic.com/firebasejs/9.10.0/firebase-firestore.js";

// Your web app's Firebase configuration
const firebaseConfig = {
    apiKey: "AIzaSyBAgeUvIPwMirPSPywX9YZJZ79htSpKO5c",
    authDomain: "wrud-5b418.firebaseapp.com",
    databaseURL: "https://wrud-5b418-default-rtdb.firebaseio.com",
    projectId: "wrud-5b418",
    storageBucket: "wrud-5b418.appspot.com",
    messagingSenderId: "867302937144",
    appId: "1:867302937144:web:152fa283505a65facd4ccd",
};

// Initialize Firebase
const app = initializeApp(firebaseConfig); // Initialize Firebase app
const db = getFirestore(app); // Get Firestore database instance

// Function to fetch and display patient data
const displayPatients = async () => {
    const patientData = document.getElementById("patient-data"); // Get reference to the patient data container

    try {
        // Query the "patients" collection
        const querySnapshot = await getDocs(collection(db, "patients"));
        // Loop through each document in the collection
        querySnapshot.forEach((doc) => {
            const patient = doc.data(); // Get patient data
            const row = document.createElement("tr"); // Create a table row element
            // Populate the row with patient data
            row.innerHTML = `
                <td><a href="profile.html?id=${doc.id}">${doc.id}</a></td>
                <td>${patient.firstName} ${patient.lastName}</td>
                <td>${patient.email}</td>
                <td>${patient.address}</td>
                <td>${patient.gender}</td>
                <td>${patient.phoneNo}</td>
                <td>${patient.date}</td>
            `;
            patientData.appendChild(row); // Append the row to the patient data container
        });
    } catch (e) {
        console.error("Error fetching patient data: ", e); // Log any errors that occur during data fetching
    }
};

// Invoke the display function to fetch and display patient data
displayPatients();
