function getCellValue(tr, idx) { 
    return tr.children[idx].innerText || tr.children[idx].textContent; 
}

const comparer = (idx, asc) => (a, b) => ((v1, v2) => 
    v1 !== '' && v2 !== '' && !isNaN(v1) && !isNaN(v2) ? v1 - v2 : v1.toString().localeCompare(v2)
    )(getCellValue(asc ? a : b, idx), getCellValue(asc ? b : a, idx));

document.querySelectorAll('th').forEach((th) => {
    th.style.cursor = "pointer";
    th.addEventListener('click', (() => {
        let tbody = th.parentNode.parentNode.parentNode.querySelector("tbody");
        Array.from(tbody.querySelectorAll('tr'))
             .sort(comparer(Array.from(th.parentNode.children).indexOf(th), this.asc = !this.asc))
             .forEach(tr => tbody.appendChild(tr));
    }))
}); 