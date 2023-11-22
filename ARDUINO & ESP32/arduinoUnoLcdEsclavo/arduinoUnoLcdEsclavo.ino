#include <Wire.h>
#include <TFT.h>
#include <SPI.h>
#include <Servo.h>

#define I2C_ARDUINO_UNO_ADDR 0x60
#define cs 10
#define dc 9
#define rst 8

// Pin del servo
#define servoPin 3
Servo servo;  // Creamos una instancia del servo

//DATA
uint8_t receivedData[12];
// Variables para almacenar los valores anteriores
uint8_t previousReceivedData[11];
uint8_t receivedValue = 0;  // Variable para almacenar el valor recibido

//PANTALLA
TFT TFTscreen(cs, dc, rst);




int anguloActual = 50;  // Angulo inicial
int anguloObjetivo = 50;  // Angulo al que quieres llegar
unsigned long tiempoAnterior = 0;  // Variable para almacenar el tiempo anterior
int tiempoDeEspera = 1000;  // Intervalo de tiempo en milisegundos (1 segundo)



//TIEMPO

unsigned long lastUpdateTime = 0;
const unsigned long updateInterval = 250;  // Intervalo de actualización en milisegundos

void setup() {
  Wire.begin(I2C_ARDUINO_UNO_ADDR);
  Wire.onReceive(receiveEvent);
  Serial.begin(115200);

  TFTscreen.begin();
  TFTscreen.setRotation(0);  // Configura la rotación en 90 grados (vertical)

  TFTscreen.background(0, 0, 0);

  //SERVOS
  servo.attach(servoPin);  // Inicializamos el servo en el pin 3
  servo.write(50);         // Movemos el servo a 0 grados al inicio
}

void loop() {

  // Mueve gradualmente el servo hacia la posición deseada
  if (anguloActual != anguloObjetivo) {
    unsigned long tiempoActual = millis();

    if (tiempoActual - tiempoAnterior >= 20) {  // Ajusta este valor según la velocidad deseada
      tiempoAnterior = tiempoActual;

      if (anguloActual < anguloObjetivo) {
        anguloActual++;
      } else {
        anguloActual--;
      }

      servo.writeMicroseconds(map(anguloActual, 0, 180, 1000, 2000));
    }
  } else {
    // Si ya alcanzó la posición deseada, reinicia el tiempo de espera
    tiempoAnterior = millis();
  }

  // Espera 1 segundo antes de la próxima actualización
  if (millis() - tiempoAnterior >= tiempoDeEspera) {
    tiempoAnterior = millis();  // Reinicia el tiempo de espera
  }

}

//CUANDO SE RECIBEN VALORES
void receiveEvent(int byteCount) {
  if (byteCount == 12) {

    for (int i = 0; i < 12; i++) {
      receivedData[i] = Wire.read();
    }

    Serial.print("\nVALOR PUERTA :  ");
    Serial.println(receivedData[11]);


    //CONTAMOS CEROS
    int countZeros = 0;
    for (int i = 0; i < 11; i++) {
      if (receivedData[i] == 0) {
        countZeros++;
      }
    }


    //ESTÁ LLENO
    if (receivedData[11] == 2 && countZeros == 0) {
      //servo.write(150);
      anguloObjetivo = 150;

      //NO ESTÁ LLENO
    } else if (receivedData[11] == 1) {
      //servo.write(50);

      anguloObjetivo = 50;
    }

   


    // Verifica si los valores en receivedData han cambiado
    bool valuesChanged = false;
    for (int i = 0; i < 11; i++) {
      if (receivedData[i] != previousReceivedData[i]) {
        valuesChanged = true;
        break;  // Si se encuentra un cambio, sal del bucle
      }
    }

    //SI CAMBIAN LOS VALORES
    if (valuesChanged) {
      //Serial.println("\nCAMBIO");



      Serial.println("Datos recibidos en Arduino Uno:");
      for (int i = 0; i < 11; i++) {
        Serial.print(receivedData[i]);
        Serial.print(" ");
      }

      Serial.print("Estacionamientos Libres: ");
      Serial.println(countZeros);

      // Convierte countZeros a una cadena de caracteres
      char countZerosStr[4];
      snprintf(countZerosStr, 4, "%d", countZeros);

      // Si no hay ceros, movemos el servo a 0 grados

      //ESTÁ LLENO
      if (countZeros == 0 && receivedData[11] == 2) {
        //servo.write(150);
        
        anguloObjetivo = 150;
        //NO ESTÁ LLENO
      } else if (countZeros != 0 || receivedData[11] == 1) {
        //servo.write(50);

        anguloObjetivo = 50;
      }

      unsigned long currentTime = millis();

      // Actualiza la pantalla solo si ha transcurrido el tiempo necesario
      if (currentTime - lastUpdateTime >= updateInterval) {
        // Limpia la pantalla LCD
        TFTscreen.background(0, 0, 0);

        // Imprime el valor en la pantalla LCD
        TFTscreen.stroke(255, 255, 255);
        TFTscreen.setTextSize(2);
        TFTscreen.text("PARKINGS", 20, 10);
        TFTscreen.setTextSize(8);
        TFTscreen.stroke(0, 255, 0);
        TFTscreen.text(countZerosStr, 20, 50);

        lastUpdateTime = currentTime;
      }

      // ACTUALIZACIÓN DE VALORES ACTUALES -------------------------------------
      for (int i = 0; i < 11; i++) {
        previousReceivedData[i] = receivedData[i];
      }

    } else {
      //Serial.println("Los valores en receivedData no han cambiado.");
    }
  }
}
