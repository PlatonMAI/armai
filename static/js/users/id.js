window.onload = async (e) => {

let url = new URL(window.location.href);
let id = url.searchParams.get("id");
console.log("users_id: определенный id: " + id);

console.log("users_id: обращаюсь к серверу...");
let response = await fetch(`http://localhost:8001/users/${id}`);

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
