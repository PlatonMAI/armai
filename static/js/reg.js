window.onload = async (e) => {

let formElem = document.querySelector("form#reg");
formElem.addEventListener("submit", async function (event) {
    event.preventDefault();

    let formData = new FormData(formElem);

    if (formData.get("password") != formData.get("confirm-password")) {
        alert("Пароли не совпадают!");
        return;
    }

    console.log("email: " + formData.get("email"));
    console.log("password: " + formData.get("password"));
    console.log("name: " + formData.get("name"));
    console.log("sex: " + formData.get("sex"));
    console.log("birth: " + formData.get("birth"));
    console.log(JSON.stringify(Object.fromEntries(formData)));

    let response = await fetch('http://localhost:8001/users/register', {
        method: 'POST',
        body: JSON.stringify(Object.fromEntries(formData))
    });

    if (response.ok) {
        document.location.href = "/me.html";
    } else if (response.status == 409) {
        alert("Пользователь с таким email уже существует!");
    } else {
        alert("Что-то пошло не так!");
        console.log("reg: " + response.status);
    }
});

}
