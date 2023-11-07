// Función que activa el menú responsive y adapta el contenido por debajo
function Funcion1(){
    const hamburger = document.querySelector(".hamburger");
    const content = document.querySelector('.contenido');
    hamburger.onclick = function() {
        const navBar = document.querySelector(".nav-bar");
        navBar.classList.toggle("active");

        if (navBar.classList.contains('active')) {
            content.style.marginTop = '450px'; // Ajusta el valor según la altura de tu menú desplegable
            }  
            else {
            content.style.marginTop = '0';
            }
    };
}



  