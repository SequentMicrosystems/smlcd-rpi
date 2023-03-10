[![smlcd-rpi](pictures/sequent.jpg)](https://www.sequentmicrosystems.com)

# smlcd-rpi
Drivers for Sequent Microsystems LCD Adapter HAT
[![smlcd-rpi](pictures/Display.jpg)](https://www.sequentmicrosystems.com)


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
## [Command line description](https://github.com/SequentMicrosystems/smlcd-rpi/wiki/Sequent-Microsystems-LCD-Adapter-HAT-command-line-Documentation)

## [Firmware Update](update/README.md)

## [Python](python/README.md)

## [Sprinklers Node-RED](https://github.com/SequentMicrosystems/smlcd-rpi/blob/main/node-red_examples/sprinklers/README.md)
