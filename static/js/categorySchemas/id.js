window.onload = async (e) => {

let url = new URL(window.location.href);
let id = url.searchParams.get("id");
console.log("categorySchemas_id: определенный id: " + id);

console.log("categorySchemas_id: обращаюсь к серверу...");
let response = await fetch(`http://localhost:8001/category_schemas/${id}`);

if (response.status != 200) {
    alert("Что-то пошло не так!");
    console.log(response.status);
    throw new Error();
}

let json = await response.json();
console.log(json);

document.querySelector("#name").innerText = json["name"];

let categoryElem = document.querySelector(".category");
let listElem = document.querySelector("ul");

for (let category of json["categories"]) {
    fillCategories(categoryElem, listElem, category);
}

}
