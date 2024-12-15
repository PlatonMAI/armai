window.onload = async (e) => {

let competitionElem = document.querySelector(".competition");
let listElem = document.querySelector("ul");

function clearUl() {
    listElem.replaceChildren();
}

function fillUl(competitions) {
    for (let competition of competitions) {
        let competitionNewElem = competitionElem.cloneNode(true);
        competitionNewElem.classList.remove("inactive");

        let id = competition["id"];
        let name = competition["name"];
        let aElem = competitionNewElem.querySelector("a");
        aElem.href = `/competitions_/id.html?id=${id}`;
        aElem.innerText = name;

        listElem.append(competitionNewElem);
    }
}

async function getCompetitions(url) {
    console.log("competitions: обращаюсь к серверу...");
    let response = await fetch(url);

    if (response.status != 200) {
        alert("Что-то пошло не так!");
        console.log(response.status);
        throw new Error();
    }

    let json = await response.json();
    console.log(json);

    if (json["competitions"] === null) {
        listElem.innerText = "Ничего не найдено!";
        return;
    }
    
    fillUl(json["competitions"]);
}

await getCompetitions("http://localhost:8001/competitions");

document.querySelector("#select-status").addEventListener("change", async function (event) {
    clearUl();

    let value = event.target.value;
    let url = "http://localhost:8001/competitions";
    if (value)
        url += `?status=${value}`;

    await getCompetitions(url);
});

}
