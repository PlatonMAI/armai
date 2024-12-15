window.onload = async (e) => {

console.log("teams: обращаюсь к серверу...");
let response = await fetch(`http://localhost:8001/teams`);

if (response.status != 200) {
    alert("Что-то пошло не так!");
    console.log(response.status);
    throw new Error();
}

let json = await response.json();
console.log(json);

let teamElem = document.querySelector(".team");
let listElem = document.querySelector("ul");

for (let team of json["teams"]) {
    let teamNewElem = teamElem.cloneNode(true);
    teamNewElem.classList.remove("inactive");

    let id = team["id"];
    let name = team["name"];
    let aElem = teamNewElem.querySelector("a");
    aElem.href = `/teams_/id.html?id=${id}`;
    aElem.innerText = name;

    listElem.append(teamNewElem);
}

}
