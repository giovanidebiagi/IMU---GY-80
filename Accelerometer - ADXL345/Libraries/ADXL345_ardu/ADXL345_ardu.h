/*! \file ADXL345.h
    \brief Accelerometer library header file.
*/

#ifndef ADXL345_ardu_H
#define ADXL345_ardu_H

#include "Arduino.h"
#include "Wire.h"

// Accelerometer configuration.
#define Register_ID 0
//POWER_CTL
#define Register_2D 0x2D      
//The DATA_FORMAT register controls the presentation of data to Register 0x32 through Register 0x37.
#define Register_DATA_FORMAT 0X31       
// These six bytes (Register 0x32 to Register 0x37) are eight bits each and hold the output data for each axis.
#define Register_X0 0x32                
#define Register_X1 0x33
#define Register_Y0 0x34
#define Register_Y1 0x35
#define Register_Z0 0x36
#define Register_Z1 0x37
// Axis definition.
#define X_axis 1
#define Y_axis 2
#define Z_axis 3        
     
//!Class for the accelerometer ADXL345.
class ADXL345
{
    public:
     //!A constructor.
     ADXL345();                                
     //!A destructor.
     ~ADXL345();
    
     //! A function which initializes the accelerometer. 
     void accelerometerInit();
     //! A function which gets acceleration data from the sensor, for each of the axis X, Y and Z.
     double getAcceleration(int axis);
          
};
                                            
                                            
#endif
