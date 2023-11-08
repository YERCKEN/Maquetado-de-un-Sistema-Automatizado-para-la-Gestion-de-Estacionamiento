
    function regresaIndex(){

      const regresa = document.getElementById("regresame");

      regresa.addEventListener("click", () => {
      //event.preventDefault();  
      window.location.href = "https://phppasarvariable.000webhostapp.com/FRONTEND/index.html";
  });
       
}
  
    //Cierra sesión y oculta los elementos 
    function cerrarSesion() {
  
      const logoutButton = document.querySelector(".cerrarSesion");
  
      //logoutButton.addEventListener("click", function () {
      const confirmLogout = confirm("¿Estás seguro de que quieres cerrar sesión?");
  
      if (confirmLogout) {
          window.location.href = "https://phppasarvariable.000webhostapp.com/FRONTEND/index.html";
      }
  //}
  //);
  
    }
  
    //Control de la etiqueta a
    function prevenirSobreNosotros()
    {
      document.querySelector(".sobreNosotros").addEventListener("click", function(event) {
          event.preventDefault(); // Previene la acción predeterminada del enlace
          // Tu lógica para mostrar el perfil del usuario aquí
      });
    }
  
    //Control de la etiqueta a
    function prevenirCerrarSesion()
    {
      document.querySelector(".cerrarSesion").addEventListener("click", function(event) {
          event.preventDefault(); // Previene la acción predeterminada del enlace
          // Tu lógica para mostrar el perfil del usuario aquí
      });
    }
  


  

  function actualizarReloj() {
    var ahora = new Date();
    var horas = ahora.getHours();
    var minutos = ahora.getMinutes();
    var segundos = ahora.getSeconds();

    // Agregar un cero delante si los minutos o segundos son menores que 10
    minutos = minutos < 10 ? "0" + minutos : minutos;
    segundos = segundos < 10 ? "0" + segundos : segundos;

    var horaActual = horas + ":" + minutos + ":" + segundos;

    // Actualizar el contenido del div con la hora actual
    document.getElementById("reloj").innerHTML = horaActual;
}

function dameFecha(){

        var fechaActual = new Date();

        // Formatear la fecha en un formato legible
        var options = { year: 'numeric', month: 'long', day: 'numeric' };
        var fechaFormateada = fechaActual.toLocaleDateString(undefined, options);

        // Mostrar la fecha en el elemento HTML con el id "fecha"
        document.getElementById("fecha").textContent = fechaFormateada;

}






      




 
  


      

