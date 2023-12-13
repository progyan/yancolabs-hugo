// IPopup

let ipopup = document.getElementById("obj-baseof-ipopup");
let ipopupImage = document.getElementById("img-baseof-ipopup-image");

for (let img of document.querySelectorAll("img:not(#img-baseof-ipopup-image):not(.tooltip-img)")) {
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

function updateDynamicValue(elementId) {
    try {
        let el = document.querySelector(".dynamic-content#" + elementId);
        el.innerText = dynamicValues[elementId];
    } catch (exception) {
        console.log("ERROR: dynamic element with id " + elementId + " doesn't exist.");
    }
}

function updateDynamicHref(elementId) {
    try {
        let el = document.querySelector(".dynamic-link#" + elementId);
        el.href = dynamicHrefs[elementId];
    } catch (exception) {
        console.log("ERROR: dynamic element with id " + elementId + " doesn't exist.");
    }
}

if (typeof dynamicValues != 'undefined') {
    for (let [elementId, _] of Object.entries(dynamicValues)) {
        updateDynamicValue(elementId);
    }
}

if (typeof dynamicHrefs != 'undefined') {
    for (let [elementId, _] of Object.entries(dynamicHrefs)) {
        updateDynamicHref(elementId);
    }
}

function languageChanged() {
    let langSelect = document.getElementById("obj-baseof-langselect");
    window.location.href
}