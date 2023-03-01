#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "smlcd.h"
#include "comm.h"
#include "thread.h"

#define VERSION_BASE	(int)1
#define VERSION_MAJOR	(int)0
#define VERSION_MINOR	(int)0

char *warranty =
	"	       Copyright (c) 2016-2023 Sequent Microsystems\n"
		"                                                             \n"
		"		This program is free software; you can redistribute it and/or modify\n"
		"		it under the terms of the GNU Leser General Public License as published\n"
		"		by the Free Software Foundation, either version 3 of the License, or\n"
		"		(at your option) any later version.\n"
		"                                    \n"
		"		This program is distributed in the hope that it will be useful,\n"
		"		but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
		"		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
		"		GNU Lesser General Public License for more details.\n"
		"			\n"
		"		You should have received a copy of the GNU Lesser General Public License\n"
		"		along with this program. If not, see <http://www.gnu.org/licenses/>.";

void usage(void)
{
	int i = 0;
	while (gCmdArray[i] != NULL)
	{
		if (gCmdArray[i]->name != NULL)
		{
			if (strlen(gCmdArray[i]->usage1) > 2)
			{
				printf("%s", gCmdArray[i]->usage1);
			}
			if (strlen(gCmdArray[i]->usage2) > 2)
			{
				printf("%s", gCmdArray[i]->usage2);
			}
		}
		i++;
	}
	printf("Type smlcd -h <command> for more help\n");
}

int doBoardInit(void)
{
	int dev = 0;
	int add = 0;
	uint8_t buff[8];

	add = HW_ADD;
	dev = i2cSetup(add);
	if (dev == -1)
	{
		return ERROR;
	}
	if (ERROR == i2cMem8Read(dev, I2C_REVISION_MAJOR_MEM_ADD, buff, 1))
	{
		printf("LCD Display Board display did not detected!\n");
		return ERROR;
	}
	return dev;
}

int boardCheck(void)
{
	int dev = 0;
	int add = 0;
	uint8_t buff[8];

	add = HW_ADD;
	dev = i2cSetup(add);
	if (dev == -1)
	{
		return ERROR;
	}
	if (ERROR == i2cMem8Read(dev, I2C_REVISION_MAJOR_MEM_ADD, buff, 1))
	{

		return ERROR;
	}
	return OK;
}
static int doHelp(int argc, char *argv[]);
const CliCmdType CMD_HELP =
{
	"-h",
	1,
	&doHelp,
	"\t-h		Display the list of command options or one command option details\n",
	"\tUsage:		smlcd -h    Display command options list\n",
	"\tUsage:		smlcd -h <param>   Display help for <param> command option\n",
	"\tExample:	smlcd -h rread    Display help for \"rread\" command option\n"};

static int doHelp(int argc, char *argv[])
{
	int i = 0;
	if (argc == 3)
	{
		while (NULL != gCmdArray[i])
		{
			if (gCmdArray[i]->name != NULL)
			{
				if (strcasecmp(argv[2], gCmdArray[i]->name) == 0)
				{
					printf("%s%s%s%s", gCmdArray[i]->help, gCmdArray[i]->usage1,
						gCmdArray[i]->usage2, gCmdArray[i]->example);
					break;
				}
			}
			i++;
		}
		if (NULL == gCmdArray[i])
		{
			printf("Option \"%s\" not found\n", argv[2]);
			i = 0;
			while (NULL != gCmdArray[i])
			{
				if (gCmdArray[i]->name != NULL)
				{
					printf("%s", gCmdArray[i]->help);
					break;
				}
				i++;
			}
		}
		else
		{
			return ERROR;
		}
	}
	else
	{
		i = 0;
		while (NULL != gCmdArray[i])
		{
			if (gCmdArray[i]->name != NULL)
			{
				printf("%s", gCmdArray[i]->help);
			}
			i++;
		}
	}
	return OK;
}

static int doVersion(int argc, char *argv[]);
const CliCmdType CMD_VERSION =
{
	"-v",
	1,
	&doVersion,
	"\t-v		Display the smlcd command version number\n",
	"\tUsage:		smlcd -v\n",
	"",
	"\tExample:	smlcd -v  Display the version number\n"};

static int doVersion(int argc, char *argv[])
{
	UNUSED(argc);
	UNUSED(argv);
	printf("smlcd v%d.%d.%d Copyright (c) 2016 - 2023 Sequent Microsystems\n",
	VERSION_BASE, VERSION_MAJOR, VERSION_MINOR);
	printf("\nThis is free software with ABSOLUTELY NO WARRANTY.\n");
	printf("For details type: smlcd -warranty\n");
	return OK;
}

