window.onload = async (e) => {

let url = new URL(window.location.href);
let competitionId = url.searchParams.get("competitionId");
let categoryId = url.searchParams.get("categoryId");

let response = await fetch(`http://localhost:8001/competitions/${competitionId}/categories/${categoryId}`);

let armfightElem = document.querySelector("#armfight");
if (response.status == 404) {
    armfightElem.innerText = "В данной категории армфайты закончились!";
} else {

    let armfight = await response.json();
    console.log(armfight);

    let buttonFirst = document.querySelector("#participant-first");
    let buttonSecond = document.querySelector("#participant-second");

    buttonFirst.innerText = armfight["participantFirstName"];
    buttonSecond.innerText = armfight["participantSecondName"];

    buttonFirst.addEventListener("click", async function(event) {
        let response = await fetch(`http://localhost:8001/competitions/${competitionId}/categories/${categoryId}`, {
            method: "POST",
            body: JSON.stringify({"id": Number(armfight["id"]), "winnerId": Number(armfight["participantFirstId"])})
        });

        if (response.status == 200) {
            window.location.reload();
        } else {
            alert("Что-то пошло не так!");
            throw new Error();
        }
    });
    buttonSecond.addEventListener("click", async function(event) {
        let response = await fetch(`http://localhost:8001/competitions/${competitionId}/categories/${categoryId}`, {
            method: "POST",
            body: JSON.stringify({"id": Number(armfight["id"]), "winnerId": Number(armfight["participantSecondId"])})
        });

        if (response.status == 200) {
            window.location.reload();
        } else {
            alert("Что-то пошло не так!");
            throw new Error();
        }
    });

}

}
