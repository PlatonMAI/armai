window.onload = async (e) => {

console.log("me: обращаюсь к серверу...");
let response = await fetch("http://localhost:8001/users/me");

if (response.status != 200) {
    alert("Что-то пошло не так!");
    console.log(response.status);
    throw new Error();
}

let json = await response.json();

document.querySelector("#name").innerText = json["name"];
document.querySelector("#sex").innerText = json["sex"];
document.querySelector("#birth").innerText = json["birth"];
document.querySelector("#winsArmfights").innerText = json["winsArmfights"];
document.querySelector("#winsCompetitions").innerText = json["winsCompetitions"];

}