static int doWarranty(int argc, char *argv[]);
const CliCmdType CMD_WAR =
{
	"-warranty",
	1,
	&doWarranty,
	"\t-warranty	Display the warranty\n",
	"\tUsage:		smlcd -warranty\n",
	"",
	"\tExample:	smlcd -warranty  Display the warranty text\n"};

static int doWarranty(int argc UNU, char* argv[] UNU)
{
	printf("%s\n", warranty);
	return OK;
}

static int doList(int argc, char *argv[]);
const CliCmdType CMD_LIST =
	{
		"-list",
		1,
		&doList,
		"\t-list:		List all display boards connected\n\t\t\treturn the # of boards and stack level for every board\n",
		"\tUsage:		smlcd -list\n",
		"",
		"\tExample:	smlcd -list display: 1,0 \n"};

static int doList(int argc, char *argv[])
{

	UNUSED(argc);
	UNUSED(argv);

	if (boardCheck() == OK)
	{
		printf("Display board detected\n");
	}
	else
	{
		printf("NO Dispaly board detected!\n");
	}
	return OK;
}

static int doBoard(int argc, char *argv[]);
const CliCmdType CMD_BOARD =
	{
		"board",
		1,
		&doBoard,
		"\tboard		Display the board status and firmware version number\n",
		"\tUsage:		smlcd board\n",
		"",
		"\tExample:	smlcd board  Display vcc, temperature, firmware version, battery voltage \n"};

static int doBoard(int argc, char *argv[])
{
	int dev = -1;
	u8 buff[5];
	int resp = 0;

	UNUSED(argv);
	if (argc != 2)
	{
		return ARG_CNT_ERR;
	}
	dev = doBoardInit();
	if (dev <= 0)
	{
		return ERROR;
	}

	resp = i2cMem8Read(dev, I2C_REVISION_MAJOR_MEM_ADD, buff, 2);
	if (FAIL == resp)
	{
		printf("Fail to read board info!\n");
		return ERROR;
	}
	printf("Firmware ver %02d.%02d,\n", (int)buff[0], (int)buff[1]);
	return OK;
}

static int doWriteCmd(int argc, char *argv[]);
const CliCmdType CMD_WR_CMD =
{
	"cmdwr",
	1,
	&doWriteCmd,
	"\tcmdwr		Send a command to display\n",
	"\tUsage:		smlcd cmdwr <cmd>\n",
	"",
	"\tExample:	smlcd cmdwr 1 -> Send clear display command\n"};

static int doWriteCmd(int argc, char *argv[])
{
	int dev = -1;
	u8 buff[5];
	int resp = 0;

	if (argc != 3)
	{
		return ARG_CNT_ERR;

	}
	dev = doBoardInit();
	if (dev <= 0)
	{
		exit(1);
	}
	resp = atoi(argv[2]);
	buff[0] = 0xff & resp;
	buff[1] = LCD_CMD_INST_WR;
	resp = i2cMem8Write(dev, I2C_LCD_DATA, buff, 2);
	if (FAIL == resp)
	{
		printf("Fail to write!\n");
		exit(1);
	}
	return OK;
}

static int doWriteData(int argc, char *argv[]);
const CliCmdType CMD_WR_DATA =
{
	"dtwr",
	1,
	&doWriteData,
	"\tdtwr		Send a byte of data to display\n",
	"\tUsage:		smlcd dtwr <cmd>\n",
	"",
	"\tExample:	smlcd dtwr 65 -> Send \"A\" char to display\n"};

static int doWriteData(int argc, char *argv[])
{
	int dev = -1;
	u8 buff[5];
	int resp = 0;

	if (argc != 3)
	{
		return ARG_CNT_ERR;
	}
	dev = doBoardInit();
	if (dev <= 0)
	{
		return ERROR;
	}
	resp = atoi(argv[2]);
	buff[0] = 0xff & resp;
	buff[1] = LCD_CMD_DATA_WR;
	resp = i2cMem8Write(dev, I2C_LCD_DATA, buff, 2);
	if (FAIL == resp)
	{
		printf("Fail to write!\n");
		return ERROR;
	}
	return OK;
}

