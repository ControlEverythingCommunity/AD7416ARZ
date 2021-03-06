// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// AD7416ARZ
// This code is designed to work with the AD7416ARZ_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Analog-Digital-Converters?sku=AD7416ARZ_I2CS#tabs-0-product_tabset-2

#include <application.h>
#include <spark_wiring_i2c.h>

// AD7416ARZ I2C address is 0x48(72)
#define Addr 0x48

double cTemp = 0.0, fTemp = 0.0;
int temp = 0;
void setup()
{
  // Set variable
  Particle.variable("i2cdevice", "AD7416ARZ");
  Particle.variable("cTemp", cTemp);

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

  // Request 2 byte of data
  Wire.requestFrom(Addr, 2);

  // Read 2 bytes of data
  // temp msb, temp lsb
  if (Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }

  // Convert the data to 12 bits
  // Convert the data to 10 bits
  temp = ((data[0] * 256) + (data[1] & 0xC0)) / 64;
  if (temp > 511)
  {
    temp -= 1024;
  }
  
  cTemp = temp * 0.25;
  fTemp = (cTemp * 1.8) + 32;

  // Output data to dashboard
  Particle.publish("Temperature in Celsius : ", String(cTemp));
  Particle.publish("Temperature in Fahrenheit : ", String(fTemp));
  delay(1000);
}

