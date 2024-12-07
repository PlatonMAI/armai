console.log("redirectAuth: обращаюсь к серверу...");
let response = await fetch("http://localhost:8001/users/me");

if (response.status == 200) {
    document.location.href = "/index.html";
} else {
    console.log("redirectAuth: " + response.status);
}
