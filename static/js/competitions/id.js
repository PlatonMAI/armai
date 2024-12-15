window.onload = async (e) => {

let url = new URL(window.location.href);
let competitionId = url.searchParams.get("id");

let isAdmin = await checkIsAdmin();
let isOwner;

let status = "";

async function getCompetitionInfo() {
    console.log(`competitionId: ${competitionId}`);
    let response = await fetch(`http://localhost:8001/competitions/${competitionId}`);

    if (response.status != 200) {
        alert("Что-то пошло не так!");
        console.log(response.status);
        throw new Error();
    }

    let responseJson = await response.json();
    console.log(responseJson);

    document.querySelector("#name").innerText = responseJson["name"];

    status = responseJson["status"];
    document.querySelector("#status").innerText += status;

    isOwner = responseJson["isOwner"];

    if (isOwner || isAdmin) {
        let button = document.querySelector("#status-change");
        if (status != "finished")
            button.classList.remove("inactive");
        
        let text;
        switch (status) {
            case "registration":
                text = "Начать подтверждение участия"
                break;
            case "confirmation":
                text = "Начать взвешивание"
                break;
            case "weighing":
                text = "Начать соревнование"
                break;
            case "inProcess":
                text = "Завершить соревнование"
                break;
        }
        button.innerText = text;
    }
}

async function getRegistrationInfo () {
    // Открываем блок статуса регистрации
    document.querySelector("#registration-group").classList.remove("inactive");

    // Отображаем пользователю элементы регистрации на соревнование
    let responseCheckRegister = await fetch(`http://localhost:8001/competitions/${competitionId}/register/check`);

    if (responseCheckRegister.status == 200) {
        document.querySelector("#registration-user div").classList.remove("inactive");
    } else {
        let aElem = document.querySelector("#registration-user a")
        aElem.classList.remove("inactive");
        aElem.href = `/competitions_/register.html?id=${competitionId}`;
    }

    // Зарегистрированные пользователи
    let responseUsersRegistered = await fetch(`http://localhost:8001/competitions/${competitionId}/register/users`);

    let responseJson = await responseUsersRegistered.json();
    console.log(responseJson);

    let registrationUsersElem = document.querySelector("#registration-users");
    if (responseJson["users"] === null) {
        registrationUsersElem.innerText = "Пока еще никто не зарегистрировался на соревнование!";
    } else {
        let registrationUsersListElem = registrationUsersElem.querySelector("ul");
        let userElem = registrationUsersListElem.querySelector("li.inactive");
        for (let user of responseJson["users"]) {
            let userNewElem = userElem.cloneNode(true);
            userNewElem.classList.remove("inactive");

            let nameElem = userNewElem.querySelector(".user-name");
            nameElem.href = `/users_/id.html?id=${user["userId"]}`;
            nameElem.innerText = user["name"];
            
            let teamElem = userNewElem.querySelector(".user-team");
            if (user["teamId"] !== null) {
                teamElem.classList.remove("inactive");
                
                let teamElemA = teamElem.querySelector("a");
                teamElemA.href = `/teams_/id.html?id=${user["teamId"]}`;
                teamElemA.innerText = user["teamName"];
            }

            registrationUsersListElem.append(userNewElem);
        }
    }
}

async function getConfirmationInfo () {
    // Открываем блок статуса подтверждения
    let confirmationGroupElem = document.querySelector("#confirmation-group");
    confirmationGroupElem.classList.remove("inactive");

    // Проверяем, была ли регистрация
    let responseCheckRegister = await fetch(`http://localhost:8001/competitions/${competitionId}/register/check`);
    if (responseCheckRegister.status == 404) {
        document.querySelector("#confirmation-user").innerText = "Вы уже не можете подтвердить участие в этом соревновании, так как не регистрировались на него!";
    } else if (responseCheckRegister.status == 200) {
        
        // Отображаем пользователю элементы подтверждения участия в соревновании
        let responseCheckConfirmation = await fetch(`http://localhost:8001/competitions/${competitionId}/confirmation/check`);

        if (responseCheckConfirmation.status == 200) {
            document.querySelector("#confirmation-user div").classList.remove("inactive");
        } else if (responseCheckConfirmation.status == 404) {
            let aElem = document.querySelector("#confirmation-user a")
            aElem.classList.remove("inactive");
            aElem.addEventListener("click", async function(event) {
                event.preventDefault();

                let response = await fetch(`http://localhost:8001/competitions/${competitionId}/confirmation`, {method: "POST"});
                if (response.status == 200) {
                    window.location.reload();
                } else {
                    alert("Что-то пошло не так!");
                    throw new Error();
                }
            });
        } else {
            throw new Error();
        }

    } else {
        throw new Error();
    }

    // Подтвержденные пользователи
    let responseUsersRegistered = await fetch(`http://localhost:8001/competitions/${competitionId}/confirmation/users`);

    let responseJson = await responseUsersRegistered.json();
    console.log(responseJson);

    let confirmationUsersElem = document.querySelector("#confirmation-users");
    if (responseJson["users"] === null) {
        confirmationUsersElem.innerText = "Пока еще никто не подтвердил свое участие в соревновании!";
    } else {
        let confirmationUsersListElem = confirmationUsersElem.querySelector("ul");
        let userElem = confirmationUsersListElem.querySelector("li.inactive");
        for (let user of responseJson["users"]) {
            let userNewElem = userElem.cloneNode(true);
            userNewElem.classList.remove("inactive");

            let nameElem = userNewElem.querySelector(".user-name");
            nameElem.href = `/users_/id.html?id=${user["userId"]}`;
            nameElem.innerText = user["name"];
            
            let teamElem = userNewElem.querySelector(".user-team");
            if (user["teamId"] !== null) {
                teamElem.classList.remove("inactive");
                
                let teamElemA = teamElem.querySelector("a");
                teamElemA.href = `/teams_/id.html?id=${user["teamId"]}`;
                teamElemA.innerText = user["teamName"];
            }

            confirmationUsersListElem.append(userNewElem);
        }
    }
}

async function weighingParticipant(event) {
    let participantId = Number(event.target.id);
    let weight = Number(event.target.parentElement.querySelector("input").value);

    let response = await fetch(`http://localhost:8001/competitions/${competitionId}/weighing`, {
        method: "POST",
        body: JSON.stringify({participantId, weight})
    });

    if (response.status != 200) {
        alert("Что-то пошло не так!");
        throw new Error();
    }

    window.location.reload();
}

async function getWeighingInfo () {
    // Открываем блок статуса взвешивания
    let weighingGroupElem = document.querySelector("#weighing-group");
    weighingGroupElem.classList.remove("inactive");

    // Пользователи для взвешивания
    let responseUsers = await fetch(`http://localhost:8001/competitions/${competitionId}/confirmation/users`);

    let responseJson = await responseUsers.json();
    console.log(responseJson);

    let weighingUsersElem = document.querySelector("#weighing-users");
    let weighingUsersListElem = weighingUsersElem.querySelector("ul");
    let userElem = weighingUsersListElem.querySelector("li.inactive");
    for (let user of responseJson["users"]) {
        let userNewElem = userElem.cloneNode(true);
        userNewElem.classList.remove("inactive");

        let nameElem = userNewElem.querySelector(".user-name");
        nameElem.href = `/users_/id.html?id=${user["userId"]}`;
        nameElem.innerText = user["name"];
        
        let teamElem = userNewElem.querySelector(".user-team");
        if (user["teamId"] !== null) {
            teamElem.classList.remove("inactive");
            
            let teamElemA = teamElem.querySelector("a");
            teamElemA.href = `/teams_/id.html?id=${user["teamId"]}`;
            teamElemA.innerText = user["teamName"];
        }

        if (isOwner || isAdmin) {
            let buttonElem = userNewElem.querySelector("button");
            buttonElem.id = user["participantId"];
            buttonElem.addEventListener("click", weighingParticipant);

            if (user["weight"] !== null) {
                userNewElem.querySelector("input").value = user["weight"];
            }

            userNewElem.querySelector(".user-weighing").classList.remove("inactive");
        }

        weighingUsersListElem.append(userNewElem);
    }
}

async function getInProcessInfo() {
    // Открываем блок статуса в процессе
    let inProcessGroupElem = document.querySelector("#inProcess-group");
    inProcessGroupElem.classList.remove("inactive");

    // Получаем список категорий
    let response = await fetch(`http://localhost:8001/competitions/${competitionId}/categories`);
    let responseJson = await response.json();
    console.log(responseJson);
    
    let categoryElem = inProcessGroupElem.querySelector(".category");
    let listElem = inProcessGroupElem.querySelector("ul");

    for (let category of responseJson["categories"]) {
        let newElem = fillCategories(categoryElem, listElem, category);
        newElem.querySelector("a").href = `/competitions_/category.html?competitionId=${competitionId}&categoryId=${category["id"]}`;
    }
}

async function getFinishedInfo() {
    // Открываем блок статуса завершено
    let finishedGroupElem = document.querySelector("#finished-group");
    finishedGroupElem.classList.remove("inactive");

    // Получаем список категорий
    let response = await fetch(`http://localhost:8001/competitions/${competitionId}/categories`);
    let responseJson = await response.json();
    console.log(responseJson);
    
    let categoryElem = finishedGroupElem.querySelector(".category");
    let listElem = finishedGroupElem.querySelector("ul");

    for (let category of responseJson["categories"]) {
        let newElem = fillCategories(categoryElem, listElem, category);
        newElem.querySelector("a").href = `/competitions_/category.html?competitionId=${competitionId}&categoryId=${category["id"]}`;

        let response = await fetch(`http://localhost:8001/competitions/${competitionId}/categories/${category["id"]}/winner`);
        let winnerInfo = await response.json();

        let userNameElem = newElem.querySelector(".user-name");
        userNameElem.href = `/users_/id.html?id=${winnerInfo["userId"]}`;
        userNameElem.innerText = winnerInfo["name"];
        let userTeamElem = newElem.querySelector(".user-team");
        if (winnerInfo["teamId"] !== null) {
            userTeamElem.classList.remove("inactive");
            
            let teamElemA = userTeamElem.querySelector("a");
            teamElemA.href = `/teams_/id.html?id=${winnerInfo["teamId"]}`;
            teamElemA.innerText = winnerInfo["teamName"];
        }
    }
}

document.querySelector("#status-change").addEventListener("click", async function(event) {
    let response = await fetch(`http://localhost:8001/competitions/${competitionId}/change_status`);

    if (response.status == 200) {
        window.location.reload();
    } else {
        alert("Что-то пошло не так!");
        throw new Error();
    }
});

await getCompetitionInfo();
switch (status) {
    case "registration":
        await getRegistrationInfo();
        break;
    case "confirmation":
        await getConfirmationInfo();
        break;
    case "weighing":
        await getWeighingInfo();
        break;
    case "inProcess":
        await getInProcessInfo();
        break;
    case "finished":
        await getFinishedInfo();
        break;
    default:
        break;
}

}
