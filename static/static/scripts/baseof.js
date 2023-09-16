let ipopup = document.getElementById("obj-baseof-ipopup");
let ipopupImage = document.getElementById("img-baseof-ipopup-image");

for (let img of document.getElementsByTagName("img")) {
    img.addEventListener("click", () => {
        ipopup.style.display = "none";
        ipopupImage.src = self.src;
    });
}