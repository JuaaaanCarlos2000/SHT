#include <Wire.h>
#include "SHT21.h" //incluir librerías
SHT21::SHT21 () {}
void SHT21::begin(void){
Wire.begin();
}

float SHT21::obtenerHumedad(void) //función obtener humedad con la fórmula
del datasheet
{
return (-6.0 + 125.0 / 65536.0 * (float)(lecturaSHT21(HUMD_MEDIDA)));
}
float SHT21::obtenerTemperatura(void) //función obtener temperatura con la
fórmula del datasheet
{
return (-46.85 + 175.72 / 65536.0 * (float)(lecturaSHT21(TEMP_MEDIDA)));
}
uint16_t SHT21::lecturaSHT21(uint8_t comando) //función lectura del sensor
{
 uint16_t resultado;
 Wire.beginTransmission(SHT21_DIRECCION); //empieza la transmisión con
la dirección I2C
 Wire.write(comando); //escribimos comando
 Wire.endTransmission(); //terminamos transmisión
delay(100); //espera de 0.1 s
 Wire.requestFrom(SHT21_DIRECCION, 3); //solicita 3 bytes en la dirección de
I2C
 while(Wire.available() < 3) { //devuelve el número de bytes
 delay(1);
 }
 // devuelve el valor de result
 resultado = ((Wire.read()) << 8); // lectura los valores MSB y desplazamiento a
la izquierda (multiplicacion por 256)
 resultado += Wire.read(); //lectura de los valores LSB
resultado &= ~0x0003; //borra los dos bits LSB
 return resultado; //devuelve valor
}