static int doWriteText(int argc, char *argv[]);
const CliCmdType CMD_WR_TXT =
{
	"txtwr",
	1,
	&doWriteText,
	"\ttxtwr		Send a text to display\n",
	"\tUsage:		smlcd txtwr <text>\n",
	"",
	"\tExample:	smlcd txtwr Heatweb -> Write \"Heatweb\" text to display\n"};

static int doWriteText(int argc, char *argv[])
{
	int dev = -1;
	u8 buff[5];
	int resp = 0;
	unsigned int i = 0;
	int j = 0;

	if (argc < 3)
	{
		return ARG_CNT_ERR;
	}
	dev = doBoardInit();
	if (dev <= 0)
	{
		exit(1);
	}
	for (j = 2; j < argc; j++)
	{
		for (i = 0; i < strlen(argv[j]); i++)
		{
			//resp = argv[2]);
			buff[0] = 0xff & argv[j][i];
			buff[1] = LCD_CMD_DATA_WR;
			resp = i2cMem8Write(dev, I2C_LCD_DATA, buff, 2);
			if (FAIL == resp)
			{
				printf("Fail to write!\n");
				return ERROR;
			}
		}
		buff[0] = ' ';
		resp = i2cMem8Write(dev, I2C_LCD_DATA, buff, 2);
		if (FAIL == resp)
		{
			printf("Fail to write!\n");
			return ERROR;
		}
	}
	return OK;
}

int setCursor(int dev, int line, int column)
{
	u8 buff[5];
	int resp = 0;
	int address = 0;

	if (line < 1 || line > LCD_LINES_NO)
	{
		printf("Invald line number [1..%d]\n", LCD_LINES_NO);
		return ERROR;
	}
	if (column < 1 || column > LCD_COL_NO)
	{
		printf("Invald column number [1..%d]\n", LCD_COL_NO);
		return ERROR;
	}
	if (line == 2) //swap lines 3 and 2
	{
		line = 3;
	}
	else if (line == 3)
	{
		line = 2;
	}
	address = (line - 1) * LCD_COL_NO + (column - 1);
	if (line > 2)
	{
		address = LCD_SECOND_LINE_ADD_OFFSET + (line - 3) * LCD_COL_NO
			+ (column - 1);
	}
	buff[0] = 0xff & (address + LCD_INST_SET_DDR);
	buff[1] = LCD_CMD_INST_WR;
	resp = i2cMem8Write(dev, I2C_LCD_DATA, buff, 2);
	if (FAIL == resp)
	{
		printf("Fail to write!\n");
		return ERROR;
	}
	return OK;
}

static int doWriteTextAt(int argc, char *argv[]);
const CliCmdType CMD_WR_TXT_AT =
	{
		"txtwrat",
		1,
		&doWriteTextAt,
		"\ttxtwrat		Send a text to display at certain position\n",
		"\tUsage:		smlcd txtwrat <ine> <column> <text>\n",
		"",
		"\tExample:	smlcd txtwr 1 1 Heatweb -> Write \"Heatweb\" text to display at line 1 column 1\n"};

static int doWriteTextAt(int argc, char *argv[])
{
	int dev = -1;
	u8 buff[5];
	int resp = 0;
	unsigned int i = 0;
	int j = 0;
	int line = 0;
	int column = 0;
	int writePos = 0;

	if (argc < 5)
	{
		return ARG_CNT_ERR;
	}
	dev = doBoardInit();
	if (dev <= 0)
	{
		return ERROR;
	}
	line = atoi(argv[2]);
	column = atoi(argv[3]);
	if (OK != setCursor(dev, line, column))
	{
		return ERROR;
	}
	writePos = column;
	for (j = 4; j < argc; j++)
	{
		for (i = 0; i < strlen(argv[j]); i++)
		{
			if (writePos <= LCD_COL_NO)
			{
				//resp = argv[2]);
				buff[0] = 0xff & argv[j][i];
				buff[1] = LCD_CMD_DATA_WR;
				resp = i2cMem8Write(dev, I2C_LCD_DATA, buff, 2);
				if (FAIL == resp)
				{
					printf("Fail to write!\n");
					return ERROR;
				}
				writePos++;
			}
		}
		if (writePos <= LCD_COL_NO)
		{
			buff[0] = ' ';
			resp = i2cMem8Write(dev, I2C_LCD_DATA, buff, 2);
			if (FAIL == resp)
			{
				printf("Fail to write!\n");
				return ERROR;
			}
			writePos++;
		}
	}
	return OK;
}

