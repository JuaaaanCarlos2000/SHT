#ifndef SHT21_H
#define SHT21_H //definir archivo SHT21

#include <Wire.h> //incluir librerías
#include <Arduino.h>
#define SHT21_DIRECCION 0x40 //dirección I2C para el sensor
#define TEMP_MEDIDA 0xF3 //dirección de medida de temperatura
#define HUMD_MEDIDA 0xF5 //dirección de medida de humedad

class SHT21 {
//definir variables
public:
SHT21();
void begin();
float obtenerTemperatura(void); //función obtener temperatura
float obtenerHumedad(void); //función obtener humedad
private:
uint16_t lecturaSHT21(uint8_t comando); //función leer al sensor
};
#endif
