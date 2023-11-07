window.addEventListener('load', () => {

    let botonn = document.getElementById('formOpenClose');

    let valor = ""

    function toggleTrafficLight() {
    
          const trafficLight = document.getElementById('trafficLight');
          const button = document.getElementById('toggleButton');
    
          if (trafficLight.classList.contains('closed')) {
            valor = "1";
              trafficLight.classList.remove('closed');
              trafficLight.classList.add('open');
              button.textContent = 'Cerrar';
              console.log(valor);
              sendDataToServer(valor);
          } else {
            valor = "2";
              trafficLight.classList.remove('open');
              trafficLight.classList.add('closed');
              button.textContent = 'Abrir';
              console.log(valor);
              sendDataToServer(valor);
          }
        
    }

    function sendDataToServer(valor) {
        
        let formData = new FormData();
        formData.append("closeOpen", valor);
    
        fetch('openClose.php', {
            method: 'POST',
            body: formData
        })
        .then(response => response.json())
        .then(response => {
            if (response.ok) {
                console.log('Datos actualizados en la base de datos.');
            } else {
                console.error('Error al actualizar la base de datos.');
            }
        })
        .catch(error => {
            console.error('Error en el fetch', error);
        });
    }


    botonn.addEventListener('submit', (e) => {

        e.preventDefault();

        toggleTrafficLight();

    });

});
