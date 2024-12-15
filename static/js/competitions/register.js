window.onload = async (e) => {

let url = new URL(window.location.href);
let competitionId = url.searchParams.get("id");

let response = await fetch(`http://localhost:8001/teams`);
let responseJson = await response.json();
let teams = responseJson["teams"];

let selectElem = document.querySelector("#team");
for (let team of teams) {
    let optionNewElem = document.createElement("option");
    optionNewElem.value = team["id"];
    optionNewElem.innerText = team["name"];
    selectElem.append(optionNewElem);
}

let formElem = document.querySelector("#form-reg");
formElem.addEventListener("submit", async function (event) {
    event.preventDefault();

    let teamId = selectElem.value;
    if (teamId == "")
        teamId = null;
    else
        teamId = Number(teamId);

    let response = await fetch(`http://localhost:8001/competitions/${competitionId}/register`, {
        method: 'POST',
        body: JSON.stringify({"teamId": teamId})
    });

    if (response.status == 200) {
        document.location.href = `/competitions_/id.html?id=${competitionId}`;
    } else {
        alert("Что-то пошло не так!");
        console.log(response.status);
        console.log(response.statusText);
        throw new Error();
    }
});

}
