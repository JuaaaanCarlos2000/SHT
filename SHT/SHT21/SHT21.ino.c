//Librerias
#include <Wire.h>
#include "SHT21.h"
SHT21 SHT21_start;
void setup()
{
 SHT21_start.begin();
 Serial.begin(9600); //transmisión de datos de 9600 baudios
}
void loop()
{
 Serial.print("Humedad(%RH): ");
 Serial.print(SHT21_start.obtenerHumedad()); //llamar función de obtener humedad
 Serial.print(" Temperatura(C): ");
 Serial.println(SHT21_start.obtenerTemperatura()); //llamar función de obtener temperatura

 delay(1000); //espera de 1 segundo entre valor y valor
}

