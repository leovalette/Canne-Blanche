#ifndef LidarLitev2_H
#define LidarLitev2_H 


#include "mbed.h"


class LidarLitev2
{
public:
    LidarLitev2(PinName sda, PinName scl, bool = true);  // Constructor iniates I2C setup
    void configure(int = 0, int = 0xc4);   // Configure the mode and slave address 
    void beginContinuous(bool = true, char = 0x04, char = 0xff, int = 0xc4); //Enable if using continous setup with mode from Lidar and pulldown
    int distance(bool = true, bool = true, int = 0xc4); //Calclulates distance through I2C protocol of activating sensor with a write, then a write for the register, and a read.
    // Returns distance as a integer in cm
    
    int distanceContinuous(int = 0xc4); // 1.) Set Lidar circuit for continuous mode 
                                        // 2.) utilize the beginContinous function and configure as desired
                                        // This function returns distance without any need to activate the lidar senore through a write command,
                                        // instead the mode pin pulls down when the lidar is ready for a read
    // Returns distance as a integer in cm
    
private:
    // I2C Functions //
    ///////////////////
    I2C i2c; // Kept private as to prevent changing the I2C once set in the constructor of LidarLitev2
};

#endif /* LidarLitev2_H */