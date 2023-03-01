[!smlcd](../../images/sequent.jpg)

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
  * *value* command value, for example, Clear Display command value is 0x01
* Returns
  * none
  
#### *display_init()*
* Description
  * Default initialization for two or more lines display, not show cusor, no blinking cursor, no shifting. For custom initialization use *cmd()* function.
* Parameters
  * none
* Returns
  * none
  
#### *data_write(value)*
* Description
  * Write one byte of data to the display
* Parameters
  * *value* The byte that will be sent to the LCD display
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
  * Set cursor position, this function works for multiline display, with maximum 4 lines and 20 columns
* Parameters
  * *line* line number [1..4]
  * *column* column number [1..20]
* Returns
  * none  

#### *text_write(text)*
* Description
  * Write a text at the cursor's current position. The function does not check the text length
* Parameters  
  * *text* the string to be displayed 
* Returns
  * none

#### *text_write_at(line, column, text):*
* Description
  * Write a text at the specified position. The function does not check the text length
* Parameters
  * *line* dispaly line number [1..4]
  * *column* display column number [1..20]
  * *text* the string to be displayed 
* Returns
  * none

#### *bl_single(val)*
* Description
  * Set the single color dispaly backlight intensity
* Parameters
  * *val* intensity in precents [0..100]
* Returns
  * none

#### *bl_rgb(red, green, blue)*
* Description
  * Set the RGB diplay backlight intensity by color
* Parameters
  * *red* red color intensity [0..100]
  * *greeen* green color intensity [0..100]
  * *blue* blue color intensity [0..100]
* Returns
  * none

#### **
* Description
  * Set one relay state
* Parameters
  * none
* Returns
  * none


   
