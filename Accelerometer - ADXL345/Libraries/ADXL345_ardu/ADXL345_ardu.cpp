#include "Arduino.h"
#include "ADXL345_ardu.h"

int ADXAddress = 0x53;                     // Device adress 

//!A constructor
ADXL345::ADXL345(){};

//!A destructor
ADXL345::~ADXL345(){};

//! A function which initializes accelerometer using range adjustment of 2g*/
void ADXL345::accelerometerInit()
{   
    // Initialize Wire Library
    Wire.begin();                   
    //Serial.begin(9600);                    
    Serial.begin(115200);
    delay(100);

    Wire.beginTransmission(ADXAddress);
    Wire.write(Register_2D);               
    Wire.write(8);                         // Enable operation
    Wire.endTransmission();                // End communication with device
  
    // Range adjustment (0 for 2g, 1 for 4g, 2 for 8g, 3 for 16g)
    Wire.beginTransmission(ADXAddress);
    Wire.write(Register_DATA_FORMAT);
    Wire.write(0);
    Wire.endTransmission();
    
    Serial.println("Initialized successfully");
    delay(1000);
}

     /*!
     \param axis the corresponding axis.
     \return The acceleration data.
     */
double ADXL345::getAcceleration(int axis)
{   
    int Axis_register0, Axis_register1;
    int Axis_0, Axis_1;
    double Axis_out;
    double Axis_g;
  
    //Define which register will be contacted according to the axis in question
    if (axis == 1)                          // Axis x = 1 
    {
        Axis_register0 = Register_X0;
        Axis_register1 = Register_X1;
    }
    
    else if(axis == 2)                      // Axis y = 2
    {
        Axis_register0 = Register_Y0;
        Axis_register1 = Register_Y1;
    }
    
    else if(axis == 3)                      // Axis z = 3 
    {
        Axis_register0 = Register_Z0;
        Axis_register1 = Register_Z1;
    }    
  
    // Begin communication with device
    Wire.beginTransmission(ADXAddress);     
    Wire.write(Axis_register0);             // Call for Register_X0
    Wire.write(Axis_register1);             // Call for Register_X1
    Wire.endTransmission();                 // End communication with device
    Wire.requestFrom(ADXAddress,2);         // Request 2 bytes from device
  
    // If 2 bytes are successfully received
    if(Wire.available()<=2)             
    {
        //Reads 2 bytes and saves their data in 2 variables 
        Axis_0 = Wire.read();
        Axis_1 = Wire.read(); 
    
        // The reading of the accelerometer is in 2 bytes, so, we have to move the most significant byte to the left in order to add them
        //  For example: MSB = 56, LSB = 32 -> MSB = MSB << 2 -> MSB + LSB = 5632
        //
        Axis_1=Axis_1<<8;

        // The final value  
        Axis_out=Axis_0+Axis_1;                           
        
    }
       
    // Conversion of data to 'g's
    //  256.0 for 2g, 128 for 4g, 64 for 8g, 32 for 16g
    //
    Axis_g = Axis_out/256;
 
    return Axis_g;
}

     





