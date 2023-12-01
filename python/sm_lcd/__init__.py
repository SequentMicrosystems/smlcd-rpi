import smbus2
import time

__version__ = "1.0.1"
_I2C_HW_ADDRESS = 0x08
_I2C_SW_MOM_ADD = 3
_I2C_SW_INT_ADD = 4
_I2C_LCD_DATA = 6
_I2C_LCD_CMD = 7
_I2C_LCD_BL = 8
_I2C_LCD_BL_G = 9
_I2C_LCD_BL_B = 10
_I2C_ROTARY_VAL = 11
_I2C_ROTARY_RESET = _I2C_ROTARY_VAL + 2
_I2C_REVISION_HW_MAJOR_MEM_ADD = 171

_LCD_INST_WR = 0x11
_LCD_BUSY_RD = 0x22
_LCD_DATA_WR = 0x33
_LCD_DATA_RD = 0x44

_LCD_LINES_NO = 4
_LCD_COL_NO = 20
_LCD_SECOND_LINE_ADD_OFFSET = 0x40

_LCD_INST_SET_DDR = 0x80

_BUSY_RETRY_COUNT = 3


class SMlcd:
    def __init__(self, i2c=1):
        self._i2c_bus_no = i2c
        bus = smbus2.SMBus(self._i2c_bus_no)
        try:
            self._card_rev_major = bus.read_byte_data(_I2C_HW_ADDRESS, _I2C_REVISION_HW_MAJOR_MEM_ADD)
        except Exception as e:
            bus.close()
            raise Exception("Fail to read with exception " + str(e))
        bus.close()

    def busy(self):
        bus = smbus2.SMBus(self._i2c_bus_no)
        try:
            bus.write_byte_data(_I2C_HW_ADDRESS, _I2C_LCD_CMD, _LCD_BUSY_RD)
            time.sleep(0.01)
            ret = bus.read_byte_data(_I2C_HW_ADDRESS, _I2C_LCD_DATA)
        except Exception as e:
            bus.close()
            raise Exception("Fail to write with exception " + str(e))
        bus.close()
        return 0x80 & ret

    def cmd(self, value):
        bus = smbus2.SMBus(self._i2c_bus_no)
        try:
            bus.write_byte_data(_I2C_HW_ADDRESS, _I2C_LCD_DATA, value)
            bus.write_byte_data(_I2C_HW_ADDRESS, _I2C_LCD_CMD, _LCD_INST_WR)
        except Exception as e:
            bus.close()
            raise Exception("Fail to write with exception " + str(e))
        bus.close()

    def display_init(self):
        self.cmd(60)
        time.sleep(0.01)
        self.cmd(60)
        time.sleep(0.01)
        self.cmd(12)
        time.sleep(0.01)
        self.cmd(6)
        time.sleep(0.01)

        # clear display
        retry = 0
        while self.busy() != 0 and retry < _BUSY_RETRY_COUNT:
            retry += 1
        self.cmd(1)
        time.sleep(0.01)

    def data_write(self, value):
        bus = smbus2.SMBus(self._i2c_bus_no)
        try:
            bus.write_byte_data(_I2C_HW_ADDRESS, _I2C_LCD_DATA, value)
            bus.write_byte_data(_I2C_HW_ADDRESS, _I2C_LCD_CMD, _LCD_DATA_WR)
        except Exception as e:
            bus.close()
            raise Exception("Fail to write with exception " + str(e))
        bus.close()

    def data_read(self):
        bus = smbus2.SMBus(self._i2c_bus_no)
        try:
            bus.write_byte_data(_I2C_HW_ADDRESS, _I2C_LCD_CMD, _LCD_DATA_RD)
            resp = bus.read_byte_data(_I2C_HW_ADDRESS, _I2C_LCD_DATA)
        except Exception as e:
            bus.close()
            raise Exception("Fail to write with exception " + str(e))
        bus.close()
        return resp

    def cursor_set(self, line, column):
        if line < 1 or line > 4:
            raise ValueError('Invalid line [1..4]!')
        if column < 1 or column > 20:
            raise ValueError('Invalid column [1..20]!')
        retry = 0
        while self.busy() != 0 and retry < _BUSY_RETRY_COUNT:
            retry += 1
        # swap line 2 and 3
        line_i = line
        if line_i == 2:
            line_i = 3
        else:
            if line_i == 3:
                line_i = 2
        address = (line_i - 1) * _LCD_COL_NO + column - 1
        if line_i > 2:
            address = (line_i - 3) * _LCD_COL_NO + _LCD_SECOND_LINE_ADD_OFFSET + column - 1
        self.cmd((0x7f & address) | _LCD_INST_SET_DDR)

    def text_write(self, text):
        bus = smbus2.SMBus(self._i2c_bus_no)
        try:
            for char in text:
                bus.write_byte_data(_I2C_HW_ADDRESS, _I2C_LCD_DATA, ord(char))
                bus.write_byte_data(_I2C_HW_ADDRESS, _I2C_LCD_CMD, _LCD_DATA_WR)
        except Exception as e:
            bus.close()
            raise Exception("Fail to write with exception " + str(e))
        bus.close()

    def text_write_at(self, line, column, text):
        self.cursor_set(line, column)
        self.text_write(text)

    def bl_single(self, val):
        bus = smbus2.SMBus(self._i2c_bus_no)
        try:
            bus.write_byte_data(_I2C_HW_ADDRESS, _I2C_LCD_BL, 0xff & val)
        except Exception as e:
            bus.close()
            raise Exception("Fail to write with exception " + str(e))
        bus.close()

    def bl_rgb(self, red, green, blue):
        bus = smbus2.SMBus(self._i2c_bus_no)
        try:
            bus.write_byte_data(_I2C_HW_ADDRESS, _I2C_LCD_BL, 0xff & red)
            bus.write_byte_data(_I2C_HW_ADDRESS, _I2C_LCD_BL_G, 0xff & green)
            bus.write_byte_data(_I2C_HW_ADDRESS, _I2C_LCD_BL_B, 0xff & blue)
        except Exception as e:
            bus.close()
            raise Exception("Fail to write with exception " + str(e))
        bus.close()

    def get_button(self, button):
        if button < 1 or button > 6:
            raise ValueError('Invalid button number must be [1..6]!')
        bus = smbus2.SMBus(self._i2c_bus_no)
        try:
            val = bus.read_byte_data(_I2C_HW_ADDRESS, _I2C_SW_MOM_ADD)
        except Exception as e:
            bus.close()
            raise Exception("Fail to write with exception " + str(e))
        bus.close()
        if val & (1 << button -1) != 0:
            return 1
        return 0

    def get_all_buttons(self):
        bus = smbus2.SMBus(self._i2c_bus_no)
        try:
            val = bus.read_byte_data(_I2C_HW_ADDRESS, _I2C_SW_MOM_ADD)
        except Exception as e:
            bus.close()
            raise Exception("Fail to write with exception " + str(e))
        bus.close()
        return val

    def get_button_int(self, button):
        if button < 1 or button > 6:
            raise ValueError('Invalid button number must be [1..6]!')
        bus = smbus2.SMBus(self._i2c_bus_no)
        try:
            val = bus.read_byte_data(_I2C_HW_ADDRESS, _I2C_SW_INT_ADD)
            clr = val & ~(1 << (button - 1))
            bus.write_byte_data(_I2C_HW_ADDRESS, _I2C_SW_INT_ADD, clr)
        except Exception as e:
            bus.close()
            raise Exception("Fail to write with exception " + str(e))
        bus.close()
        if val & (1 << (button -1)) != 0:
            return 1
        return 0

    def get_all_buttons_int(self):
        bus = smbus2.SMBus(self._i2c_bus_no)
        try:
            val = bus.read_byte_data(_I2C_HW_ADDRESS, _I2C_SW_INT_ADD)
            bus.write_byte_data(_I2C_HW_ADDRESS, _I2C_SW_INT_ADD, 0)
        except Exception as e:
            bus.close()
            raise Exception("Fail to write with exception " + str(e))
        bus.close()
        return val

    def get_encoder_int(self):
        bus = smbus2.SMBus(self._i2c_bus_no)
        try:
            val = bus.read_byte_data(_I2C_HW_ADDRESS, _I2C_SW_INT_ADD)
            clr = 0x7f
            bus.write_byte_data(_I2C_HW_ADDRESS, _I2C_SW_INT_ADD, clr)
        except Exception as e:
            bus.close()
            raise Exception("Fail to write with exception " + str(e))
        bus.close()
        if val & 0x80 != 0:
            return 1
        return 0

    def get_encoder_val(self):
        bus = smbus2.SMBus(self._i2c_bus_no)
        try:
            buff = bus.read_i2c_block_data(_I2C_HW_ADDRESS,_I2C_ROTARY_VAL, 2)
            count = int.from_bytes(buff, "little")
            if count >= 32768:
                count = count - 65536;
        except Exception as e:
            bus.close()
            raise Exception("Fail to read with exception " + str(e))
        bus.close()
        return count

    def reset_encoder(self):
        bus = smbus2.SMBus(self._i2c_bus_no)
        try:
            bus.write_byte_data(_I2C_HW_ADDRESS, _I2C_ROTARY_RESET, 0xaa)
        except Exception as e:
            bus.close()
            raise Exception("Fail to write with exception " + str(e))
        bus.close()
