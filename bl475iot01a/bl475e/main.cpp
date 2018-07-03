#include "mbed.h"
#include "LidarLitev2.h"
#include "stm32l475e_iot01_magneto.h"
#include "stm32l475e_iot01_gyro.h"

#define LIDARLite1_SDA PB_9   //SDA pin on DISCO-L475VG-IOT01A
#define LIDARLite1_SCL PB_8  //SCL pin on DISCO-L475VG-IOT01A

#define DIST_OSTACLE 300
#define LINEARITY_STEP 100
#define ROTATION_STEP 20000

DigitalOut led1(LED1);
DigitalOut led2(LED2);
LidarLitev2 Lidar(LIDARLite1_SDA, LIDARLite1_SCL);
Serial pc(USBTX,USBRX);
int16_t pDataXYZ[3] = {0};
int16_t pDataXYZprev[3] = {0};
float pGyroDataXYZ[3] = {0};
int linear = 1;

int isLinear(int16_t n, int16_t m){
    if (abs(n-m) > LINEARITY_STEP){
        return 0;
    }
    return 1;
}

int main()
{
    BSP_MAGNETO_Init();
    BSP_GYRO_Init();
    BSP_MAGNETO_GetXYZ(pDataXYZprev);
    BSP_MAGNETO_GetXYZ(pDataXYZ);
    pc.baud(9600);
    Lidar.configure();
         
    while(1) {  
        while(Lidar.distance() > DIST_OSTACLE){
            pc.printf("distance = %d cm \n", Lidar.distance());
            pDataXYZprev[0] = pDataXYZ[0];  
            pDataXYZprev[1] = pDataXYZ[1]; 
            pDataXYZprev[2] = pDataXYZ[2]; 
            BSP_MAGNETO_GetXYZ(pDataXYZ);
            pc.printf("\nMAGNETO_X = %d\n", pDataXYZ[0]);
            pc.printf("MAGNETO_Y = %d\n", pDataXYZ[1]);
            pc.printf("MAGNETO_Z = %d\n", pDataXYZ[2]);

            if (!isLinear(pDataXYZprev[0], pDataXYZ[0]) && !isLinear(pDataXYZprev[1], pDataXYZ[1]) && !isLinear(pDataXYZprev[2], pDataXYZ[2])){
                linear = 0;
            }else{
                linear = 1;
            }
            pc.printf("linear = %d\n", linear);
            BSP_GYRO_GetXYZ(pGyroDataXYZ);
            printf("GYRO_Z = %.2f\n", pGyroDataXYZ[2]);
            if(pGyroDataXYZ[2] <= -ROTATION_STEP && !linear){
                //right vibration 
                led1 = 1;
                pc.printf("left deviation");
                wait(2);
                led1 = 0;
            }
            if(pGyroDataXYZ[2] >= ROTATION_STEP && !linear){
                //left vibration    
                led2 = 1;
                pc.printf("right deviation");
                wait(2);
                led2 = 0;
            }
            wait(1);
        } 
        pc.printf("distance = %d \n", Lidar.distance());
        //double vibration
        led1 = 1;
        led2 = 1;
        pc.printf("Obstacle ahead");
        wait(2);
        led1 = 0;
        led2 = 0;  
    }
}
