document.addEventListener("DOMContentLoaded", function (){
    const kuru = document.getElementById("kuru");
    const kurugif = document.getElementById("kurugif");
    kuru.addEventListener("click", () => {
        if (kurugif.style.display == "block") {
            kurugif.style.display = "none";
        }
        else {
            kurugif.style.display = "block";
        }
    });
});