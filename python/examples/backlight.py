import sm_lcd
import time

lcd = sm_lcd.SMlcd()

# automatic initialization
lcd.display_init()
# write something
lcd.text_write_at(1, 1, 'Backlight testing...')

for i in range(100):
    lcd.bl_rgb(i, i, i)
    time.sleep(0.01)

for i in range(100):
    lcd.bl_rgb(i, 0, 0)
    time.sleep(0.01)

for i in range(100):
    lcd.bl_rgb(0, i, 0)
    time.sleep(0.01)

for i in range(100):
    lcd.bl_rgb(0, 0, i)
    time.sleep(0.01)

lcd.bl_single(50)
lcd.text_write_at(2,  6, '!!!DONE!!!')