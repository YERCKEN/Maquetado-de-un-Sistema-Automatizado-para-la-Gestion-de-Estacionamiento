// ====================================== DEFINICIÓN   ===================================================

#include <Wire.h>
#include <NewPing.h>

// DIRECCIÓN ESP32
#define I2C_DEV_ADDR 0x55
// DIRECCIÓN ARDUINO UNO LCD
#define I2C_ARDUINO_UNO_ADDR 0x60


int receivedInt;
char estadoServo = '1';
// ================================ SENSPRES ULTRASÓNICOS ===============================================

// SENSOR #1 --------------------------------------------------------------
#define trigPin1 5  //BLANCO
#define echoPin1 6 // AZUL
#define ledSensor1 7 //VERDE

NewPing sonar1(trigPin1, echoPin1);
unsigned long tiempoInicio1 = 0;
bool objetoEnRango1 = false;
unsigned long tiempoParpadeo1 = 0;
bool parpadeo1 = false;

// SENSOR 2 ---------------------------------------------------------------
#define trigPin2 2 //NARANJA
#define echoPin2 3 //AZUL
#define ledSensor2 4 // AMARRILLo

NewPing sonar2(trigPin2, echoPin2);
unsigned long tiempoInicio2 = 0;
bool objetoEnRango2 = false;
unsigned long tiempoParpadeo2 = 0;
bool parpadeo2 = false;
bool permite0;

// SENSOR 3  ----------------------------------------------------------------
#define trigPin3 22 //BLANCO
#define echoPin3 24 // AZUL
#define ledSensor3 26 // AMARRILLo

NewPing sonar3(trigPin3, echoPin3);
unsigned long tiempoInicio3 = 0;
bool objetoEnRango3 = false;
unsigned long tiempoParpadeo3 = 0;
bool parpadeo3 = false;
bool permite03;

// SENSOR 4  ----------------------------------------------------------------
#define trigPin4 23 //BLANCO
#define echoPin4 25 // AZUL
#define ledSensor4 27 // AMARRILLo

NewPing sonar4(trigPin4, echoPin4);
unsigned long tiempoInicio4 = 0;
bool objetoEnRango4 = false;
unsigned long tiempoParpadeo4 = 0;
bool parpadeo4 = false;
bool permite04;


// SENSOR 5  ----------------------------------------------------------------
#define trigPin5 28 //BLANCO
#define echoPin5 30 // AZUL
#define ledSensor5 32 //NARANJA

NewPing sonar5(trigPin5, echoPin5);
unsigned long tiempoInicio5 = 0;
bool objetoEnRango5 = false;
unsigned long tiempoParpadeo5 = 0;
bool parpadeo5 = false;
bool permite05;

// SENSOR 6  ----------------------------------------------------------------
#define trigPin6 29 //BLANCO
#define echoPin6 31 // AZUL
#define ledSensor6 33 //AMARILLO

NewPing sonar6(trigPin6, echoPin6);
unsigned long tiempoInicio6 = 0;
bool objetoEnRango6 = false;
unsigned long tiempoParpadeo6 = 0;
bool parpadeo6 = false;
bool permite06;

// SENSOR 7  ----------------------------------------------------------------
#define echoPin7 35 // AZUL
#define trigPin7 37 //MORADO
#define ledSensor7 39 //GRIS

NewPing sonar7(trigPin7, echoPin7);
unsigned long tiempoInicio7 = 0;
bool objetoEnRango7 = false;
unsigned long tiempoParpadeo7 = 0;
bool parpadeo7 = false;
bool permite07;

// SENSOR 8  ----------------------------------------------------------------
#define echoPin8 34 // MORADO
#define trigPin8 36 //GRIS
#define ledSensor8 38 //BLANCO

NewPing sonar8(trigPin8, echoPin8);
unsigned long tiempoInicio8 = 0;
bool objetoEnRango8 = false;
unsigned long tiempoParpadeo8 = 0;
bool parpadeo8 = false;
bool permite08;

// SENSOR 9  ----------------------------------------------------------------
#define echoPin9 41 // MORADO
#define trigPin9 43 //GRIS
#define ledSensor9 45 //BLANCO

