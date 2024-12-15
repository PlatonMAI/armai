async function checkIsAdmin() {
    let response = await fetch(`http://localhost:8001/users/me/is_admin`);
    let responseJson = await response.json();

    return responseJson["isAdmin"];
}

function fillCategories(categoryElem, listElem, category) {
    let categoryNewElem = categoryElem.cloneNode(true);
    categoryNewElem.classList.remove("inactive");

    if (category["sex"]) {
        let sex = category["sex"] == "male" ? "Мужчины" : "Женщины";
        categoryNewElem.querySelector(".sex").innerText = sex + ", ";
    } else {
        categoryNewElem.querySelector(".sex").classList.append("inactive");
    }

    if (category["ageMin"] || category["ageMax"]) {
        categoryNewElem.querySelector(".ageMin").innerText = category["ageMin"] ? `от ${category["ageMin"]} лет` : "";
        categoryNewElem.querySelector(".ageMax").innerText = category["ageMax"] ? ` до ${category["ageMax"]} лет` : "";
        categoryNewElem.querySelector(".ageMax").innerText += ", ";
    }

    if (category["weightMin"] || category["weightMax"]) {
        categoryNewElem.querySelector(".weightMin").innerText = category["weightMin"] ? `от ${category["weightMin"]}кг` : "";
        categoryNewElem.querySelector(".weightMax").innerText = category["weightMax"] ? ` до ${category["weightMax"]}кг` : "";
    }

    console.log(listElem);
    listElem.append(categoryNewElem);

    return categoryNewElem;
}
