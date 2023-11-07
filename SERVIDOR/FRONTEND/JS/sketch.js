//IMG DE FONDO
let imgFondo;

let zoom = 1.0; // Factor de zoom inicial

// PANING
let Tx = 0;   
let Ty = 0;
//velocidad paning
let dts = 1; 

//ESCALA = ZOOM
let S = 1; 

//POSICIÓN CANVAS
let canvasX = 0; // Posición X actual del canvas
let canvasY = 0; // Posición Y actual del canvas


// % DE ALTURA DEL CANVAS
let porcentajeDeAltura = 0.80;
let porcentajeDeAnchura= 0.95;

//DATOS DE ESTACIONAMIENTO
let parkingData;


//PRELOAD __________________________________________________________________________-

function preload() {
  //imgFondo = loadImage('https://cdn.glitch.global/20e097f8-2be8-4fa4-8f12-20d3d33c120d/FONDO.jpg?v=1697933427787');
  imgFondo = loadImage('https://cdn.glitch.global/20e097f8-2be8-4fa4-8f12-20d3d33c120d/FONDO_GRIS_SIN_CESPED.jpg?v=1698018267809');
}

//SETUP __________________________________________________________________________-

function setup() {
  // Obtener el contenedor del canvas y sus dimensiones


  // Crear el canvas con las dimensiones del contenedor
  let canvas = createCanvas(windowWidth * porcentajeDeAnchura, windowWidth * porcentajeDeAltura);

  fetchParkingData();
  setInterval(fetchParkingData, 1000);  // Llama a fetchParkingData cada 1000ms (es decir, cada segundo)

  canvas.parent('canvas-container'); // Agrega el canvas al contenedor HTML
}


function draw() {
  background("#D0D7DA");
  
  // APLICAR TRANSFORMACIONES ===============================================
  push();

  // Traslación
  translate(Tx, Ty);
  // Escala
  scale(S);

  // Imagen
  image(imgFondo, 0, 0);
  if (parkingData) {
    dibujarEstacionamientoC();
  }

  // FIN DE TRANSFORMACIONES ===============================================================
  pop();

  // Información de posición del mouse
  /*
  textSize(24);
  fill("red");
  strokeWeight(1);
  text("X: " + mouseX, mouseX - 50, mouseY);
  fill("blue");
  text("Y: " + mouseY, mouseX - 50, mouseY + 20);
  */
  //agregarMargenes();
}

function fetchParkingData() {
  fetch('https://phppasarvariable.000webhostapp.com/BACKEND/database_access.php')
    .then(response => response.json())
    .then(data => {
        parkingData = data;
        //dibujarEstacionamientoC();
    })
    .catch(error => {
        console.error('Error:', error);
    });
}

function dibujarEstacionamientoC() {
  let positions = [
    {x: 683, y: 222}, {x: 728, y: 222}, {x: 774, y: 222}, {x: 819, y: 222}, {x: 864, y: 222}, {x: 909, y: 222},
    {x: 683, y: 320}, {x: 728, y: 320}, {x: 774, y: 320}, {x: 819, y: 320}, {x: 864, y: 320}, {x: 909, y: 320}
  ];
  
  for (let i = 0; i < positions.length; i++) {
    let parkKey = 'park' + (i + 1);
    let parkValue = parkingData[parkKey];
    console.log(`Valor para ${parkKey}: ${parkValue}`); // Imprime el valor
    dibujarRectangulo(positions[i].x, positions[i].y, 43, 91, parkValue);

  }
}
// FUCNIÓN PAR ADIBUJAR RECTÁNGULOO
function dibujarRectangulo(x, y, ancho, alto, value) {
  if (value === '0') {
    //fill("#866EFF");
    //fill("#C4FFEB");
    fill("#FFFFFF");
    //OCUPADO
  } else if (value === '1') {
    //MORADO
    //fill("#866EFF");
    //ROJO de ocupado
    fill("#FF4D4D");
  }
  rect(x, y, ancho, alto);
}


// FUNCUÓN PARA MÁRGENES Y TAMAÑO DE PANTALLA ===============================================
function agregarMargenes() {
  let porcentajeGrosor = 0.02;
  let grosorMargen = windowWidth * porcentajeGrosor;
  let alturaDeMargen = windowHeight * porcentajeDeAltura;

  noStroke();
  fill('white');

  // Izquierda
  rect(0, 0, grosorMargen, alturaDeMargen);
  // Derecha
  rect(windowWidth - grosorMargen, 0, grosorMargen, alturaDeMargen);
}

function windowResized() {
  // Cambiar el tamaño del canvas cuando se redimensiona la ventana
  resizeCanvas(windowWidth, windowHeight * porcentajeDeAltura);

  // Volver a agregar los márgenes
  //agregarMargenes();
}

//FUNCIONES DE TRANSFORMACIOES ===============================================================================

//traslación
function touchMoved() {
  if (estaEnElCanvas()) {
    Tx += (mouseX - pmouseX) * dts;
    Ty += (mouseY - pmouseY) * dts;
  }
}

//verificar si está en el canvas
function estaEnElCanvas() {
  return (0.0 <= pmouseX && pmouseX <= width) && (0.0 <= pmouseY && pmouseY <= height);
}

// evento de rueda de mouse

function mouseWheel(event) {
  if (estaEnElCanvas()) {
    let canvasX = mouseX;
    let canvasY = mouseY;

    if (event.delta > 0) {
      // Hacer zoom in centrado en la posición del mouse
      zoomOut(canvasX, canvasY);
    } else {
      // Hacer zoom out centrado en la posición del mouse
      zoomIn(canvasX, canvasY);
    }
  }
  return false; // Evitar que la página haga scroll
}

//ZOOM +
function zoomIn(mouseX, mouseY) {
   // Factor de escala para hacer zoom in
  let scaleFactor = 1.1;
  let newS = S * scaleFactor;
  
  // Ajusta la posición del canvas para que el mouse quede en el mismo lugar después del zoom
  Tx = mouseX - (mouseX - Tx) * scaleFactor;
  Ty = mouseY - (mouseY - Ty) * scaleFactor;
  
  S = newS;
  // Aquí debes redibujar el contenido del canvas con la nueva escala y posición
}

//ZOOM -

function zoomOut(mouseX, mouseY) {
  // Factor de escala para hacer zoom out
  let scaleFactor = 0.9; 
  let newS = S * scaleFactor;
  
  // Ajusta la posición del canvas para que el mouse quede en el mismo lugar después del zoom
  Tx = mouseX - (mouseX - Tx) * scaleFactor;
  Ty = mouseY - (mouseY - Ty) * scaleFactor;
  
  S = newS;
  // Aquí debes redibujar el contenido del canvas con la nueva escala y posición
}
