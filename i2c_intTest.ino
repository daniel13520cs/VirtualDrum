#include <Wire.h>

/* ADXL pin sets 
 *  Vin : 3.3V
 *  GND : 0V
 *  SDD : 0V => makes the slave address 0x53
 *  CS : 3.3V
 *  => thie results in slave address 0x53
 */
 

/* Teensy 3.2 config */
//#define CS A2 
//#define SDD_Pin A3
#define SDA_Pin A4//1
#define SCL_Pin A5//2
//#define GND A6
//#define three_V_three A7
//#define VIN A8

#define acceAddr 0x53 //0x1D or 0x53
#define DATAX0 0x32
#define DATAX1 0x33
#define DATAY0 0x34
#define DATAY1 0x35
#define DATAZ0 0x36
#define DATAZ1 0x37
#define Power_Register 0x2D // Power Control Register

#include "config.h"

int Z1;

void setup_ADXL343() 
{
  /* set up ADXL343 */  
  //set up sda and scl 
  Wire.setSDA(SDA_Pin);
  Wire.setSCL(SCL_Pin);

  //begin
  Wire.begin();
  Serial.begin(9600);
  delay(100);
  
  // Enable measurement
  Wire.beginTransmission(acceAddr);
  Wire.write(Power_Register);
  // Bit D3 High for measuring enable (0000 1000)
  Wire.write(8);  
  Wire.endTransmission();
}



void runADXL343() 
{
 //Serial.println("begin...");
 
  Wire.beginTransmission(acceAddr);
  Wire.write(DATAZ0);
  Wire.write(DATAZ1);
  Serial.println(Wire.endTransmission());

//  Serial.print("ack = ");
//  Serial.println(ack & (0x1), DEC);

  Wire.requestFrom(acceAddr, 2);

  if (Wire.available() <= 2) {
    int z0 = Wire.read();
    int z1 = Wire.read();
//    if (z0 < 150) {
//      digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
//    } else {
//      digitalWrite(led, LOW);   // turn the LED on (HIGH is the voltage level)
//    }
    Z0 = z0;
    Z1 = z1;
  }

  Serial.print("Z0 = ");
  Serial.print(Z0);
  Serial.print("   Z1 = ");
  Serial.println(Z1);

  
delay(300);
}
