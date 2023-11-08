window.addEventListener('load', () => {


    let boton = document.getElementById('formulario');

    let usuario = document.getElementById('username');

    let password = document.getElementById('password');

    
  
    function data (){


        let datos = new FormData();

        datos.append("nombreUsuario", usuario.value);
        datos.append("accesoClave", password.value);
        fetch('https://phppasarvariable.000webhostapp.com/BACKEND/validame.php', {
            method: 'POST',
            body: datos
        }).then(Response => Response.json())
        .then(({success}) => {
            if(success === 1){

                noti();
                const overlay = document.getElementById("overlay");
                overlay.style.display = "none";

                const control = document.querySelector(".controlUnlock");
                control.style.display = "flex";

                const cerrarSesion = document.querySelector(".cerrarSesion");
                cerrarSesion.style.display = "flex";

                const accesor = document.getElementById("accesar");
                accesor.style.display = "none";


                //alert("Usuarios y Pass correctos");
                console.log("correcto");


                //location.href = 'index2.html';
            }else{
                document.getElementById('errorMsg').style.display = 'flex';
                console.log("equicado");
            }
        });
    }




    boton.addEventListener('submit', (e) => {

        e.preventDefault();

        data();

    });


    function noti (){

        var toast = document.querySelector('.wrapper');

        // Muestra la notificación
        toast.style.display = 'flex';

        // Oculta la notificación después de 5 segundos (5000 milisegundos)
        setTimeout(function() {
        toast.style.display = 'none';
        }, 5000);
        }


});
