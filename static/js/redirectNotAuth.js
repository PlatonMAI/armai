console.log("redirectNotAuth: обращаюсь к серверу...");
let response = await fetch("http://localhost:8001/users/me");

if (response.status == 401) {
    document.location.href = "/reg.html";
} else {
    console.log("redirectNotAuth: " + response.status);
}
