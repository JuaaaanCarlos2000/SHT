#include<SHT25.h>
#include<Wire.h>
SHT25::SHT25(void){
}
//llamada al reinicio del sensor
char SHT25::begin(void){
 Wire.begin();
 if(reinicioSensor()){
 return 1;
 }else{return 0;}
}
//reinicio sensor
char SHT25::reinicioSensor(void){
 Wire.beginTransmission(SHT25_direccion); //modo start
 Wire.write(REINICIO); //reinicio sensor
 char error = Wire.endTransmission();
 if(error == 0){
 delay(15); //espera para reinicio sensor
 return 1;
 }else{return 0;}
}
//función de obtención de humedad
float SHT25::obtenerHumedad(void){
 if(lecturaBytes(HUMEDAD, S_RH, 3, DIRECCION_HUMEDAD)){
 RH = -6.0 + 125.0*(S_RH/((long)1<<16)); //fórmula humedad relativa
 return RH;
 }else{return RH_ERROR;}
}
//función de obtención de temperatura

float SHT25::obtenerTemperatura(){
 if(lecturaBytes(TEMPERATURA, S_T, 3, DIRECCION_TEMPERATURA)){
 TEMP = -46.85 + 175.72*(S_T/((long)1<<16)); //fórmula temperatura
 return TEMP;
 }else{return T_ERROR;}
}
//lectura de bytes
char SHT25::lecturaBytes(char CMD, float &valor, char numerolongitud, char
parametro){
 unsigned char data[numerolongitud];
 Wire.beginTransmission(SHT25_direccion); //start
 Wire.write(CMD);
 char error = Wire.endTransmission(); //fin
 if(parametro){
 delay(RH_Delay); //espera
 }else{delay(T_Delay);}
 if(error == 0){
 Wire.requestFrom(SHT25_direccion, numerolongitud); //solicita los bytes de start
 while (!Wire.available());
 for(char x=0; x<numerolongitud; x++){
 data[x] = Wire.read(); //lectura de datos recibidos
 x++;
 }
//primero se obtienen los valores MSB y se desplazan hacia la izquierda (MSB)
//y después se obtienen los valores LSB y se desplazan 2 posiciones a la izquierda
//porque los dos valores de la derecha (LSB) están reservados
 valor = (float)((unsigned int)data[0]*((int)1<<8) + (unsigned
int)(data[1]&((int)1<<2)));
 return 1;
 }else{return 0;}
}
//lectura de un solo byte
char SHT25::lecturaByte(char CMD, byte &valor){
 Wire.beginTransmission(SHT25_direccion); //start
 Wire.write(CMD);
 char error = Wire.endTransmission(); //fin

 if(error == 0){
 Wire.requestFrom(SHT25_direccion,1); //solicita un solo byte
 while (!Wire.available()) {
 valor = Wire.read();
 }
 return 1;
 }else{return 0;}
}
//escritura de bytes
char SHT25::escrituraByte(char CMD, byte regDatos){
 Wire.beginTransmission(SHT25_direccion); //start
 Wire.write(CMD);
 Wire.write(regDatos); //escritura del registro para la resolución
 char error = Wire.endTransmission(); //fin
 if(error == 0){
 return 1;
 }else{return 0;}
}
//configuración de la resolución
char SHT25::Resolucion(byte combinacion){
 byte regDatos, valor;
 switch (combinacion) {
 case 1: //RH-12bit, T-14bit
 this->T_Delay = 85; //delay
 this->RH_Delay = 29;
 regDatos = 0x02; //direccion para estas resoluciones
 break;
 case 2: //RH-8bit, T-12bit
 this->T_Delay = 22; //delay
 this->RH_Delay = 4;
 regDatos = 0x03; //direccion para estas resoluciones
 break;
 case 3: //RH-10bit, T-13bit
 this->T_Delay = 43; //delay
 this->RH_Delay = 9;
 regDatos = 0x82; //direccion para estas resoluciones
 break;
 case 4: //RH-11bit, T-11bit

 this->T_Delay = 11; //delay
 this->RH_Delay = 15;
 regDatos = 0x83; //direccion para estas resoluciones
 break;
 default:
 break;
 }
 if(escrituraByte(LECTURA, valor)){
 regDatos |= (valor & 0x7E); //nos aseguramos la direccion de la resolución y
obtenemos el valor obtenido
 if(escrituraByte(ESCRITURA, regDatos)){
 return 1;
 }else{return 0;}
 }else{return 0;}
}
//activamos heater
char SHT25::HabilitarHeater(void){
 byte valor, data;
 if(lecturaByte(LECTURA, valor)){
 data = (valor & 0xFB) | 0x04; //encendemos el heater con la direccion de este
 if(escrituraByte(ESCRITURA, data)){
 return 1;
 } else{return 0;}
 }else{return 0;}
}
//desactivamos heater
char SHT25::DeshabilitarHeater(void){
 byte valor, data;
 if(lecturaByte(LECTURA, valor)){
 data = (valor & 0xFB); //desactivamos heater con la direccion de este
 if(escrituraByte(ESCRITURA, data)){
 return 1;
 } else{return 0;}
 }else{return 0;}
}

char SHT25::bateria(void){
 byte valor;
 if(lecturaByte(LECTURA, valor)){
 valor &= 0x40; //reiniciamos sensor con la direccion de start
 if(valor == 0x40){
 return 1;
 } else{return 0;}
 }else{return 0;}
}
