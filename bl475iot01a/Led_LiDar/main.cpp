#include "mbed.h"
#include "LidarLitev2.h"

#define LD1_ON     {led1 = 1;}
#define LD1_OFF    {led1 = 0;}
#define LD1_TOG    {led1 = !led1;}

#define LD2_ON     {led2 = 1;}
#define LD2_OFF    {led2 = 0;}
#define LD2_TOG    {led2 = !led2;}

#define LD3_ON     {led34.output(); led34 = 1; led3_status = 1;}
#define LD3_OFF    {led34.input(); led3_status = 0;}
#define LD3_TOG    {if (led3_status) LD3_OFF else LD3_ON;}

#define LD4_ON     {led34.output(); led34 = 0; led4_status = 1;}
#define LD4_OFF    {led34.input(); led4_status = 0;}
#define LD4_TOG    {if (led4_status) LD4_OFF else LD4_ON;}

#define LIDARLite1_SDA PB_9   //SDA pin on DISCO-L475VG-IOT01A
#define LIDARLite1_SCL PB_8  //SCL pin on DISCO-L475VG-IOT01A

DigitalOut led1(LED1);
DigitalOut led2(LED2);
// This object drives both LD3 and LD4 on the board.
// Only one of these LEDs can be driven at a time.
DigitalInOut led34(LED3);
InterruptIn button(USER_BUTTON);

LidarLitev2 Lidar(LIDARLite1_SDA, LIDARLite1_SCL);
Serial pc(USBTX,USBRX);
Timer dt;

int led_nb = 0;
int led3_status = 0;
int led4_status = 0;
double led_delay = 0.1; // 100 ms

void button_pressed()
{
    pc.printf("let %d \n",led_nb);
    if (led_nb == 4) {
        if (led_delay == 0.1) {
            led_delay = 1.0; // 1 second
        } else {
            led_delay = 0.1; // 100 ms
        }
    }
}

void button_released()
{
    LD1_OFF;
    LD2_OFF;
    LD3_OFF;
    LD4_OFF;
    led_nb++;
    if (led_nb > 4) {
        led_nb = 0;
    }
}

int main()
{
    button.fall(&button_pressed); // Change led delay
    button.rise(&button_released); // Change led
    pc.baud(115200);
    Lidar.configure();
    dt.start();
         
    while(1) {
        pc.printf("distance = %d cm frequency = %.2f Hz\n", Lidar.distance(), 1/dt.read());
         dt.reset();
        switch(led_nb) {
            case 0:
                LD1_TOG;
                break;
            case 1:
                LD2_TOG;
                break;
            case 2:
                LD3_TOG;
                break;
            case 3:
                LD4_TOG;
                break;
            case 4:
                LD1_TOG;
                LD2_TOG;
                LD3_TOG;
                break;
            default:
                break;
        }
        wait(led_delay);
    }
}
