# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# AD7416ARZ
# This code is designed to work with the AD7416ARZ_I2CS I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/content/Analog-Digital-Converters?sku=AD7416ARZ_I2CS#tabs-0-product_tabset-2

import smbus
import time

# Get I2C bus
bus = smbus.SMBus(1)

# AD7416ARZ address, 0x48(72)
# Read data back fom 0x00(00), 2 bytes
# temp MSB, temp LSB
data = bus.read_i2c_block_data(0x48, 0x00, 2)

# Convert the data to 10-bits
temp = ((data[0] * 256) + (data[1] & 0xC0)) / 64
if temp > 511 :
	temp -= 1024
cTemp = temp * 0.25
fTemp = cTemp * 1.8 + 32

# Output data to screen
print "Temperature in Celsius : %.2f C" %cTemp
print "Temperature in Fahrenheit : %.2f F" %fTemp
