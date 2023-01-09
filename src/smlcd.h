#ifndef __SM_LCD_H__
#define __SM_LCD_H__

#define HW_ADD 0x08
#define LCD_CMD_INST_WR 0x11
#define LCD_CMD_BUSY_RD 0x22
#define LCD_CMD_DATA_WR 0x33
#define LCD_CMD_DATA_RD 0x44

#define LCD_LINES_NO 4
#define LCD_COL_NO 20
#define LCD_SECOND_LINE_ADD_OFFSET 0x40

#define LCD_INST_CLR_DISP 0x01
#define LCD_INST_RET_HOME 0x02

#define LCD_INST_SET_DDR 0x80


#define UNUSED(X) (void)X      /* To avoid gcc/g++ warnings */

#define ERROR	-1
#define OK		0
#define FAIL	-1
#define ARG_CNT_ERR -2

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

enum
{
	I2C_RED_LED_ADD = 0,
	I2C_GREEN_LED_ADD,
	I2C_BLUE_LED_ADD,
	I2C_SW_MOM_ADD,
	I2C_SW_INT_ADD,
	I2C_SW_INT_EN_ADD,
	I2C_LCD_DATA,
	I2C_LCD_CMD,
	I2C_LCD_BL,

	I2C_MEM_CPU_RESET = 0xaa,
	I2C_REVISION_HW_MAJOR_MEM_ADD ,
	I2C_REVISION_HW_MINOR_MEM_ADD,
	I2C_REVISION_MAJOR_MEM_ADD,
	I2C_REVISION_MINOR_MEM_ADD,
	SLAVE_BUFF_SIZE = 255
};



typedef struct
{
	const char *name;
	const int namePos;
	int (*pFunc)(int, char**);
	const char *help;
	const char *usage1;
	const char *usage2;
	const char *example;
} CliCmdType;

enum{
	RED = 0,
	GREEN,
	BLUE,
	COLOR_COUNT
};

extern const CliCmdType *gCmdArray[];

#endif