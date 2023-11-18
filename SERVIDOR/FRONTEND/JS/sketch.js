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
let porcentajeDeAnchura= 0.90;

//DATOS DE ESTACIONAMIENTO
let parkingData;

// Variables para el pinch-to-zoom
let initialPinchDistance = 0;

//PRELOAD __________________________________________________________________________-
function preload() {
  imgFondo = loadImage('https://cdn.glitch.global/20e097f8-2be8-4fa4-8f12-20d3d33c120d/FONDO_GRIS_SIN_CESPED.jpg?v=1698018267809');
}

//SETUP __________________________________________________________________________-
function setup() {
  let canvas = createCanvas(windowWidth * porcentajeDeAnchura, windowHeight * porcentajeDeAltura);

  fetchParkingData();
  setInterval(fetchParkingData, 1000);

  canvas.parent('canvas-container');
}

function draw() {
  background("#D0D7DA");

  push();
  translate(Tx, Ty);
  scale(S);

  image(imgFondo, 0, 0);
  if (parkingData) {
    dibujarEstacionamientoC();
  }
  pop();
}

function fetchParkingData() {
  fetch('https://phppasarvariable.000webhostapp.com/BACKEND/database_access.php')
    .then(response => response.json())
    .then(data => {
      parkingData = data;
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
    console.log(`Valor para ${parkKey}: ${parkValue}`);
    dibujarRectangulo(positions[i].x, positions[i].y, 43, 91, parkValue);
  }
}

function dibujarRectangulo(x, y, ancho, alto, value) {
  if (value === '0') {
    fill("#FFFFFF");
  } else if (value === '1') {
    fill("#FF4D4D");
  }
  rect(x, y, ancho, alto);
}

function agregarMargenes() {
  let porcentajeGrosor = 0.02;
  let grosorMargen = windowWidth * porcentajeGrosor;
  let alturaDeMargen = windowHeight * porcentajeDeAltura;

  noStroke();
  fill('white');

  rect(0, 0, grosorMargen, alturaDeMargen);
  rect(windowWidth - grosorMargen, 0, grosorMargen, alturaDeMargen);
}

function windowResized() {
  resizeCanvas(windowWidth * porcentajeDeAnchura, windowHeight * porcentajeDeAltura);
}

//FUNCIONES DE TRANSFORMACIOES ===============================================================================
//traslación
function touchMoved() {
  if (estaEnElCanvas()) {
    if (touches.length === 1) {
      // Paning con un dedo
      Tx += (touches[0].x - pmouseX) * dts;
      Ty += (touches[0].y - pmouseY) * dts;
    } else if (touches.length === 2) {
      // Pinch-to-zoom con dos dedos
      let pinchDistance = dist(touches[0].x, touches[0].y, touches[1].x, touches[1].y);

      if (initialPinchDistance === 0) {
        initialPinchDistance = pinchDistance;
      } else {
        let delta = pinchDistance - initialPinchDistance;

        if (delta > 0) {
          // Zoom in
          zoomIn((touches[0].x + touches[1].x) / 2, (touches[0].y + touches[1].y) / 2);
        } else {
          // Zoom out
          zoomOut((touches[0].x + touches[1].x) / 2, (touches[0].y + touches[1].y) / 2);
        }

        initialPinchDistance = pinchDistance;
      }
    }
  }
}

function touchEnded() {
  // Restablecer la distancia inicial al finalizar el toque
  initialPinchDistance = 0;
}

function estaEnElCanvas() {
  return (0.0 <= touches[0].x && touches[0].x <= width) && (0.0 <= touches[0].y && touches[0].y <= height);
}

function mouseWheel(event) {
  if (estaEnElCanvas()) {
    let canvasX = mouseX;
    let canvasY = mouseY;

    if (event.delta > 0) {
      zoomOut(canvasX, canvasY);
    } else {
      zoomIn(canvasX, canvasY);
    }
  }
  return false;
}

function zoomIn(mouseX, mouseY) {
  let scaleFactor = 1.03;
  let newS = S * scaleFactor;

  Tx = mouseX - (mouseX - Tx) * scaleFactor;
  Ty = mouseY - (mouseY - Ty) * scaleFactor;

  S = newS;
}

function zoomOut(mouseX, mouseY) {
  let scaleFactor = 0.97;
  let newS = S * scaleFactor;

  Tx = mouseX - (mouseX - Tx) * scaleFactor;
  Ty = mouseY - (mouseY - Ty) * scaleFactor;

  S = newS;
}
