#ifndef L3G4200D_H
#define L3G4200D_H

#include "Arduino.h"
#include "Wire.h"

#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24

#define REGISTER_X0 0x28
#define REGISTER_X1 0x29
#define REGISTER_Y0 0x2A
#define REGISTER_Y1 0x2B
#define REGISTER_Z0 0x2C
#define REGISTER_Z1 0x2D

#define X_Axis 1
#define Y_Axis 2
#define Z_Axis 3

class L3G4200D
{
	public:
		L3G4200D();		/*!< Constructor */
		~L3G4200D();	/*!< Destructor */

		int gyroscopeInit(int scale);	/*!< Initialize gyroscope */
		double getGyroData(int axis);			/*!< Get data from gyroscope */
		void writeRegister(int L3GAddress, byte address, byte val);
		int readRegister(int L3GAddress, byte address);
};

#endif