NewPing sonar9(trigPin9, echoPin9);
unsigned long tiempoInicio9 = 0;
bool objetoEnRango9 = false;
unsigned long tiempoParpadeo9 = 0;
bool parpadeo9 = false;
bool permite09;

// SENSOR 10  ----------------------------------------------------------------
#define echoPin10 40 // AZUL
#define trigPin10 42 // VERDE
#define ledSensor10 44 //AMARILLO

NewPing sonar10(trigPin10, echoPin10);
unsigned long tiempoInicio10 = 0;
bool objetoEnRango10 = false;
unsigned long tiempoParpadeo10 = 0;
bool parpadeo10 = false;
bool permite010;


// SENSOR 11  ----------------------------------------------------------------
#define echoPin11 48 // AZUL
#define trigPin11 50 // MORADO
#define ledSensor11 52 //GRIS

NewPing sonar11(trigPin11, echoPin11);
unsigned long tiempoInicio11 = 0;
bool objetoEnRango11 = false;
unsigned long tiempoParpadeo11 = 0;
bool parpadeo11 = false;
bool permite011;


// ================================ INFORMACIÓN A ENVIAR  ===============================================

uint8_t dataToSend[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t dataIndex = 0;
unsigned long previousMillis = 0;
const unsigned long interval = 1000; // 1 segundo


// ====================================== SETUP  =======================================================

void setup() {
  Serial.begin(115200);
  // Iniciamos la comunicación I2C
  Wire.begin();

  //MODO LEDS --------------------------
  pinMode(ledSensor1, OUTPUT);
  pinMode(ledSensor2, OUTPUT);
  pinMode(ledSensor3, OUTPUT);
  pinMode(ledSensor4, OUTPUT);
  pinMode(ledSensor5, OUTPUT);
  pinMode(ledSensor6, OUTPUT);
  pinMode(ledSensor7, OUTPUT);
  pinMode(ledSensor8, OUTPUT);
  pinMode(ledSensor9, OUTPUT);
  pinMode(ledSensor10, OUTPUT);
  pinMode(ledSensor11, OUTPUT);
}

// ======================================= LOPP =======================================================

void loop() {
  unsigned long currentMillis = millis();

  // Sensor 1 ----------------------------------------------------------------------------------------

  if (currentMillis - tiempoInicio1 >= 1000) 
    {
      unsigned int distance1 = sonar1.ping_cm();
      
      //VERIFIACIÓN DE DISTANCIA
      if (distance1 <= 10) 
        {
        if (!objetoEnRango1) 
          {
            objetoEnRango1 = true;
            tiempoInicio1 = currentMillis;
            Serial.print("\nComprobando si Hay un Auto en el Sensor 1 \n");
          }

        //COMPROBACIÓN SI HAN PASADO 5 SEGUNDOS
        if (currentMillis - tiempoInicio1 >= 5000) 
          {
            //Serial.print("\nEstacionamiento #1 OCUPADO ");
            //Serial.print(distance1);
            //Serial.print(" cm");
            digitalWrite(ledSensor1, HIGH);
            //OCUPADO
            dataToSend[0] = 1;
          } 
        //SI NO HAN PASADO 5 SEG Y NO A SALIDO DEL RANGO 
        else 
          {
            // PARPADEO DE LA LED
            if (currentMillis - tiempoParpadeo1 >= 100) 
              {
                tiempoParpadeo1 = currentMillis;
                Serial.print(".");
                if (parpadeo1) 
                  {
                    digitalWrite(ledSensor1, LOW);
                  } 
                else 
                  {
                    digitalWrite(ledSensor1, HIGH);
                  }
                parpadeo1 = !parpadeo1;
              }
          }
      } 
      //FUERA DE RANGO
      else 
        {
          objetoEnRango1 = false;
          digitalWrite(ledSensor1, LOW);
          //estacionamiento VACÍO
          dataToSend[0] = 0;
        }
    }
  
  // Sensor 2 ----------------------------------------------------------------------------------------

  if (currentMillis - tiempoInicio2 >= 1000) 
    {
      unsigned int distance2 = sonar2.ping_cm();

      //VERIFIACIÓN DE DISTANCIA
      if ( distance2 <= 10) 
        {

          //VERIFIACIÓN DE DISTANCIA EXTRA esto por los errores falsos del sensor
          if (distance2 > 0)
            {
              permite0 = true;
              //Serial.print("\nPERMITE = SI \n");
            }
          else
            {
              permite0 = false;
              //Serial.print("  PERMITE = NO, SALIMOS \n");
            }

          //SI SE PERMITE EL 0 FALSO COMPROBAMOS 
          if (permite0 == true)
            {   
                //SI ESTÁ EN EL RANGO
                if (!objetoEnRango2) 
                  {
                    objetoEnRango2 = true;
                    tiempoInicio2 = currentMillis;
                    Serial.print("\nComprobando si Hay un Auto en el Sensor 2 \n");
                  }

                //SI HAN PASADO 5 SEGUNDOS DE COMPROBACIÓN
                if (currentMillis - tiempoInicio2 >= 5000) 
                  {
                      //Serial.print("\nEstacionamiento #2 OCUPADO ");
                      //Serial.print(distance2);
                      //Serial.print(" cm");
                      digitalWrite(ledSensor2, HIGH);
                      //OCUPAMOS EL ESTACIONAMIENTO
                      dataToSend[1] = 1;
                  }
                else 
                  {
                      if (currentMillis - tiempoParpadeo2 >= 100) 
                        {
                          tiempoParpadeo2 = currentMillis;
                          Serial.print(".");
                          if (parpadeo2) 
                            {
                              digitalWrite(ledSensor2, LOW);
                            } 
                          else 
                            {
                              digitalWrite(ledSensor2, HIGH);
                            }
                          parpadeo2 = !parpadeo2;
                        }
                  }
            }
          //SI YA EL 0 NO ES FALSO
          else
            {
              //Serial.print("  PERMITE = NO, SALIMOS \n");
            }

        } 
      //SI SALIÓ DEL RANGO O NO ESTÁ 
      else 
        {
          objetoEnRango2 = false;
          digitalWrite(ledSensor2, LOW);
          //ESTABLECEMOS ESTACIONAMIENTO VACÍO
          dataToSend[1] = 0;
          //Serial.write("\n Estacionmaiento #2 Abandonado");
        }
    }

  // Sensor 3 ------------------------------------------------------------------------------------------

  if (currentMillis - tiempoInicio3 >= 1000) 
    {
      unsigned int distance3 = sonar3.ping_cm();

      //VERIFIACIÓN DE DISTANCIA
      if (distance3 <= 10) 
        {
          //VERIFIACIÓN DE DISTANCIA EXTRA esto por los errores falsos del sensor
          if (distance3 > 0) 
            {
              permite03 = true;
            } 
          else 
            {
              permite03 = false;
            }

          //SI SE PERMITE EL 0 FALSO COMPROBAMOS 
          if (permite03 == true) 
            {
              //SI ESTÁ EN EL RANGO
              if (!objetoEnRango3) 
                {
                  objetoEnRango3 = true;
                  tiempoInicio3 = currentMillis;
                  Serial.print("\nComprobando si Hay un Auto en el Sensor 3 \n");
                }

              //SI HAN PASADO 5 SEGUNDOS DE COMPROBACIÓN
              if (currentMillis - tiempoInicio3 >= 5000) 
                {
                  
                  //Serial.print("\nEstacionamiento #2 OCUPADO ");
                  //Serial.print(distance3);
                  //Serial.print(" cm");
                  digitalWrite(ledSensor3, HIGH);
                  dataToSend[2] = 1; // Establece el tercer valor en 1 cuando el estacionamiento #3 está ocupado
                } 
              else 
                {
                  if (currentMillis - tiempoParpadeo3 >= 100) 
                    {
                      tiempoParpadeo3 = currentMillis;
                      Serial.print(".");
                      if (parpadeo3) 
                        {
                          digitalWrite(ledSensor3, LOW);
                        } 
                      else
                        {
                          digitalWrite(ledSensor3, HIGH);
                        }
                      parpadeo3 = !parpadeo3;
                    }
                }
            } 
          //SI YA EL 0 NO ES FALSO
          else
            {
                //Serial.print("  PERMITE = NO, SALIMOS \n");
            }
        }
      //SI SALIÓ DEL RANGO O NO ESTÁ 
      else 
        {
          objetoEnRango3 = false;
          digitalWrite(ledSensor3, LOW);
          dataToSend[2] = 0; // Establece el tercer valor en 0 cuando el estacionamiento está vacío
        }
    }

  // Sensor 4 ------------------------------------------------------------------------------------------
  if (currentMillis - tiempoInicio4 >= 1000) 
    {
      unsigned int distance4 = sonar4.ping_cm();

      //VERIFIACIÓN DE DISTANCIA
      if (distance4 <= 10) 
        {
          //VERIFIACIÓN DE DISTANCIA EXTRA esto por los errores falsos del sensor
          if (distance4 > 0) 
            {
              permite04 = true;
            } 
          else 
            {
              permite04 = false;
            }

          //SI SE PERMITE EL 0 FALSO COMPROBAMOS 
          if (permite04 == true) 
            {
              //SI ESTÁ EN EL RANGO
              if (!objetoEnRango4) 
                {
                  objetoEnRango4 = true;
                  tiempoInicio4 = currentMillis;
                  Serial.print("\nComprobando si Hay un Auto en el Sensor 4 \n");
                }

              //SI HAN PASADO 5 SEGUNDOS DE COMPROBACIÓN
              if (currentMillis - tiempoInicio4 >= 5000) 
                {
                  
                  //Serial.print("\nEstacionamiento #2 OCUPADO ");
                  //Serial.print(distance4);
                  //Serial.print(" cm");
                  digitalWrite(ledSensor4, HIGH);
                  dataToSend[3] = 1; // Establece el tercer valor en 1 cuando el estacionamiento #4 está ocupado
                } 
              else 
                {
                  if (currentMillis - tiempoParpadeo4 >= 100) 
                    {
                      tiempoParpadeo4 = currentMillis;
                      Serial.print(".");
                      if (parpadeo4) 
                        {
                          digitalWrite(ledSensor4, LOW);
                        } 
                      else
                        {
                          digitalWrite(ledSensor4, HIGH);
                        }
                      parpadeo4 = !parpadeo4;
                    }
                }
            } 
          //SI YA EL 0 NO ES FALSO
          else
            {
                //Serial.print("  PERMITE = NO, SALIMOS \n");
            }
        }
      //SI SALIÓ DEL RANGO O NO ESTÁ 
      else 
        {
          objetoEnRango4 = false;
          digitalWrite(ledSensor4, LOW);
          dataToSend[3] = 0; // Establece el tercer valor en 0 cuando el estacionamiento está vacío
        }
    }

  // Sensor 5 ------------------------------------------------------------------------------------------
  if (currentMillis - tiempoInicio5 >= 1000) 
    {
      unsigned int distance5 = sonar5.ping_cm();

      //VERIFIACIÓN DE DISTANCIA
      if (distance5 <= 10) 
        {
          //VERIFIACIÓN DE DISTANCIA EXTRA esto por los errores falsos del sensor
          if (distance5 > 0) 
            {
              permite05 = true;
            } 
          else 
            {
              permite05 = false;
            }

          //SI SE PERMITE EL 0 FALSO COMPROBAMOS 
          if (permite05 == true) 
            {
              //SI ESTÁ EN EL RANGO
              if (!objetoEnRango5) 
                {
                  objetoEnRango5 = true;
                  tiempoInicio5 = currentMillis;
                  Serial.print("\nComprobando si Hay un Auto en el Sensor 5 \n");
                }

              //SI HAN PASADO 5 SEGUNDOS DE COMPROBACIÓN
              if (currentMillis - tiempoInicio5 >= 5000) 
                {
                  
                  //Serial.print("\nEstacionamiento #2 OCUPADO ");
                  //Serial.print(distance4);
                  //Serial.print(" cm");
                  digitalWrite(ledSensor5, HIGH);
                  dataToSend[4] = 1; // Establece el tercer valor en 1 cuando el estacionamiento #4 está ocupado
                } 
              else 
                {
                  if (currentMillis - tiempoParpadeo5 >= 100) 
                    {
                      tiempoParpadeo5 = currentMillis;
                      Serial.print(".");
                      if (parpadeo5) 
                        {
                          digitalWrite(ledSensor5, LOW);
                        } 
                      else
                        {
                          digitalWrite(ledSensor5, HIGH);
                        }
                      parpadeo5 = !parpadeo5;
                    }
                }
            } 
          //SI YA EL 0 NO ES FALSO
          else
            {
                //Serial.print("  PERMITE = NO, SALIMOS \n");
            }
        }
      //SI SALIÓ DEL RANGO O NO ESTÁ 
      else 
        {
          objetoEnRango5 = false;
          digitalWrite(ledSensor5, LOW);
          dataToSend[4] = 0; // Establece el tercer valor en 0 cuando el estacionamiento está vacío
        }
    }

  // Sensor 6 ------------------------------------------------------------------------------------------
  if (currentMillis - tiempoInicio6 >= 1000) 
    {
      unsigned int distance6 = sonar6.ping_cm();

      //VERIFIACIÓN DE DISTANCIA
      if (distance6 <= 10) 
        {
          //VERIFIACIÓN DE DISTANCIA EXTRA esto por los errores falsos del sensor
          if (distance6 > 0) 
            {
              permite06 = true;
            } 
          else 
            {
              permite06 = false;
            }

          //SI SE PERMITE EL 0 FALSO COMPROBAMOS 
          if (permite06 == true) 
            {
              //SI ESTÁ EN EL RANGO
              if (!objetoEnRango6) 
                {
                  objetoEnRango6 = true;
                  tiempoInicio6 = currentMillis;
                  Serial.print("\nComprobando si Hay un Auto en el Sensor 6 \n");
                }

              //SI HAN PASADO 5 SEGUNDOS DE COMPROBACIÓN
              if (currentMillis - tiempoInicio6 >= 5000) 
                {
                  
                  //Serial.print("\nEstacionamiento #2 OCUPADO ");
                  //Serial.print(distance4);
                  //Serial.print(" cm");
                  digitalWrite(ledSensor6, HIGH);
                  dataToSend[5] = 1; // Establece el tercer valor en 1 cuando el estacionamiento #4 está ocupado
                } 
              else 
                {
                  if (currentMillis - tiempoParpadeo6 >= 100) 
                    {
                      tiempoParpadeo6 = currentMillis;
                      Serial.print(".");
                      if (parpadeo6) 
                        {
                          digitalWrite(ledSensor6, LOW);
                        } 
                      else
                        {
                          digitalWrite(ledSensor6, HIGH);
                        }
                      parpadeo6 = !parpadeo6;
                    }
                }
            } 
          //SI YA EL 0 NO ES FALSO
          else
            {
                //Serial.print("  PERMITE = NO, SALIMOS \n");
            }
        }
      //SI SALIÓ DEL RANGO O NO ESTÁ 
      else 
        {
          objetoEnRango6 = false;
          digitalWrite(ledSensor6, LOW);
          dataToSend[5] = 0; // Establece el tercer valor en 0 cuando el estacionamiento está vacío
        }
    }

  // Sensor 7 ------------------------------------------------------------------------------------------
  if (currentMillis - tiempoInicio7 >= 1000) 
    {
      unsigned int distance7 = sonar7.ping_cm();

      //VERIFIACIÓN DE DISTANCIA
      if (distance7 <= 10) 
        {
          //VERIFIACIÓN DE DISTANCIA EXTRA esto por los errores falsos del sensor
          if (distance7 > 0) 
            {
              permite07 = true;
            } 
          else 
            {
              permite07 = false;
            }

          //SI SE PERMITE EL 0 FALSO COMPROBAMOS 
          if (permite07 == true) 
            {
              //SI ESTÁ EN EL RANGO
              if (!objetoEnRango7) 
                {
                  objetoEnRango7 = true;
                  tiempoInicio7 = currentMillis;
                  Serial.print("\nComprobando si Hay un Auto en el Sensor 7 \n");
                }

              //SI HAN PASADO 5 SEGUNDOS DE COMPROBACIÓN
              if (currentMillis - tiempoInicio7 >= 5000) 
                {
                  
                  //Serial.print("\nEstacionamiento #2 OCUPADO ");
                  //Serial.print(distance4);
                  //Serial.print(" cm");
                  digitalWrite(ledSensor7, HIGH);
                  dataToSend[6] = 1; // Establece el tercer valor en 1 cuando el estacionamiento #4 está ocupado
                } 
              else 
                {
                  if (currentMillis - tiempoParpadeo7 >= 100) 
                    {
                      tiempoParpadeo7 = currentMillis;
                      Serial.print(".");
                      if (parpadeo7) 
                        {
                          digitalWrite(ledSensor7, LOW);
                        } 
                      else
                        {
                          digitalWrite(ledSensor7, HIGH);
                        }
                      parpadeo7 = !parpadeo7;
                    }
                }
            } 
          //SI YA EL 0 NO ES FALSO
          else
            {
                //Serial.print("  PERMITE = NO, SALIMOS \n");
            }
        }
      //SI SALIÓ DEL RANGO O NO ESTÁ 
      else 
        {
          objetoEnRango7 = false;
          digitalWrite(ledSensor7, LOW);
          dataToSend[6] = 0; // Establece el tercer valor en 0 cuando el estacionamiento está vacío
        }
    }

  // Sensor 8 ------------------------------------------------------------------------------------------
  if (currentMillis - tiempoInicio8 >= 1000) 
    {
      unsigned int distance8 = sonar8.ping_cm();

      //VERIFIACIÓN DE DISTANCIA
      if (distance8 <= 10) 
        {
          //VERIFIACIÓN DE DISTANCIA EXTRA esto por los errores falsos del sensor
          if (distance8 > 0) 
            {
              permite08 = true;
            } 
          else 
            {
              permite08 = false;
            }

          //SI SE PERMITE EL 0 FALSO COMPROBAMOS 
          if (permite08 == true) 
            {
              //SI ESTÁ EN EL RANGO
              if (!objetoEnRango8) 
                {
                  objetoEnRango8 = true;
                  tiempoInicio8 = currentMillis;
                  Serial.print("\nComprobando si Hay un Auto en el Sensor 8 \n");
                }

              //SI HAN PASADO 5 SEGUNDOS DE COMPROBACIÓN
              if (currentMillis - tiempoInicio8 >= 5000) 
                {
                  
                  //Serial.print("\nEstacionamiento #2 OCUPADO ");
                  //Serial.print(distance4);
                  //Serial.print(" cm");
                  digitalWrite(ledSensor8, HIGH);
                  dataToSend[7] = 1; // Establece el tercer valor en 1 cuando el estacionamiento #4 está ocupado
                } 
              else 
                {
                  if (currentMillis - tiempoParpadeo8 >= 100) 
                    {
                      tiempoParpadeo8 = currentMillis;
                      Serial.print(".");
                      if (parpadeo8) 
                        {
                          digitalWrite(ledSensor8, LOW);
                        } 
                      else
                        {
                          digitalWrite(ledSensor8, HIGH);
                        }
                      parpadeo8 = !parpadeo8;
                    }
                }
            } 
          //SI YA EL 0 NO ES FALSO
          else
            {
                //Serial.print("  PERMITE = NO, SALIMOS \n");
            }
        }
      //SI SALIÓ DEL RANGO O NO ESTÁ 
      else 
        {
          objetoEnRango8 = false;
          digitalWrite(ledSensor8, LOW);
          dataToSend[7] = 0; // Establece el tercer valor en 0 cuando el estacionamiento está vacío
        }
    }
  
  // Sensor 9 ------------------------------------------------------------------------------------------
  if (currentMillis - tiempoInicio9 >= 1000) 
    {
      unsigned int distance9 = sonar9.ping_cm();

      //VERIFIACIÓN DE DISTANCIA
      if (distance9 <= 10) 
        {
          //VERIFIACIÓN DE DISTANCIA EXTRA esto por los errores falsos del sensor
          if (distance9 > 0) 
            {
              permite09 = true;
            } 
          else 
            {
              permite09 = false;
            }

          //SI SE PERMITE EL 0 FALSO COMPROBAMOS 
          if (permite09 == true) 
            {
              //SI ESTÁ EN EL RANGO
              if (!objetoEnRango9) 
                {
                  objetoEnRango9 = true;
                  tiempoInicio9 = currentMillis;
                  Serial.print("\nComprobando si Hay un Auto en el Sensor 9 \n");
                }

              //SI HAN PASADO 5 SEGUNDOS DE COMPROBACIÓN
              if (currentMillis - tiempoInicio9 >= 5000) 
                {
                  
                  //Serial.print("\nEstacionamiento #2 OCUPADO ");
                  //Serial.print(distance4);
                  //Serial.print(" cm");
                  digitalWrite(ledSensor9, HIGH);
                  dataToSend[8] = 1; // Establece el tercer valor en 1 cuando el estacionamiento #4 está ocupado
                } 
              else 
                {
                  if (currentMillis - tiempoParpadeo9 >= 100) 
                    {
                      tiempoParpadeo9 = currentMillis;
                      Serial.print(".");
                      if (parpadeo9) 
                        {
                          digitalWrite(ledSensor9, LOW);
                        } 
                      else
                        {
                          digitalWrite(ledSensor9, HIGH);
                        }
                      parpadeo9 = !parpadeo9;
                    }
                }
            } 
          //SI YA EL 0 NO ES FALSO
          else
            {
                //Serial.print("  PERMITE = NO, SALIMOS \n");
            }
        }
      //SI SALIÓ DEL RANGO O NO ESTÁ 
      else 
        {
          objetoEnRango9 = false;
          digitalWrite(ledSensor9, LOW);
          dataToSend[8] = 0; // Establece el tercer valor en 0 cuando el estacionamiento está vacío
        }
    }

  // Sensor 10  ------------------------------------------------------------------------------------------
  if (currentMillis - tiempoInicio10 >= 1000) 
    {
      unsigned int distance10 = sonar10.ping_cm();

      //VERIFIACIÓN DE DISTANCIA
      if (distance10 <= 10) 
        {
          //VERIFIACIÓN DE DISTANCIA EXTRA esto por los errores falsos del sensor
          if (distance10 > 0) 
            {
              permite010 = true;
            } 
          else 
            {
              permite010 = false;
            }

          //SI SE PERMITE EL 0 FALSO COMPROBAMOS 
          if (permite010 == true) 
            {
              //SI ESTÁ EN EL RANGO
              if (!objetoEnRango10) 
                {
                  objetoEnRango10 = true;
                  tiempoInicio10 = currentMillis;
                  Serial.print("\nComprobando si Hay un Auto en el Sensor 10 \n");
                }

              //SI HAN PASADO 5 SEGUNDOS DE COMPROBACIÓN
              if (currentMillis - tiempoInicio10 >= 5000) 
                {
                  
                  //Serial.print("\nEstacionamiento #2 OCUPADO ");
                  //Serial.print(distance4);
                  //Serial.print(" cm");
                  digitalWrite(ledSensor10, HIGH);
                  dataToSend[9] = 1; // Establece el tercer valor en 1 cuando el estacionamiento #4 está ocupado
                } 
              else 
                {
                  if (currentMillis - tiempoParpadeo10 >= 100) 
                    {
                      tiempoParpadeo10 = currentMillis;
                      Serial.print(".");
                      if (parpadeo10) 
                        {
                          digitalWrite(ledSensor10, LOW);
                        } 
                      else
                        {
                          digitalWrite(ledSensor10, HIGH);
                        }
                      parpadeo10 = !parpadeo10;
                    }
                }
            } 
          //SI YA EL 0 NO ES FALSO
          else
            {
                //Serial.print("  PERMITE = NO, SALIMOS \n");
            }
        }
      //SI SALIÓ DEL RANGO O NO ESTÁ 
      else 
        {
          objetoEnRango10 = false;
          digitalWrite(ledSensor10, LOW);
          dataToSend[9] = 0; // Establece el tercer valor en 0 cuando el estacionamiento está vacío
        }
    }

  // Sensor 11  ------------------------------------------------------------------------------------------
  if (currentMillis - tiempoInicio11 >= 1000) 
    {
      unsigned int distance11 = sonar11.ping_cm();

      //VERIFIACIÓN DE DISTANCIA
      if (distance11 <= 10) 
        {
          //VERIFIACIÓN DE DISTANCIA EXTRA esto por los errores falsos del sensor
          if (distance11 > 0) 
            {
              permite011 = true;
            } 
          else 
            {
              permite011 = false;
            }

          //SI SE PERMITE EL 0 FALSO COMPROBAMOS 
          if (permite011 == true) 
            {
              //SI ESTÁ EN EL RANGO
              if (!objetoEnRango11) 
                {
                  objetoEnRango11 = true;
                  tiempoInicio11 = currentMillis;
                  Serial.print("\nComprobando si Hay un Auto en el Sensor 11 \n");
                }

              //SI HAN PASADO 5 SEGUNDOS DE COMPROBACIÓN
              if (currentMillis - tiempoInicio11 >= 5000) 
                {
                  
                  //Serial.print("\nEstacionamiento #2 OCUPADO ");
                  //Serial.print(distance4);
                  //Serial.print(" cm");
                  digitalWrite(ledSensor11, HIGH);
                  dataToSend[10] = 1; // Establece el tercer valor en 1 cuando el estacionamiento #4 está ocupado
                } 
              else 
                {
                  if (currentMillis - tiempoParpadeo11 >= 100) 
                    {
                      tiempoParpadeo11 = currentMillis;
                      Serial.print(".");
                      if (parpadeo11) 
                        {
                          digitalWrite(ledSensor11, LOW);
                        } 
                      else
                        {
                          digitalWrite(ledSensor11, HIGH);
                        }
                      parpadeo11 = !parpadeo11;
                    }
                }
            } 
          //SI YA EL 0 NO ES FALSO
          else
            {
                //Serial.print("  PERMITE = NO, SALIMOS \n");
            }
        }
      //SI SALIÓ DEL RANGO O NO ESTÁ 
      else 
        {
          objetoEnRango11 = false;
          digitalWrite(ledSensor11, LOW);
          dataToSend[10] = 0; // Establece el tercer valor en 0 cuando el estacionamiento está vacío
        }
    }
  
  //ENVIO DE DATOS POR I2C ----------------------------------------------------------------------

  if (currentMillis - previousMillis >= interval) 
    {
      previousMillis = currentMillis;

      // ESP32 I2C -----------------------------------------------------
      Wire.beginTransmission(I2C_DEV_ADDR);
      for (int i = 0; i < 11; i++) 
        {
          Wire.write(dataToSend[i]);
        }
      uint8_t error = Wire.endTransmission();
      Serial.print("EndTransmision ESP32: ");
      Serial.println(error);
      
      // Read 16 bytes from the slave
      Wire.requestFrom(I2C_DEV_ADDR, 1);
      Serial.print("requestFrom: ");
      Serial.println(Wire.available());
      
      while (Wire.available()) {
        estadoServo = Wire.read();
        Serial.print(estadoServo);
      }
      Serial.print("\n");

      //MANDAMOS ESTADO DE LA PUERTA
      if (estadoServo == '1')
        {
            Serial.println("ABIERTO");
            dataToSend[11] = 1;
        }
      else if (estadoServo == '2') 
        {
          Serial.println("CERRADO");
          dataToSend[11] = 2;
        }

      // ARDUINO UNO LCD I2C -----------------------------------------------------
      Wire.beginTransmission(I2C_ARDUINO_UNO_ADDR);
      for (int i = 0; i < 12; i++) 
        {
          Wire.write(dataToSend[i]);
        }
      error = Wire.endTransmission();
      Serial.print("EndTransmision Arduino Uno: ");
      Serial.println(error);



    }
}
