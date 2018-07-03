# Canne-Blanche

You can find the main page of the project [here](https://air.imag.fr/index.php/Canne_Blanche).

## This project consists of :

* an experimentation of IoT technologies allowing visually impaired people to avoid obstacles
* a comparison between three possible technologies known as :
  * [LiDaR](https://air.imag.fr/index.php/LIDAR_Lite_SEN-13167)
  * [VL53L1 Time of Flight Ranging Sensor ](https://air.imag.fr/index.php/)
  * [Movidius Neural Stick with a Raspeberry PI](https://air.imag.fr/index.php/Intel_Movidius)

## Installation :

### VL53L1 Time of Flight Ranging Sensor

Warning, this install is for Windows. If you are running Linux, please use a virtual machine.

* Download the [VL53L1X GUI](http://www.st.com/en/embedded-software/stsw-img008.html)   
* Extract the files from the .zip downloaded which should look like ```en.STSW-IMG008.zip```  
* Execute ```VL53L1X_Setup.exe```    
* Follow the installation wizard instructions   
* Connect your board to your machine   
* Launch ```VL53L1X_GUI```   
* Go on the tab named *about* and click on *Flash FW*

Now you can test your board !


### Raspberry Pi + Movidius NCS + LiDaR

[Raspberry Pi](#raspberry-pi)   
[Movidius NCS](#movidius-ncs)   
[LiDaR](#lidar)   
[Finals steps](#finals-steps)   

All the steps of this installation should be done on your Raspberry Pi.

#### Raspberry Pi
Install [Debian Stretch with Raspberry Pi Desktop](https://www.raspberrypi.org/downloads/raspberry-pi-desktop/) onto your Raspberry Pi. If these are your first steps with a Raspberry Pi, you can follow [this tutorial](https://projetsdiy.fr/decouverte-test-configuration-raspberry-pi-3/). And to install the camera, this is [here](http://espace-raspberry-francais.fr/Composants/Utilisation-Camera-sur-Raspberry-Pi-Francais/).


#### Movidius NCS
Open a terminal window (```CTRL + ALT + T```) and create a new directory. We will name it **workspace**.
* ```mkdir ~/workspace```

Go into this directory and clone the **ncdsk** repository from Movidius on Github

* ```cd ~/workspace```
* ```git clone https://github.com/movidius/ncsdk.git```

Go into your new repository and do its install

* ```cd ~/workspace/ncdsk```
* ```sudo bash ~/workspace/ncdsk/install.sh``` This will take a while (approximately 1h30)
* ```make all``` Execute this one then... it will take 4h. I advise to not do anything else on your Pi while it is executing.

Let's test your install :

* ```cd ~/workspace/ncsdk/blob/master/examples/apps/hello_ncs_py/```
* Run ```python hello_ncs_py```. The output should be like this :
  >Hello NCS! Device opened normally.   
  >Goodbye NCS! Device closed normally.   
  >NCS device working.   

You need do download an other repository :

* ```cd ~/workspace```
* ```git clone https://github.com/movidius/ncappzoo```

Now do ```cd ~/workspace/ncappzoo/apps/image-classifier``` and execute ```make all```


#### LiDaR
There is the connection diagram to connect the LiDaR to the Raspberry Pi :
![Connection diagram](https://snag.gy/eGT1FS.jpg)

We need to setup I2C on your Raspberry Pi
Open up a terminal window and type:  ```sudo raspi-config```
* Choose option : **5 Interfacing Options**
* Choose option : **P5 I2C and hit enter**
* Choose :  **Yes** to turn on the I2C interface
* Choose : **Ok**
* Choose :  **Finish**
Verify your setup by typing ```ls /dev/*i2c*``` in a terminal window.
If the result of the command looks like this ``` '/dev/i2c-1'``` then it is good.

Now you need to install the I2C tools : execute ```sudo apt-get install -y i2c-tools``` in a terminal window.


#### Finals steps

We now need to setup your Pi in order to launch the programm when your Pi is starting.
In a new terminal, execute the following command :

* ```sudo nano /etc/rc.local```

Insert this line just before ```# Print the IP address``` :   
* ```sudo python /home/pi/workspace/ncappzoo/apps/image-classifier.py ```   

### B-L475E-IOT01A + LiDaR

[B-L475E-IOT01A](#b-l475e-iot01a)   
[LiDaR](#lidar)

### B-L475E-IOT01A
To run the program, import it to the [MBed compiler](https://os.mbed.com/compiler/). MBed is an online compiler which allows you to download the binary file to execute for your embedded card.   


#### LiDaR
There is the connection diagram to connect the LiDaR to the B-L475E-IOT01A :
![Connection diagram](https://snag.gy/aXzPZR.jpg)
The represented card here is not the B-L475E-IOT01A but an Arduino Leopardo which have approximately the same pins. Just notice that the pins named SDA and SCl on the Arduino Leopardo are named D14 and D15 on the B-L475E-IOT01A.
