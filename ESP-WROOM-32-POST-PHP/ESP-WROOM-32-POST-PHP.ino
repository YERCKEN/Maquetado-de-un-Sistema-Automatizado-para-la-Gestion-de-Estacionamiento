#include <HTTPClient.h>
#include <WiFi.h>

const char* ssid = "CWC-7986324-2.4";      // SSID de tu red Wi-Fi
const char* password = "snns7pdTxnkw";  // Contraseña de tu red Wi-Fi
int temperatura = 11;


//ESTACIONAMIENTOS
int park1, park2, park3, park4, park5, park6, park7, park8, park9, park10, park11;

// DEFINICIÓN VALORES PARKING

void valoresPark (){

  park1 = 0;
  park2 = 0;
  park3 = 0;
  park4 = 0;
  park5 = 0;
  park6 = 1;
  park7 = 0;
  park8 = 0;
  park9 = 1;
  park10 = 0;
  park11 = 0;
}

//SETUP -==================================================================================

void setup() {
  Serial.begin(115200);
  Serial.println(F("ESP32 SEND DATA TO PHP SERVER"));
  
  WiFi.begin(ssid, password);
  Serial.print("Conectando...");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  //definición valores park
  valoresPark ();

  Serial.println("Conexión OK!");
  Serial.print("IP Local: ");
  Serial.println(WiFi.localIP());
}

//ENVIO DE DATOS -==================================================================================

void EnvioDatos() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;  // Crear objeto HTTP

    // Obtener datos a enviar
    // Obtener datos a enviar solo para park1 a park11
    String datos_a_enviar = "park1=" + String(park1);
    datos_a_enviar += "&park2=" + String(park2);
    datos_a_enviar += "&park3=" + String(park3);
    datos_a_enviar += "&park4=" + String(park4);
    datos_a_enviar += "&park5=" + String(park5);
    datos_a_enviar += "&park6=" + String(park6);
    datos_a_enviar += "&park7=" + String(park7);
    datos_a_enviar += "&park8=" + String(park8);
    datos_a_enviar += "&park9=" + String(park9);
    datos_a_enviar += "&park10=" + String(park10);
    datos_a_enviar += "&park11=" + String(park11);


    Serial.println(datos_a_enviar);


    http.begin("http://phppasarvariable.000webhostapp.com/esp-post.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    int codigo_respuesta = http.POST(datos_a_enviar);

    if (codigo_respuesta > 0) {
      Serial.println("Código HTTP: " + String(codigo_respuesta));
      if (codigo_respuesta == 200) {
        String cuerpo_respuesta = http.getString();
        Serial.println("El servidor respondió: ");
        Serial.println(cuerpo_respuesta);
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

//LOOP -==================================================================================

void loop() {
  WiFi.status();
  Serial.println(WiFi.status());
  
  if (WiFi.status() == WL_CONNECTED) {
    EnvioDatos(); // Llama a la función EnvioDatos
  } else {
    Serial.println("Error en la conexión WiFi");
  }

  delay(2000);
}
