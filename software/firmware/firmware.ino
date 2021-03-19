#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <max6675.h>


/*************************************************************
Notes:
- Timer 2 is used as clock. This means that PWM on pins 3 and 11
cannot be used.
*************************************************************/

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
#define  pwmBomba  9   //--------------------> Need a different pin to control pump direction.

/* Initialize color sensor */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_101MS, TCS34725_GAIN_4X);
uint16_t r, g, b, c;
boolean doMeasure = false;

/* Initialize thermocouple */
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

String inputString;
boolean stringComplete = false;

//Time between measurements
#define  TIMERseconds  5
int count=0;
boolean flag=false;


void setup(){
 Serial.begin(9600);
 inputString.reserve(50);
 
 if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }
  
 setTimer();
}


void loop(){
   
  //Should we do a measurement?
   if( flag & doMeasure){
     flag = false;
     measure();
   }
   
   //New command to parse?
   if( stringComplete ){
      Serial.println(inputString);
      parseCommand();
      inputString = "";
      stringComplete = false;
   }
   
}

//Set Timer 2 to work as clock to set interval between measurements.
void setTimer(){
  TCCR2A &= 0x0;  //CTC mode
  TCCR2A |= 0x2;
  TCCR2B &= !(0x0F); //Clear prescaler settings
  TCCR2B |= 0x7; //Fcpu/1024 -> 16Mhz/1024 = 15625
  OCR2A = 125;  //Count 125 pulses. -> 15625/125 = 125
  TIMSK2 |= (1 << OCIE2A); // Enable CTC interrupt 
}

//This routine is executed once every 1/125 seconds (see calculations above).
//Then, every 124 calls to this function we get 1 second.
ISR(TIMER2_COMPA_vect){
  count++;
  if(count == 124*TIMERseconds){
    count = 0;
    flag = true;
  }
}

