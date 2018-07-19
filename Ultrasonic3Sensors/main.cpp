#include "mbed.h"
#include "ultrasonic.h"

#define OBJECTDIST 3000
Serial pc(USBTX,USBRX);
int dist1;
int dist2;
int dist3;

void dist(int distance)
 
{
    //put code here to happen when the distance is changed
    pc.printf("Distance changed to %dmm\r\n", distance);
}

//Set the trigger pin to D8 and the echo pin to D9 have updates every .1 seconds and a timeout after 1second, and call dist when the distance changes
ultrasonic mu1(D8, D9, .1, 1, &dist);    //middle sensor 
ultrasonic mu2(D7, D6, .1, 1, &dist);   //left sensor
ultrasonic mu3(D4, D5, .1, 1, &dist);   //right sensor

int objectDetected(int distance){
    if (distance <= OBJECTDIST){
        return 1;
    }
    return 0;
}

int main()
{
    //start mesuring the distance
    mu1.startUpdates();
    mu2.startUpdates();
    mu3.startUpdates();
    while(1)
    {
        //Put the same code as for LiDaR 
        //pc.printf("Sensor 1");
        //mu1.checkDistance();     //call checkDistance() as much as possible, as this is where
                                //the class checks if dist needs to be called.
        //pc.printf("Sensor 2");
        //mu2.checkDistance();
        //pc.printf("Sensor 3");
        //mu3.checkDistance();
        dist1 = mu1.getCurrentDistance();
        dist2 = mu2.getCurrentDistance();
        dist3 = mu3.getCurrentDistance();
        pc.printf("\nDistance 1 %dmm\r\n", dist1);
        pc.printf("Distance 2 %dmm\r\n", dist2);
        pc.printf("Distance 3 %dmm\r\n", dist3);
        if (objectDetected(dist1)){
            pc.printf("\nObject in front of you\n");   
        }
        if (objectDetected(dist2)){
            pc.printf("Object on your left\n");   
        }
        if (objectDetected(dist3)){
            pc.printf("Object on your right\n");   
        }
        wait(1);
    }
}
