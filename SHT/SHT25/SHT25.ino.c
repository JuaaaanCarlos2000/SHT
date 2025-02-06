//Librerias
#include<SHT25.h>
SHT25 SHT25_start;
void setup(void){
 Serial.begin(9600); // velocidad de comunicación 9600 baudios
 if(SHT25_start.begin()){
 Serial.println("Inicialización del SHT25 completada!");
 }else{
 Serial.println("Inicialización interrumpida!");
 }
 // byte combi= ; //Definir resolución del SHT25 si es necesario o preciso
 // SHT25_start.Resolucion(combi); //Cambiar resolución en la función
 // Serial.print("Resolucion: ");
 // Serial.print(combi); //mostrar por pantalla la resolución escogida
}
void loop(void){
 Serial.print("Humedad : ");
 Serial.print(SHT25_start.obtenerHumedad()); //llamar función de obtener humedad
 Serial.println(" %RH");
 Serial.print("Temperatura : ");
 Serial.print(SHT25_start.obtenerTemperatura()); //llamar función de obtener temperatura
 Serial.println(" C");
 delay(1000); //espera de 1 segundo entre valor y valor
}