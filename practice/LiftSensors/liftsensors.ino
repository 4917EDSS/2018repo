/*

  Arduino UNO sketch to show minimal coding required to read distance from tinyLiDAR
  This program will continually print the measured distance from tinyLiDAR which
  is operating in its default single step mode.
  Last Edit: Oct 23, 2017
  Copyright (c) 2017 by Dinesh Bhatia

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>

  Notes:
  This code requires the "Arduino I2C Master Library rev5" library to allow the
  standard I2C stretch feature to work properly on the UNO.
** Please install it before running this sketch. **
  The library can be downloaded from here:
  http://dsscircuits.com/articles/arduino-i2c-master-library

*/
#include <Wire.h>
#include "Ultrasonic.h"

#define SCL_PORT PORTC
#define SDA_PORT PORTC
#define SCL_PIN 5        //std SCL pin
#define SDA_PIN 4        //std SDA pin

#define I2C_ADDRESS 0x10

Ultrasonic ultrasonic(12,13);

void setup() {

  Serial.begin(115200);     //setup the serial port
  Wire.begin(); // join i2c bus

} //setup

void loop() {

  uint16_t val;
  uint16_t ultraVal;
  int state = 0;

  Serial.println("TinyLiDAR");

  while (1)
  {
    // Get tinyLidar value
    Wire.beginTransmission((int)I2C_ADDRESS);
    Wire.write('D');  //take single measurement
    Wire.endTransmission();
    Wire.requestFrom((int)I2C_ADDRESS, 2); // request 2 bytes from tinyLiDAR
    val = 0;
    if (2 <= Wire.available()) // if two bytes were received
    {
      val = Wire.read(); // receive high byte (overwrites previous reading)
      val = val << 8; // shift high byte to be high 8 bits
      val |= Wire.read(); // receive low byte as lower 8 bits
    }
    ultraVal = ultrasonic.Ranging(CM);

    switch( state )
    {
     case 0:
      Serial.print("Up        L=");
      Serial.print(val);
      Serial.print(" U=");
      Serial.println(ultraVal);
      if( val < 500 ) // in mm
      {
        state = 1;
      }
      break;
     case 1:
      Serial.print("Fwd       L=");
      Serial.print(val);
      Serial.print(" U=");
      Serial.println(ultraVal);
      if( ultraVal < 5 ) // in cm
      {
        state = 2;
      }
      break;
     case 2:
      Serial.print("Stop      L=");
      Serial.print(val);
      Serial.print(" U=");
      Serial.println(ultraVal);
      break;
    }

    

    
    
    delay(100);               // delay as required (13ms or higher in default single step mode)
  } //while


} //loop

