window.onload = async (e) => {

let formElem = document.querySelector("form#auth");
formElem.addEventListener("submit", async function (event) {
    event.preventDefault();

    let formData = new FormData(formElem);

    console.log("email: " + formData.get("email"));
    console.log("password: " + formData.get("password"));
    console.log(JSON.stringify(Object.fromEntries(formData)));

    let response = await fetch('http://localhost:8001/users/auth', {
        method: 'POST',
        body: JSON.stringify(Object.fromEntries(formData))
    });

    if (response.ok) {
        document.location.href = "/me.html";
    } else if (response.status == 401) {
        alert("Неверная почта или пароль!");
    } else {
        alert("Что-то пошло не так!");
        console.log("reg: " + response.status);
    }
});

}
