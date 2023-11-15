#include <HTTPClient.h>
#include <WiFi.h>
#include <Wire.h>

//======================================================================================
// WIFI
//======================================================================================
const char* ssid = "CWC-7986324";      // SSID de tu red Wi-Fi
const char* password = "snns7pdTxnkw";  // Contraseña de tu red Wi-Fi


//======================================================================================
// DATOS RECIBIDOS
//======================================================================================
int receivedData[11];  // Array para almacenar los datos I2C
int previousData[11]; // Array para almacenar los datos I2C anteriores
#define I2C_ARDUINO_UNO_ADDR 0x60 // Dirección del Arduino Uno

// CERRADO O ABIERTO
int estadoServo = 1;

#define I2C_DEV_ADDR 0x55
//======================================================================================
// CONEXIÓN SERVIDOR
//======================================================================================
const char* urlServidorDirection = "https://phppasarvariable.000webhostapp.com/BACKEND/ServoMotor.php";
const char* urlServidorParkings = "https://phppasarvariable.000webhostapp.com/BACKEND/esp-post.php";


//======================================================================================
// SETUP
//======================================================================================
void setup() {
  Serial.begin(115200);
  Serial.println(F("\nESP32 SEND DATA TO PHP SERVER"));
  
  WiFi.begin(ssid, password);
  Serial.print("\nConectando...");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConexión OK!");
  //Serial.print("\nIP Local: ");
  Serial.println(WiFi.localIP());
  
  Wire.onReceive(onReceive);
  Wire.onRequest(onRequest);
  Wire.begin(I2C_DEV_ADDR); // Utiliza la dirección I2C 0x55
}


//======================================================================================
// I2C
//======================================================================================


void onRequest() {
  //Wire.print(i++);
  Wire.print(estadoServo);
}

// Función para procesar datos I2C recibidos
void onReceive(int len) {

  //Serial.println("Datos recibidos en ESP32:");
  for (int i = 0; i < 11; i++) {
    receivedData[i] = Wire.read();
    //Serial.print(receivedData[i]);
    //Serial.print(" ");
  }
  //Serial.println("Received.");

   // Enviar respuesta al Arduino Mega

   // Enviar la variable estadoServo de vuelta al Arduino MEGA
   // Enviar la variable estadoServo de vuelta al Arduino MEGA
  

}

//======================================================================================
// FUNCIÓN PARA DETERMINAR SI LOS VALORES DEL VECTOR HAN CAMBIADO
//======================================================================================

// Comprueba si los valores han cambiado
bool valoresHanCambiado() {
  for (int i = 0; i < 11; i++) {
    if (receivedData[i] != previousData[i]) {
      Serial.println("CAMBIARON");
      return true; // Al menos un valor ha cambiado
    }
  }
  //Serial.println("no cambiaronCambiaron");
  return false; // Ningún valor ha cambiado
}

//======================================================================================
// POST PARKING
//======================================================================================

//ENVIO DE DATOS
void EnvioDatos() {

  if (WiFi.status() == WL_CONNECTED ) {

    // Crear objeto HTTP
    HTTPClient http;  

    // Construye la cadena de datos a enviar
    String datos_a_enviar = "";
    
    // Agrega los datos I2C a la cadena de datos a enviar
    for (int i = 0; i < 11; i++) {
      datos_a_enviar += "park" + String(i + 1) + "=" + String(receivedData[i]);
      if (i < 10) {
        datos_a_enviar += "&";
      }
    }

    Serial.println("\nCADENA POST");
    Serial.println(datos_a_enviar);
    Serial.println("\n");

    //REALIZAMOS POST -----------------------------------------------------------------
    http.begin(urlServidorParkings);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int codigo_respuesta = http.POST(datos_a_enviar);


    if (codigo_respuesta > 0) {

      Serial.println("Código HTTP: " + String(codigo_respuesta));

      if (codigo_respuesta == 200) {
        String cuerpo_respuesta = http.getString();

        //RESPUESTAS DEL SERVIDOR
        Serial.println("El servidor respondió: ");
        Serial.println(cuerpo_respuesta);

        // Actualiza los valores anteriores después de enviar los datos
        for (int i = 0; i < 11; i++) {
          previousData[i] = receivedData[i];
        }

      }
    } else {
      Serial.print("Error al enviar POST, código: ");
      Serial.println(codigo_respuesta);
    }

    http.end();  // Liberar recursos

  } else {
     Serial.println("Error en la conexión WiFi");
  }
}

//======================================================================================
// POST DIRECCIÓN DEL SERVO
//======================================================================================

void sendDirection(const char* direction) {
  
  HTTPClient http;
  // Establece la URL del servidor
  http.begin(urlServidorDirection);

  // Configura la solicitud POST
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  String postPayload = "direction=" + String(direction);  // Envía la dirección como un parámetro

  // Realiza la solicitud POST
  int httpCode = http.POST(postPayload);

  if (httpCode > 0) {

    //Serial.printf("[HTTP] POST SERVO CON éxito, código: %d\n", httpCode);
    // Imprime la respuesta del servidor
    String response = http.getString();
    //Serial.println(response);

    //MOVIMIENTO DEL SERVO SEGÚN LA RESPUESTA
  

    if (response.equals("1")){

        //Wire.beginTransmission(I2C_ARDUINO_UNO_ADDR);
        //Wire.write(1); // Envía 1 al Arduino Uno
        //Wire.endTransmission();
        estadoServo = 1;
         Serial.println("ABIERTO");
      }
    else if(response.equals("2")){

        //Wire.beginTransmission(I2C_ARDUINO_UNO_ADDR);
        //Wire.write(2); // Envía 2 al Arduino Uno
        //Wire.endTransmission();
        estadoServo = 2;
        Serial.println("CERRADO");
      }
        //Serial.println("SIN MOVIMEINTO");
    
    
  } else {
    Serial.printf("[HTTP] POST SERVO fallido, código: %d\n", httpCode);
  }
  // Libera los recursos de HTTPClient
  http.end();
}


//======================================================================================
// LOOP
//======================================================================================

void loop() {
  WiFi.status();
  //Serial.println(WiFi.status());

  if (WiFi.status() == WL_CONNECTED) 
    {

      // ENVIO POST PARA SABER SI LA PUERTA ESTA ABIERTA O CERRADA
      sendDirection("holaMandameLadireccion");

    

      //SI LOS VALORES CAMBIAN ENVIO POST DE LOS ESTACIONAMIENTOS
      if (valoresHanCambiado())
        {
          EnvioDatos();
        }
    } 
  else 
    {
      Serial.println("Error en la conexión WiFi");
    }

  //Wire.beginTransmission(I2C_ARDUINO_UNO_ADDR);
  //Wire.write(2); // Envía 2 al Arduino Uno
  //Wire.endTransmission();
  delay(1000);
}
