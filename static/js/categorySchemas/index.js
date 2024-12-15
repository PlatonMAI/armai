window.onload = async (e) => {

console.log("categorySchemas: обращаюсь к серверу...");
let response = await fetch(`http://localhost:8001/category_schemas`);

if (response.status != 200) {
    alert("Что-то пошло не так!");
    console.log(response.status);
    throw new Error();
}

let json = await response.json();
console.log(json);

let schemaElem = document.querySelector(".schema");
let listElem = document.querySelector("ul");

for (let schema of json["schemas"]) {
    let schemaNewElem = schemaElem.cloneNode(true);
    schemaNewElem.classList.remove("inactive");

    let id = schema["id"];
    let name = schema["name"];
    let aElem = schemaNewElem.querySelector("a");
    aElem.href = `/categorySchemas/id.html?id=${id}`;
    aElem.innerText = name;

    listElem.append(schemaNewElem);
}

}
