// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// AD7416ARZ
// This code is designed to work with the AD7416ARZ_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Analog-Digital-Converters?sku=AD7416ARZ_I2CS#tabs-0-product_tabset-2

#include <Wire.h>

// AD7416ARZ I2C address is 0x48(72)
#define Addr 0x48

void setup()
{
  // Initialise I2C communication as Master
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(9600);
  delay(300);
}

void loop()
{
  unsigned int data[2];

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Select data register
  Wire.write(0x00);
  // Stop I2C transmission
  Wire.endTransmission();

  // Request 2 bytes of data
  Wire.requestFrom(Addr, 2);

  // Read 2 bytes of data
  // temp msb, temp lsb
  if (Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }

  // Convert the data to 10-bits
  int temp = (((data[0] & 0xFF) * 256) + (data[1] & 0xC0)) / 64;
  if (temp > 511)
  {
    temp -= 1024 ;
  }
  float cTemp = temp * 0.25;
  float fTemp = (cTemp * 1.8) + 32;

  // Output data to serial monitor
  Serial.print("Temperature in Celsius : ");
  Serial.print(cTemp);
  Serial.println(" C");
  Serial.print("Temperature in Fahrenheit : ");
  Serial.print(fTemp);
  Serial.println(" F");
  delay(500);
}
