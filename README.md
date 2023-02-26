# smlcd-rpi
Drivers for Sequent Microsystems LCD Adapter HAT

## Setup

Enable Raspberry Pi I2C communication by opening a terminal and typing:
```bash
~$ sudo raspi-config
```
Go to the *Interface Options* menu then *I2C* and enable the port.

## Usage

```bash
~$ git clone https://github.com/SequentMicrosystems/smlcd-rpi.git
~$ cd smlcd-rpi/
~/smlcd-rpi$ sudo make install
```

Now you can access all the functions of the LCD board through the command "smlcd". Use -h option for help:
```bash
~$ smlcd -h
```

If you clone the repository any update can be made with the following commands:

```bash
~$ cd smlcd-rpi/  
~/smlcd-rpi$ git pull
~/smlcd-rpi$ sudo make install
``` 
## Command line description

The ```smlcd``` command line interface is created to access all the features of the Sequent Microsystems LCD Adapter HAT. A complete help of the command is shown by running the ```-h``` option. 
Below a list of the avilable command options:

### ```-v``` 
Show the version number of the ```smlcd``` command, usage:
```bash
$ smlcd -v
```

### ```-h```
Show the list of all available command options and can take a command option as a parameter and display the help for that option.
Example: 
```bash
$ smlcd -h -v
        -v              Display the smlcd command version number
        Usage:          smlcd -v
        Example:        smlcd -v  Display the version number
```

### ```-warranty```
Dispaly this command warranty.

### ```-list``` 
Tells you if a LCD Adapter Hat is connected or not:
```bash
 $ smlcd -list
Display board detected
```

### ```board```
Display board firmware version:
```bash
$ smlcd board
Firmware ver 02.00
```

### ```cmdwr```
Send a command to the display, for example if you need to clear dispaly you send the command 1:
```bash
$ smlcd cmdwr 1
```
This option is useful for initialize the display also. The initialization procedure is specific to each display type. Please refere to yur LCD display datasheet for initialization list of commands and timing.
Below an example of shell script file for initialisation of a 4 line display, no cursor, normal writing direction:
```bash
#!/bin/bash

#init display commands
smlcd cmdwr 60
sleep 0.01
smlcd cmdwr 12
sleep 0.01
smlcd cmdwr 6
sleep 0.01

#clear display
smlcd cmdwr 1

#set backlight to 50%
smlcd blwr 50

#replace the folowing line with your greetings message
smlcd txtwr Sequent LCD Adapter
```






## [Firmware Update](https://github.com/SequentMicrosystems/smlcd-rpi/blob/main/update/README.md)
