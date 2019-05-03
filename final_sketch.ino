// void setRGB(int R, int G, int B)

// Include Libraries
#include "Arduino.h"
#include "MPU6050.h"
#include "Wire.h"
#include "I2Cdev.h"
#include "RGBLed.h"

// Pin Definitions
#define RGBLED_PIN_R  5
#define RGBLED_PIN_G  6
#define RGBLED_PIN_B  3

// Global variables and defines
int16_t mpu6050Ax, mpu6050Ay, mpu6050Az;
int16_t mpu6050Gx, mpu6050Gy, mpu6050Gz;

// object initialization
MPU6050 mpu6050;
RGBLed rgbLed(RGBLED_PIN_R, RGBLED_PIN_G, RGBLED_PIN_B);

// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;
char last = '1';

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while(!Serial) ; // wait for serial port to connect. Needed for native USB
    Wire.begin();
    mpu6050.initialize();
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    // SparkFun MPU-6050 - Accelerometer and Gyro - Test Code
    mpu6050.getMotion6(&mpu6050Ax, &mpu6050Ay, &mpu6050Az, &mpu6050Gx, &mpu6050Gy, &mpu6050Gz);   //read accelerometer and gyroscope raw data in three axes
    Serial.print(mpu6050Ax); Serial.print(", ");
    Serial.print(mpu6050Ay); Serial.print(", ");
    Serial.println(mpu6050Az); 
    menu();
    delay(50);        
}

void menu()
{
//  while (!Serial.available());
    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if ((last != '1') && c != '1') {
          break;
        }
        else if (isAlphaNumeric(c)) 
        { 
          if(c == '1') 
          {
            rgbLed.turnOff();
            last = '1';
          }
          else if (c == '2')
          {
            rgbLed.setRGB(255, 0, 0);
            last = '2';
          }
          else if (c == '3')
          {
            rgbLed.setRGB(0, 255, 0);
            last = '3';
          }
          else if (c == '4')
          {
            rgbLed.setRGB(0, 0, 255);
            last = '4';
          }
          else if (c == '5')
          {
            rgbLed.setRGB(255, 255, 255);
            last = '5';
          }
          time0 = millis();
          return c;
        }
    }
}
