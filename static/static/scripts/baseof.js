let ipopup = document.getElementById("obj-baseof-ipopup");
let ipopupImage = document.getElementById("img-baseof-ipopup-image");

for (let img of document.querySelectorAll("img:not(#img-baseof-ipopup-image)")) {
    img.addEventListener("click", () => {
        ipopup.style.display = "block";
        ipopupImage.src = img.src;
    });
}

function closeIPopup() {
    ipopup.style.display = "none";
}