#include "LidarLitev2.h"
#include "math.h"

int nackack;
//Constructor iniating the I2C connection
LidarLitev2::LidarLitev2(PinName sda, PinName scl, bool fast) : i2c(sda, scl)
{
    if (fast) i2c.frequency(400000); //I2C @ 400kHz
    else i2c.frequency(100000);     //I2C @ 100Khz
    wait(0.2);
}

void LidarLitev2::configure(int config, int LidarLitev2_addr)
{
    char reset[2] = {0x00, 0x00};           //Register and value to Reset the Lidar to orgional settings
    char aquisition[2] = {0x04, 0x00};      //Register and value to set the acquisition to 1/3 default value
    switch (config){
        case 0: //Deafault config
            nackack = 1;
            while(nackack !=0)
            {
                //wait_ms(1);
                nackack = i2c.write(LidarLitev2_addr, reset, 2); // Resets the Lidar settings
            }
            
            break;
        case 1:
            nackack = 1;
            while(nackack !=0)
            {
                //wait_ms(1);
                nackack = i2c.write(LidarLitev2_addr, aquisition, 2);  // Set the acquisition to 1/3 default value
            }
            break;
        }          
}

void LidarLitev2::beginContinuous(bool modePinLow, char interval, char numberOfReadings,int LidarLitev2_addr)
{
    char reg_freq[2] = {0x45, interval};    // Sets the time between measurements through reg 0x45
    
    nackack = 1;
    while(nackack !=0)
            {
                nackack =i2c.write(LidarLitev2_addr, reg_freq, 2, false);  //Write to register 0x45 the interval time
            }
  //  Set register 0x04 to 0x20 to look at "NON-default" value of velocity scale
  //  If you set bit 0 of 0x04 to "1" then the mode pin will be low when done
    char reg_modePin[2] = {0x04, 0x21}; // Default modePin Setting
    if (!modePinLow) reg_modePin[1] = 0x20;
    
    nackack = 1;
    while(nackack !=0)
            {
                nackack =i2c.write(LidarLitev2_addr, reg_modePin, 2, false);
            }
    char reg_numOfReadings[2] = {0x11, numberOfReadings};  // Set the number of readings through reg 0x11
    
    nackack = 1;
    while(nackack !=0)
            {
                nackack =i2c.write(LidarLitev2_addr, reg_numOfReadings, 2, false);   // writes into Reg_numofreadings the number of readings desired
            }
    char reg_reading_distance[2] = {0x00, 0x04};  // Iniates reg_readDistance
    nackack = 1;
    while(nackack !=0)
            {
                nackack =i2c.write(LidarLitev2_addr, reg_reading_distance, 2, false);   // writes into Reg_readDistance to begin continuos reading
            }
}

int LidarLitev2::distance(bool stablizePreampFlag, bool takeReference, int LidarLitev2_addr){
    // Standard read distance protocol without continuous
    
    char reg_dc[2] = {0x00, 0x04};  // Iniates reg_readDistance
    if(!stablizePreampFlag) reg_dc[1] = 0x03;
    
    nackack = 1;
    while(nackack !=0)
    {
        nackack = i2c.write(LidarLitev2_addr, reg_dc, 2); // writes into Reg_readDistance to begin a reading
    }
    
    char data[2];
    char reg_read[1] = {0x8f};  // Register to read distance value from
    
    nackack = 1;
    while(nackack !=0)
    {
        nackack = i2c.write(LidarLitev2_addr, reg_read, 1); // Ready to read from reg distance
    }
    
    nackack = 1;
    while(nackack !=0)
    {
        nackack = i2c.read(LidarLitev2_addr, data, 2);  // Read from reg distance 2bytes of information
    }
    int distance = ((uint8_t)data[0]<<8) + (uint8_t)data[1]; //Combine byes to a int to be returned as the distance measured
    return distance;
}

int LidarLitev2::distanceContinuous(int LidarLitev2_addr)
{
    char data[2];
    char reg_read[1] = {0x8f}; // Register to read distance value from
    
    nackack = 1;
    while(nackack !=0)
            {
                nackack =i2c.write(LidarLitev2_addr, reg_read, 1); // Ready to read from reg distance
            }
    nackack = 1;
    while(nackack !=0)
            {
                nackack =i2c.read(LidarLitev2_addr, data, 2); // Read from reg distance 2bytes of information
            }
    int distance = ((uint8_t)data[0]<<8) + (uint8_t)data[1]; //Combine byes to a int to be returned as the distance measured
    return distance;
}
