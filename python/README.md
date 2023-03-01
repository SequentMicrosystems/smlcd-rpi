[![smlcd-rpi](../pictures/sequent.jpg)](https://www.sequentmicrosystems.com)

# sm_lcd

This is the python library to control the [Six-in-one LCD Adapter Kit Using 2004 or 1602 LCDs for Raspberry Pi](https://sequentmicrosystems.com).

## Install

```bash
~$ sudo apt-get update
~$ sudo apt-get install build-essential python-pip python-dev python-smbus2
~$ git clone https://github.com/SequentMicrosystems/smlcd-rpi.git
~$ cd smlcd-rpi/python/sm_lcd/
~/smlcd-rpi/python/sm_lcd$ sudo python setup.py install
```
If you use python3.x repace the second and the last lines with:
```
~$ sudo apt-get install build-essential python3-pip python3-dev python3-smbus2

~/smlcd-rpi/python/sm_lcd$ sudo python3 setup.py install
```
## Update

```bash
~$ cd smlcd-rpi/
~/smlcd-rpi$ git pull
~$ cd smlcd-rpi/python/sm_lcd/
~/smlcd-rpi/python/sm_lcd$ sudo python setup.py install
```
If you use python3.x repace the last line with:
```
~/smlcd-rpi/python/sm_lcd$ sudo python3 setup.py install
```
## Usage example

```bash
~$ python
Python 3.10.7 (main, Nov  7 2022, 22:59:03) [GCC 8.3.0] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> import sm_lcd
>>> lcd = sm_lcd.SMlcd()
>>> lcd.bl_single(50)
>>> lcd.display_init()
>>> lcd.text_write_at(1, 1, 'Hello world')
>>>
```

More usage example in the [examples](examples/) folder

## [Functions prototypes](sm_lcd/README.md)
