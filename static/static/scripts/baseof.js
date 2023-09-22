// IPopup

let ipopup = document.getElementById("obj-baseof-ipopup");
let ipopupImage = document.getElementById("img-baseof-ipopup-image");

for (let img of document.querySelectorAll("img:not(#img-baseof-ipopup-image)")) {
    img.addEventListener("click", () => {
        ipopup.style.opacity = 1;
        ipopup.style.pointerEvents = "all";
        ipopupImage.src = img.src;
    });
}

function closeIPopup() {
    ipopup.style.opacity = 0;
    ipopup.style.pointerEvents = "none";
    ipopupImage.src = "";
}

// Dynamic content

function updateDynamic(elementId) {
    try {
        let el = document.querySelector(".dynamic-content#" + elementId);
        el.innerText = dynamicValues[elementId];
    } catch (exception) {
        console.log("ERROR: dynamic element with id " + elementId + " doesn't exist.");
    }
}

if (typeof dynamicValues != 'undefined') {
    for (let [elementId, _] of Object.entries(dynamicValues)) {
        updateDynamic(elementId);
    }
}