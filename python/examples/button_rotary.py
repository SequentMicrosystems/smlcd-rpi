import sm_lcd
import time
import signal
import sys
import RPi.GPIO as GPIO

BUTTON_GPIO =  37

lcd = sm_lcd.SMlcd()


def display_buttons():
    val = lcd.get_all_buttons_int()
    text = ''
    for i in range(0, 6):
        if val & (1 << i) != 0:
            text = text + ' ^'
            if i == 0:  # left button resets the encoder value
                lcd.reset_encoder()
                val = val | 0x80  #  Simulate encoder interrupt
        else:
            text = text + ' _'
    lcd.text_write_at(4, 4, text)
    if val & 0x80 != 0:
        enc = lcd.get_encoder_val()
        text = str(enc) + '  '
        lcd.text_write_at(2,10, text)

   


if __name__ == '__main__':
    GPIO.setmode(GPIO.BOARD)
    GPIO.setup(BUTTON_GPIO, GPIO.IN, pull_up_down=GPIO.PUD_UP)
    lcd.display_init()
    lcd.bl_single(50)
    # write something
    lcd.text_write_at(1, 1, 'Push buttons...')
    lcd.text_write_at(2, 1, 'Encoder: 0')
    try:
        while True:
            time.sleep(0.2)
            if GPIO.input(BUTTON_GPIO) == 0:
                # print("Interrupted")
                display_buttons()
    except KeyboardInterrupt:
        pass
