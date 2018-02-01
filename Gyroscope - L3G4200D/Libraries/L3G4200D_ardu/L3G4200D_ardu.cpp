#include "Arduino.h"
#include "L3G4200D_ardu.h"

int L3G4200D_Address = 105;		/*!< Gyro address */

L3G4200D::L3G4200D() { ; }		/*!< Constructor */
L3G4200D::~L3G4200D() { ; }		/*!< Destructor */

int L3G4200D::gyroscopeInit(int scale)
{
	// Enable x, y, z and turn off power down:
	writeRegister(L3G4200D_Address, CTRL_REG1, 0b00001111);

	// If you'd like to adjust/use the HPF, you can edit the line below to configure CTRL_REG2:
	writeRegister(L3G4200D_Address, CTRL_REG2, 0b00000000);

	// Configure CTRL_REG3 to generate data ready interrupt on INT2
	// No interrupts used on INT1, if you'd like to configure INT1
	// or INT2 otherwise, consult the datasheet:
	writeRegister(L3G4200D_Address, CTRL_REG3, 0b00001000);

	// CTRL_REG4 controls the full-scale range, among other things:
	if (scale == 250) {
		writeRegister(L3G4200D_Address, CTRL_REG4, 0b00000000);
	}
	else if (scale == 500) {
		writeRegister(L3G4200D_Address, CTRL_REG4, 0b00010000);
	}
	else {
		writeRegister(L3G4200D_Address, CTRL_REG4, 0b00110000);
	}

	// CTRL_REG5 controls high-pass filtering of outputs, use it
	// if you'd like:
	writeRegister(L3G4200D_Address, CTRL_REG5, 0b00000000);
}

double L3G4200D::getGyroData(int axis)
{
	int axis_register0, axis_register1;
	double gyro_data;

	if (axis == 1)
	{
		axis_register0 = REGISTER_X0;
		axis_register1 = REGISTER_X1;
	}

	else if (axis == 2)
	{
		axis_register0 = REGISTER_Y0;
		axis_register1 = REGISTER_Y1;
	}

	else if (axis == 3)
	{
		axis_register0 = REGISTER_Z0;
		axis_register1 = REGISTER_Z1;
	}

	// Data reading routine
	byte MSB = readRegister(L3G4200D_Address, axis_register1);
	byte LSB = readRegister(L3G4200D_Address, axis_register0);
	gyro_data = ((MSB << 8) | LSB);

	return gyro_data;
}

void L3G4200D::writeRegister(int L3GAddress, byte address, byte val)
{
	Wire.beginTransmission(L3GAddress); // start transmission to device 
	Wire.write(address);       // send register address
	Wire.write(val);         // send value to write
	Wire.endTransmission();     // end transmission
}

int L3G4200D::readRegister(int L3GAddress, byte address)
{
	int v;
	Wire.beginTransmission(L3GAddress);
	Wire.write(address); // register to read
	Wire.endTransmission();

	Wire.requestFrom(L3GAddress, 1); // read a byte

	while (!Wire.available())
	{
		// waiting
	}
	v = Wire.read();
	return v;
}