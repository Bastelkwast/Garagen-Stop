#include <Arduino.h>

// Program to demonstrate the MD_Parola library
//
// Uses the Arduino Print Class extension with various output types
//
// MD_MAX72XX library can be found at https://github.com/MajicDesigns/MD_MAX72XX
//

#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <HCSR04.h>


const uint16_t WAIT_TIME = 300;

// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW
#define MAX_DEVICES 2

#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    10

int Test = 1;

byte triggerPin = 7;
byte echoPin = 6;
int entfernung = 0;

// Hardware SPI connection
MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
// Arbitrary output pins
// MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

void setup(void)
{
  P.begin();
  Serial.begin(9600);
  HCSR04.begin(triggerPin, echoPin);
}

void loop(void)
{
double* distances = HCSR04.measureDistanceCm();
  
  entfernung = distances[0];
  
  Serial.print(entfernung);
  Serial.println(" cm");
  
  delay(500);

if (entfernung < 5 || entfernung > 199)
{
P.print("---");
}
else
{
P.print(entfernung);
}

delay(WAIT_TIME);

//Test++;
//  P.print(1234, HEX);
//  delay(WAIT_TIME);
//  P.print(12.5);      // float not supported by Arduino Print class
//  delay(WAIT_TIME);
//  P.print(9876l);
//  delay(WAIT_TIME);
//  P.println("end");   // only get the /r/n characters - avoid using println
//  delay(WAIT_TIME);
//  P.write('A');
//  delay(WAIT_TIME);
//  P.write('B');
//  delay(WAIT_TIME);
//  P.write('C');
//  delay(WAIT_TIME);

}