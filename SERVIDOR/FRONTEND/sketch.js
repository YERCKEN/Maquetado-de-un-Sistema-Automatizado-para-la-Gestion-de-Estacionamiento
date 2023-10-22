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

//PRELOAD __________________________________________________________________________-

function preload() {
  imgFondo = loadImage('https://cdn.glitch.global/20e097f8-2be8-4fa4-8f12-20d3d33c120d/FONDO.jpg?v=1697933427787');
}

//SETUP __________________________________________________________________________-

function setup() {
  createCanvas(1080, 1920);
}

function draw() {
  background(220);
  
  // APLICAR TRANSFORMACIONES ===============================================
  push();

  // Traslación
  translate(Tx, Ty);
  // Escala
  scale(S);

  // Imagen
  image(imgFondo, 0, 0);

  // FIN DE TRANSFORMACIONES ===============================================================
  pop();
  

  // Información de posición del mouse
  textSize(24);
  fill("red");
  strokeWeight(1);
  text("X: " + mouseX, mouseX - 50, mouseY);
  fill("blue");
  text("Y: " + mouseY, mouseX - 50, mouseY + 20);
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
      zoomIn(canvasX, canvasY);
    } else {
      // Hacer zoom out centrado en la posición del mouse
      zoomOut(canvasX, canvasY);
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
