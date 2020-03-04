#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <max6675.h>



/* Sensor de color TCS34725 */
/* Connect SCL    to analog 5
   Connect SDA    to analog 4
   Connect VDD    to 3.3V DC
   Connect GROUND to common ground */
   
/* Termocupla MAX6675 */
/* VCC  to  5V DC
   GND  to  GND
   SCK  to  pin 6
   CS   to  pin 5
   SO   to  pin 4 */
#define thermoDO  4
#define thermoCS  5
#define thermoCLK 6

/* Control de Bomba */
#define  pwmBomba  9   //--------------------> Para controlar el sentido hay que usar otro pin mas.

/* Inicializamos sensor de color */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

/* Inicializamos termocupla */
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void setup(){
 Serial.begin(115200);
 
 if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }
}

void loop(){
  uint16_t r, g, b, c, colorTemp, lux;

  for( int i=0; i<256; i+=1 ){
   analogWrite(3, i);
   Serial.println(i);
   delay(500);
   tcs.getRawData(&r, &g, &b, &c);
   Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
   Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
   Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.println(" ");
  
    Serial.print("**C = "); 
   Serial.println(thermocouple.readCelsius());
  }
}
