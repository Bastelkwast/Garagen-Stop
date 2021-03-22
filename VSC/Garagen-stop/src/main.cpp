// Garagenstop
// Verwendet wird ein Arduino Pro Mini 5V/16MHz, ein Ultraschallsensor US-026, 2x Dotmatrix 8x8 mit MAX72xx Chip
// Anschluss:
// Der Ultraschallsensor: VCC an 5V, GND an GND, Trig an Pin 7 , Echo an Pin 6
// Die Dot Matrix: VCC an 5V, GND an GND, DIN an Pin 11, CS an Pin 10, CLK an Pin 13

#include <Arduino.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <HCSR04.h>

const uint16_t WAIT_TIME = 300;

#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW
#define MAX_DEVICES 2

#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    10

int Korrektur = -2; 
// Da der Sensor hinter der Garagenwand angebracht ist wird hier die 
// Wandstärke mit angegeben um sie von dem gemessenen Wert abzuziehen.

byte triggerPin = 7;
byte echoPin = 6;
int entfernung = 0;

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
  entfernung = entfernung + Korrektur;
  
  Serial.print(entfernung);
  Serial.println(" cm");
  
  delay(500);

if (entfernung < 2 || entfernung > 199) // Der Messwert wird nur im Bereich von 2 - 199cm angezeigt
{
P.print("---");
}
else
{
P.print(entfernung);
}

delay(WAIT_TIME);

}