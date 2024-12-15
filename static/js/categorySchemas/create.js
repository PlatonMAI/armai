window.onload = async (e) => {

function emptyToNull(str) {
    return str ? str : null;
}

const sexGroupsElem = document.querySelector(".sex-groups");

const sexGroupElem = document.querySelector(".sex-group");
const ageGroupElem = document.querySelector(".age-group");
const weightGroupElem = document.querySelector(".weight-group");

function addSex(event) {
    let sexGroupNewElem = sexGroupElem.cloneNode(true);
    
    if (event)
        event.target.before(sexGroupNewElem);
    else
        sexGroupsElem.prepend(sexGroupNewElem);
}
document.querySelector(".add-sex").addEventListener("click", function (event) {
    event.preventDefault();

    addSex(event);
    addEventListeners();
});

function delete_(event) {
    event.preventDefault();
    console.log(event.target);

    event.target.parentNode.remove();
}
function addAge(event) {
    event.preventDefault();

    let ageGroupNewElem = ageGroupElem.cloneNode(true);
    event.target.before(ageGroupNewElem);
    addEventListeners();
}
function addWeight(event) {
    event.preventDefault();

    let weightGroupNewElem = weightGroupElem.cloneNode(true);
    event.target.before(weightGroupNewElem);
    addEventListeners();
}

function addEventListeners() {
    document.querySelectorAll(".delete").forEach(item => item.addEventListener("click", delete_));
    document.querySelectorAll(".add-age").forEach(item => item.addEventListener("click", addAge));
    document.querySelectorAll(".add-weight").forEach(item => item.addEventListener("click", addWeight));
}

document.querySelector("#form-category").addEventListener("submit", async function (event) {
    event.preventDefault();

    let sexElems = Array.from(document.querySelectorAll(".sex-group")).slice(1);
    let schemaSex = [];
    for (let sexElem of sexElems) {
        let okSex = !!sexElem.querySelector("select").value;

        let ageElems = sexElem.querySelectorAll(".age-group");
        let schemaAge = [];
        for (let ageElem of ageElems) {
            let okAge = (ageElem.querySelector("input:first-child").value || ageElem.querySelector("input:last-child").value);

            let weightElems = ageElem.querySelectorAll(".weight-group");
            let schemaWeight = [];
            for (let weightElem of weightElems) {
                let okWeight = (weightElem.querySelector("input:first-child").value || weightElem.querySelector("input:last-child").value);
                if (!okWeight)
                    continue;

                schemaWeight.push({
                    "weight": emptyToNull(Number(weightElem.querySelector("input:last-child").value)),
                    "schema": []
                });
            }

            if (okAge) {
                schemaAge.push({
                    "age": emptyToNull(Number(ageElem.querySelector("input:last-child").value)),
                    "schema": schemaWeight
                });
            } else {
                schemaAge = schemaWeight;
            }
        }
        
        if (okSex) {
            schemaSex.push({
            "sex": sexElem.querySelector("select").value,
            "schema": schemaAge
            });
        } else {
            schemaSex = schemaAge;
        }
    }

    let schema = {};
    schema["name"] = document.querySelector("#name").value;
    schema["schema"] = schemaSex;

    console.log(schema);

    let response = await fetch('/category_schemas', {
        method: 'POST',
        body: JSON.stringify(schema)
    });

    if (response.status == 200) {
        alert("Успешно!");
        let responseJson = await response.json();
        console.log(responseJson);
        window.location.href = `/categorySchemas/id.html?id=${responseJson["id"]}`;
    } else {
        alert("Что-то пошло не так!");
        console.log(response.status);
        console.log(response.statusText);
    }
});

addSex();
addEventListeners();

}