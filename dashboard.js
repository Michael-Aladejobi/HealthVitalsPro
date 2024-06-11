import { initializeApp } from "https://www.gstatic.com/firebasejs/9.8.1/firebase-app.js";
import {
    getAuth,
    onAuthStateChanged,
    signOut,
} from "https://www.gstatic.com/firebasejs/9.8.1/firebase-auth.js";

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
const app = initializeApp(firebaseConfig);
const auth = getAuth(app); // Get the Auth instance
const user = auth.currentUser; // Get the current user

console.log(user); // Log the current user to the console
onAuthStateChanged(auth, (user) => {
    if (user) {
        // If user is signed in
        updateUserProfile(user); // Update user profile
        const uid = user.uid; // Get user ID
        return uid; // Return user ID

        // ...
    } else {
        // User is signed out, redirect  to the reggistration page
        // ...
        alert("Create Account & Login!"); // Display alert message
        window.location.href = "signup.html"; // Redirect to signup page
    }
});

// Function to update user profile
function updateUserProfile(user) {
    const userEmail = user.email; // Get user email

    // document.getElementById(
    //     "logged-in-as"
    // ).innerHTML = ` LoggedIn as: <br><small> ${userEmail} </small>`; // Update logged-in user display
}
