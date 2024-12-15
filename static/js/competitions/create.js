window.onload = async (e) => {

let response = await fetch("http://localhost:8001/category_schemas");
let responseJson = await response.json();
console.log(responseJson);
let categorySchemas = responseJson["schemas"];

let selectSchemasElem = document.querySelector("#categorySchemaId");
for (let schema of categorySchemas) {
    let optionElem = document.createElement("option");
    optionElem.value = schema.id;
    optionElem.innerText = schema.name;
    selectSchemasElem.append(optionElem);
}

let formElem = document.querySelector("form#form-competition");
formElem.addEventListener("submit", async function (event) {
    event.preventDefault();

    let formData = new FormData(formElem);
    let object = Object.fromEntries(formData);

    if (object["hand"] == "")
        object["hand"] = null;
    object["categorySchemaId"] = Number(object["categorySchemaId"]);

    console.log(JSON.stringify(object));

    let response = await fetch('http://localhost:8001/competitions', {
        method: 'POST',
        body: JSON.stringify(object)
    });

    let responseJson = await response.json();

    if (response.ok) {
        document.location.href = `/competitions_/id.html?id=${responseJson["id"]}`;
    } else {
        alert("Что-то пошло не так!");
        console.log(response.status);
        console.log(response.statusText);
    }
});

}