static int doSetCursor(int argc, char *argv[]);
const CliCmdType CMD_SET_CURSOR =
{
	"crs",
	1,
	&doSetCursor,
	"\tcrs		Set cursor position for 4x20 character display\n",
	"\tUsage:		smlcd crs <line> <column>\n",
	"",
	"\tExample:	smlcd crs 1 10 -> Set cursor position at line 1 column 10\n"};

static int doSetCursor(int argc, char *argv[])
{
	int dev = -1;
	int line = 0;
	int column = 0;

	if (argc != 4)
	{
		return ARG_CNT_ERR;
	}
	dev = doBoardInit();
	if (dev <= 0)
	{
		return ERROR;
	}
	line = atoi(argv[2]);
	column = atoi(argv[3]);
	return setCursor(dev, line, column);
}

static int doWriteBacklight(int argc, char *argv[]);
const CliCmdType CMD_WR_BL =
{
	"blwr",
	1,
	&doWriteBacklight,
	"\tblwr		Set the backlight intensity [0..100]\n",
	"\tUsage:		smlcd blwr <bl>\n",
	"\tUsage:		smlcd blwr <red> <green> <blue>\n",
	"\tExample:	smlcd blwr 50 -> Set backlight half intensity\n"};

static int doWriteBacklight(int argc, char *argv[])
{
	int dev = -1;
	u8 buff[5];
	int resp = 0;

	if (argc != 3 && argc != 5)
	{
		return ARG_CNT_ERR;
	}
	dev = doBoardInit();
	if (dev <= 0)
	{
		return ERROR;
	}

	resp = atoi(argv[2]);
	if (resp < 0 || resp > 100)
	{
		printf("Invalid backligt intensity value [0..100]\n");
		return ERROR;
	}
	buff[0] = 0xff & resp;
	if (argc > 3)
	{
		resp = atoi(argv[3]);
		if (resp < 0 || resp > 100)
		{
			printf("Invalid backligt intensity value [0..100]\n");
			return ERROR;
		}
		buff[1] = 0xff & resp;

		resp = atoi(argv[4]);
		if (resp < 0 || resp > 100)
		{
			printf("Invalid backligt intensity value [0..100]\n");
			return ERROR;
		}
		buff[2] = 0xff & resp;
		resp = i2cMem8Write(dev, I2C_LCD_BL, buff, 3);
	}
	else
	{
		resp = i2cMem8Write(dev, I2C_LCD_BL, buff, 1);
	}
	if (FAIL == resp)
	{
		printf("Fail to write!\n");
		return ERROR;
	}
	return OK;
}

static int doReadButton(int argc, char *argv[]);
const CliCmdType CMD_READ_BUTTON =
{
	"swrd",
	1,
	&doReadButton,
	"\tswrd		Read one push button or all as a bitmap\n",
	"\tUsage:		smlcd swrd <sw>\n",
	"\tUsage:		smlcd swrd\n",
	"\tExample:	smlcd swrd 1 -> Read button no 1\n"};

static int doReadButton(int argc, char *argv[])
{
	int dev = -1;
	u8 buff[2];
	int resp = 0;
	int sw = 0;

	if (argc != 2 && argc != 3)
	{
		return ARG_CNT_ERR;
	}
	dev = doBoardInit();
	if (dev <= 0)
	{
		return ERROR;
	}
	resp = i2cMem8Read(dev, I2C_SW_MOM_ADD, buff, 1);
	if (FAIL == resp)
	{
		printf("Fail to read!\n");
		return ERROR;
	}
	if (argc == 3)
	{
		sw = atoi(argv[2]);
		if (sw < 1 || sw > 6)
		{
			printf("Invalid sw no! [1..6]\n");
			return ERROR;
		}
		if (buff[0] & (1 << (sw - 1)))
		{
			printf("1\n");
		}
		else
		{
			printf("0\n");
		}
	}
	else
	{
		printf("%d\n", (int)buff[0]);
	}
	return OK;
}

static int doReadButtonInt(int argc, char *argv[]);
const CliCmdType CMD_READ_BUTTON_INT =
	{
		"swird",
		1,
		&doReadButtonInt,
		"\tswird		Read one push button interrupt flag or all as a bitmap and clear them\n",
		"\tUsage:		smlcd swird <sw>\n",
		"\tUsage:		smlcd swird\n",
		"\tExample:	smlcd swird 1 -> Read button no 1 interrupt flag\n"};

