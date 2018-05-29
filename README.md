# Canne-Blanche

## This project consists of :

* an experimentation of IoT technologies allowing visually impaired people to avoid obstacles
* a comparison between three possible technologies known as :
  * [LiDaR](https://air.imag.fr/index.php/LIDAR_Lite_SEN-13167)
  * [VL53L1 Time of Flight Ranging Sensor ](https://air.imag.fr/index.php/)
  * [Movidius Neural Stick with a Raspeberry PI](https://air.imag.fr/index.php/Intel_Movidius)

## Installation :
* Install [Debian Stretch with Raspberry Pi Desktop](https://www.raspberrypi.org/downloads/raspberry-pi-desktop/) onto your Raspberry Pi. If these are your first steps with a Raspberry Pi, you can follow [this tutorial](https://projetsdiy.fr/decouverte-test-configuration-raspberry-pi-3/).
Open a terminal window (```CTRL + ALT + T```) and create a new directory. We will name it *workspace*.
  * ```mkdir ~/workspace```
Go into this directory and clone the *ncdsk* repository from Movidius on Github
  * ```cd ~/workspace```
  * ```git clone https://github.com/movidius/ncsdk.git```
Go into your new repository and do its install
  * ```cd ~/workspace/ncdsk```
  * ```./install.sh``` This will take a while (approximately 1h30)
  * ```make all``` Execute this one then... it will take 4h. I advise to not do anything else on your Pi while it is executing.
Let's test your install :
  * ```cd ~/workspace/ncsdk/blob/master/examples/apps/hello_ncs_py/```
  * Run ```python hello_ncs_py```. The output should be like this :
    * ```Hello NCS! Device opened normally.
  Goodbye NCS! Device closed normally.
  NCS device working.```

You need do download an other repository :
  * ```cd ~/workspace```
  * ```git clone https://github.com/movidius/ncappzoo```
Now do ```cd ~/workspace/ncappzoo/apps/image-classifier``` and execute ```make all```


We now need to setup your Pi in order to launch the programm when your Pi is starting.
In a new terminal, execute the following command :
    * ```sudo nano /etc/rc.local```
Insert this line just before ```# Print the IP address``` : ```sudo python /home/pi/workspace/ncappzoo/apps/image-classifier.py ```
