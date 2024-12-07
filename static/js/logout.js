console.log("logout: обращаюсь к серверу...");
let response = await fetch("http://localhost:8001/users/logout");

if (response.status == 200) {
    document.location.href = "/reg.html";
} else {
    console.log("logout: " + response.status);
}
