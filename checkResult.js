document.addEventListener("DOMContentLoaded", function () {
    const form = document.querySelector("form");
    form.addEventListener("submit", function (event) {
        event.preventDefault(); // Prevent the form from submitting the default way

        const userID = document.getElementById("userID").value; // Get the user input
        const baseUrl =
            "https://michael-aladejobi.github.io/HealthVitalsPro/profile.html"; // actual base URL // TOP LEVEL
        const fullUrl = `${baseUrl}?id=${encodeURIComponent(userID)}`; // Appended the userID to the URL

        if (userID === "") {
            alert("Please, Enter an ID!");
        } else {
            window.open(fullUrl, "_self"); // Open the new URL in a new tab
        }
    });
});
