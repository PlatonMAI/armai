window.onload = async (e) => {

let formElem = document.querySelector("form#form-team");
formElem.addEventListener("submit", async function (event) {
    event.preventDefault();

    let formData = new FormData(formElem);

    console.log("name: " + formData.get("name"));
    console.log(JSON.stringify(Object.fromEntries(formData)));

    let response = await fetch('http://localhost:8001/teams', {
        method: 'POST',
        body: JSON.stringify(Object.fromEntries(formData))
    });

    let responseJson = await response.json();

    if (response.ok) {
        document.location.href = `/teams_/id.html?id=${responseJson["id"]}`;
    } else {
        alert("Что-то пошло не так!");
        console.log(response.status);
        console.log(response.statusText);
    }
});

}
