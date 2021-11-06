#include <OneWire.h>
#include <DallasTemperature.h>  //Librerias para controlar el sensor de temperatura DS18B20
#include <SoftwareSerial.h>     //Liberia que se encarga de interpretar los comandos AT/GSM en arduino y SIM900

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//En esta área declaras los pines con los cuales enviaras o recibiras datos de los sensores.
//De igual manera aquí instancias los "objetos" de asi requerirlo el sensor.

SoftwareSerial SIM900(7,8);     //Se declaran los pines encargados de la comunicación entre el SIM900 y arduino
 
const int pinDatosDQ = 9;       //Se declarar el pin receptor de datos del sensor de temperatura
 
//Instancia a las clases OneWire y DallasTemperature
OneWire oneWireObjeto(pinDatosDQ); 
DallasTemperature sensorDS18B20(&oneWireObjeto);
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void setup() {
  //En esta área declaras o inicializas son parametros de los sensores que utilizaras, configuralos para que trabajen a la frecuencia de 115200.
   // Iniciamos la comunicación serial del SIM900
   SIM900.begin(115200);
   Serial.begin(115200);
   // Iniciamos el bus 1-Wire
   sensorDS18B20.begin(); 
}
 
void loop() {
    //Dentro de esta área estara todo el código que se debe estar en funcionamiento en relación a los ciclos de repetición indicados en el ultimo delay

    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Leemos y mostramos los datos de los sensores DS18B20 a través del monitor serial (unicamente para ver en el monitor serial que se envia, se puede descartar este código)
    //
    Serial.print("Temperatura sensor 0: ");
    Serial.print(sensorDS18B20.getTempCByIndex(0));
    Serial.println(" C");
    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    //Se realiza la captura de datos del mensaje a enviar, estos deben ser enviados a través de la "variable" SIM900 ya que es la que se encarga de crear el mensaje a enviar
    //Importante que este escrito "SIM900.println((char)26);" al final de la creación del mensaje ya que es el que envia un comando AT al SIM900 que le indica que ya se termino
    //de escribir el mensaje que se va a enviar.
    SIM900.println("AT+CMGS=\"7442592371\"");   //Aquí se indica el número de celular al cual se enviara el msg
    delay(100);
    SIM900.println("La temperatura es ");
    SIM900.print(sensorDS18B20.getTempCByIndex(0));
    SIM900.println(" C");
    delay(100);
    SIM900.println((char)26);     //SE INDICA EL FINAL DEL MENSAJE DE TEXTO A ENVIAR
    delay(100);
    
    delay(10000);                 //En este retardo se indica cada cuanto tiempo se repetiran los ciclos, actualmente esta indicado a 10 segundos
}