static int doReadButtonInt(int argc, char *argv[])
{
	int dev = -1;
	u8 buff[2];
	int resp = 0;
	int sw = 0;

	if (argc != 2 && argc != 3)
	{
		return ARG_CNT_ERR;
	}
	dev = doBoardInit();
	if (dev <= 0)
	{
		return ERROR;
	}
	resp = i2cMem8Read(dev, I2C_SW_INT_ADD, buff, 1);
	if (FAIL == resp)
	{
		printf("Fail to read!\n");
		return ERROR;
	}
	if (argc == 3)
	{
		sw = atoi(argv[2]);
		if (sw < 1 || sw > 6)
		{
			printf("Invalid sw no! [1..6]\n");
			return ERROR;
		}
		if (buff[0] & (1 << (sw - 1)))
		{
			printf("1\n");
		}
		else
		{
			printf("0\n");
		}
		buff[0] &= ~ (1 << (sw - 1));
	}
	else
	{
		printf("%d\n", (int)buff[0]);
		buff[0] = 0;
	}
	resp = i2cMem8Write(dev, I2C_SW_INT_ADD, buff, 1);
	if (FAIL == resp)
	{
		printf("Fail to write!\n");
		return ERROR;
	}
	return OK;
}

static int doReadRotary(int argc, char *argv[]);
const CliCmdType CMD_READ_ROTARY =
{
	"rotrd",
	1,
	&doReadRotary,
	"\trotrd		Read rotary value\n",
	"\tUsage:		smlcd rotrd \n",
	"",
	"\tExample:	smlcd rotrd -> Read rotary value\n"};

static int doReadRotary(int argc, char *argv[])
{
	int dev = -1;
	u8 buff[2];
	int resp = 0;
	int16_t val = 0;
	UNUSED(argv);

	if (argc != 2)
	{
		return ARG_CNT_ERR;
	}
	dev = doBoardInit();
	if (dev <= 0)
	{
		return ERROR;
	}
	resp = i2cMem8Read(dev, I2C_ROTARY_VAL, buff, 2);
	if (FAIL == resp)
	{
		printf("Fail to read!\n");
		return ERROR;
	}
	memcpy(&val, buff, 2);
	printf("%d\n", val);
	return OK;
}

static int doResetRotary(int argc, char *argv[]);
const CliCmdType CMD_RST_ROTARY =
{
	"rotrst",
	1,
	&doResetRotary,
	"\trotrst		Reset rotary value\n",
	"\tUsage:		smlcd rotrst \n",
	"",
	"\tExample:	smlcd rotrst -> Reset rotary value\n"};

static int doResetRotary(int argc, char *argv[])
{
	int dev = -1;
	u8 buff[2];
	int resp = 0;
	
	UNUSED(argv);

	if (argc != 2)
	{
		return ARG_CNT_ERR;
	}
	dev = doBoardInit();
	if (dev <= 0)
	{
		return ERROR;
	}
	buff[0] = RESET_ROTARY_KEY;
	resp = i2cMem8Write(dev, I2C_ROTARY_RESET, buff, 1);
	if (FAIL == resp)
	{
		printf("Fail to write!\n");
		return ERROR;
	}
	return OK;
}


const CliCmdType *gCmdArray[] =
{
	&CMD_VERSION,
	&CMD_HELP,
	&CMD_WAR,
	&CMD_LIST,
	&CMD_BOARD,
	&CMD_WR_CMD,
	&CMD_WR_DATA,
	&CMD_WR_TXT,
	&CMD_WR_TXT_AT,
	&CMD_SET_CURSOR,
	&CMD_WR_BL,
	&CMD_READ_BUTTON,
	&CMD_READ_BUTTON_INT,
	&CMD_READ_ROTARY,
	&CMD_RST_ROTARY,
	NULL}; //null terminated array of cli structure pointers

int main(int argc, char *argv[])
{
	int i = 0;
	int ret = 0;

	if (argc == 1)
	{
		usage();
		return -1;
	}
	while (NULL != gCmdArray[i])
	{
		if ( (gCmdArray[i]->name != NULL) && (gCmdArray[i]->namePos < argc))
		{
			if (strcasecmp(argv[gCmdArray[i]->namePos], gCmdArray[i]->name) == 0)
			{
				ret = gCmdArray[i]->pFunc(argc, argv);
				if (ARG_CNT_ERR == ret)
				{
					printf(
						"Invalid arguments number, type \"smlcd -h %s\" for details\n",
						gCmdArray[i]->name);
				}
				return ret;
			}
		}
		i++;
	}
	printf("Invalid command option\n");
	usage();

	return -1;
}
