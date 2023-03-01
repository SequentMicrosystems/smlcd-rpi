[![smlcd-rpi](../../pictures/sequent.jpg)](https://www.sequentmicrosystems.com)

# sm-lcd libray documentation

### *class sm_lcd.SMlcd(i2c = 1)*
* Description
  * Init the SMlcd object and check the card presence 
* Parameters
  * i2c : I2C port number, 1 - Raspberry default, 7 - rock pi 4, etc.
* Returns 
  * card object
  
#### *busy()*
* Description
  * Get the LCD Display busy flag
* Parameters  
  * none
* Returns
  * 1 if the LCD is busy; 0 otherwise
  
#### *cmd(value)*
* Description
  * Send a command to the LCD Display
* Parameters
  * *value*: command value, for example, Clear Display command value is 0x01
* Returns
  * none
  
#### *display_init()*
* Description
  * Default initialization for two or more lines display, not show cursor, no blinking cursor, no shifting. For custom initialization use *cmd()* function.
* Parameters
  * none
* Returns
  * none
  
#### *data_write(value)*
* Description
  * Write one byte of data to the display
* Parameters
  * *value*: The byte that will be sent to the LCD display
* Returns
  * none  
  
#### *data_read()*
* Description
  * Read one byte of data from the display
* Parameters
  * none
* Returns
  * One byte of data
  
#### *cursor_set(line, column)*
* Description
  * Set cursor position, this function works for multiline display, with a maximum of 4 lines and 20 columns
* Parameters
  * *line*: line number [1..4]
  * *column*: column number [1..20]
* Returns
  * none  

#### *text_write(text)*
* Description
  * Write a text at the cursor's current position. The function does not check the text length
* Parameters  
  * *text*: the string to be displayed 
* Returns
  * none

#### *text_write_at(line, column, text):*
* Description
  * Write a text at the specified position. The function does not check the text length
* Parameters
  * *line* display line number [1..4]
  * *column* display column number [1..20]
  * *text* the string to be displayed 
* Returns
  * none

#### *bl_single(val)*
* Description
  * Set the single-color display backlight intensity
* Parameters
  * *val*: intensity in precentage [0..100]
* Returns
  * none

#### *bl_rgb(red, green, blue)*
* Description
  * Set the RGB display backlight intensity by color
* Parameters
  * *red*: red color intensity [0..100]
  * *green*: green color intensity [0..100]
  * *blue*: blue color intensity [0..100]
* Returns
  * none

#### *get_button(button)*
* Description
  * Get one pushbutton current state 
* Parameters
  * *button*: button number [1..6]
* Returns
  * button state: 1 - button is pressed; 0 - otherwise

#### *get_all_buttons()*
* Description
  * Returns the state of all 6 buttons as a bitmap
* Parameters
  * none
* Returns
  * all buttons state [0x00..0x3f]

#### *get_button_int(button)*
* Description
  * Return 1 if a button has been pushed since the last call of this function. This function tells you if a button has generated an interrupt.
* Parameters
  * *button*: button number [1..6]
* Returns
  * 1 - the button has been pushed since last read; 0 - if not 

#### *get_all_buttons_int()*
* Description
  * Returns the interrupt flag for all buttons and the rotary encoder as a bitmap, buttons bits 0..5, encoder change interrupt bot 7. 
* Parameters
  * none
* Returns
  * Interrupt flags 

#### *get_encoder_int()*
* Description
  * Get the encoder *on change* interrupt flag 
* Parameters
  * none
* Returns
  * 1 - encoder value has been changed; 0 - if not 

#### *get_encoder_val()*
* Description
  * Get the encoder accumulated value as a 16 bits signed integer
* Parameters
  * none
* Returns
  * encoder value (-32767..32767)

#### *reset_encoder()*
* Description
  * Reset the encoder value
* Parameters
  * none
* Returns
  * none

   
