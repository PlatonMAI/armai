window.onload = async (e) => {

let url = new URL(window.location.href);
let id = url.searchParams.get("id");
console.log("teams_id: определенный id: " + id);

console.log("teams_id: обращаюсь к серверу...");
let response = await fetch(`http://localhost:8001/teams/${id}`);

if (response.status != 200) {
    alert("Что-то пошло не так!");
    console.log(response.status);
    throw new Error();
}

let json = await response.json();
console.log(json);

document.querySelector("#name").innerText = json["name"];
document.querySelector("#winsArmfights").innerText = json["winsArmfights"];
document.querySelector("#winsCompetition").innerText = json["winsCompetitions"];

let participantElem = document.querySelector(".participant");
let listElem = document.querySelector("ul");

if (json["participants"] === null) {
    document.querySelector("#title-participants").innerText = "Пока еще никто не выступал за эту команду!";

    return;
}

for (let participant of json["participants"]) {
    let participantNewElem = participantElem.cloneNode(true);
    participantNewElem.classList.remove("inactive");

    let aElem = participantNewElem.querySelector("a");
    aElem.href = `/users_/id.html?id=${participant["id"]}`;
    aElem.innerText = participant["name"];

    listElem.append(participantNewElem);
}

}
