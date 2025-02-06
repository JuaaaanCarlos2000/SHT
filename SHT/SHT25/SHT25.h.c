#include <Arduino.h>
//Definimos variables constantes (direcciones) que iremos utilizando
#define TEMPERATURA 0xF3 //direccion de medida de temperatura
#define HUMEDAD 0xF5 //direccion de medida de humedad
#define ESCRITURA 0xE6 //direccion de usuario de registro de escritura
#define LECTURA 0xE7 //direccion de usuario de registro de lectura
#define REINICIO 0xFE //direccion de reinicio
//definimos si es humedad o temperatura
#define DIRECCION_HUMEDAD 0x01 //humedad
#define DIRECCION_TEMPERATURA 0x00 //temperatura

//definimos variables dentro de una plantilla de creación de objetos
class SHT25{
 public:
 SHT25(void);
 char begin(void);
 char Resolucion(byte combinacion); // configuracion de la resolución
 char HabilitarHeater(void); //configuracion del heater
 char DeshabilitarHeater(void);
 float obtenerTemperatura(void); //función para obtener la temperatura
 float obtenerHumedad(void); //función para obtener la humedad
 char bateria(void); //función para end-bateria
 const float RH_ERROR = 101.0,T_ERROR = 126.0; //error
 private:
 const byte SHT25_direccion = 0x40; //dirección sensor
 byte T_Delay = 85; // para resolución de 14 bit
 byte RH_Delay = 29; // para resolución de 12 bit
 float TEMP, RH, S_T, S_RH; //variables generales
 char reinicioSensor(void); //reinicio sensor
 char lecturaBytes(char CMD, float &valor, char numerolongitud, char parametro); //lectura
de bytes

 char lecturaByte(char CMD, byte &valor); //lectura de un byte
 char escrituraByte(char CMD, byte regDatos); //escritura de un byte
};