import sm_lcd
import time

lcd = sm_lcd.SMlcd()

# manual initialization
# initialisation commands
lcd.cmd(60)  # Function set
time.sleep(0.01)
lcd.cmd(60)  # Function set
time.sleep(0.01)
lcd.cmd(15)  # Display ON/OFF
time.sleep(0.01)
lcd.cmd(6)  # Entry mode set
time.sleep(0.01)
lcd.cmd(1)  # clear display
time.sleep(0.01)

lcd.text_write_at(1, 5, 'Manual init')
lcd.cursor_set(2, 1)
time.sleep(1)
for i in range(20):
    lcd.data_write(61)  # '='
    time.sleep(0.2)

for i in range(20):
    lcd.text_write_at(2, i+1, ' ')
    time.sleep(0.2)

# automatic initialization
lcd.display_init()

# replace the folowing line with your greetings message
lcd.text_write_at(1, 3, 'Default init')
lcd.cursor_set(2, 1)
time.sleep(1)
for i in range(20):
    lcd.data_write(61)  # '='
    time.sleep(0.2)

# lcd.cursor_set(2, 1)
for i in range(20):
    lcd.text_write_at(2, i+1, ' ')
    time.sleep(0.2)

lcd.text_write_at(4, 5, '!!!DONE!!!')
