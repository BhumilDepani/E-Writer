#include "stm32f4xx.h"
#include "FontASCII.c"

static void LCD_PinsConfiguration(void);
void msDelay(__IO  uint32_t count);
static void LCD_Initialization(void);
static void LCD_WriteData(uint16_t data);
static void LCD_WriteIndex(uint16_t index);
static void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue);
static void LCD_SetCursor(uint16_t Xpos,uint16_t Ypos);
static void LCD_Clear(uint16_t color);
static void LCD_SetPoint(uint16_t Xpos,uint16_t Ypos,uint16_t color);
static void PutChar(uint16_t Xpos,uint16_t Ypos,uint8_t ASCII, uint16_t color, uint16_t bkcolor);
static void GUI_Text(uint16_t Xpos, uint16_t Ypos, char *str, uint16_t color, uint16_t bkcolor);

#define LCD_REG (*((volatile unsigned short*) 0x60000000))
#define LCD_RAM (*((volatile unsigned short*) 0x60020000))

#define MAX_X 320
#define MAX_Y 240

#define White	0xFFFF
#define Black	0x0000
#define Gray	0xF7DE
#define Blue	0x001F
#define Blue2	0x051F
#define Red		0xF800
#define Magenta 0xF81F
#define Green	0x07E0
#define Cyan 	0x7FFF
#define Yellow  0xFFE0

GPIO_InitTypeDef GPIO_InitStructure;
FSMC_NORSRAMInitTypeDef FSMC_NORSRAMInitStructure;
FSMC_NORSRAMTimingInitTypeDef FSMC_NORSRAMTimingInitStructure;

static void LCD_PinsConfiguration(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC,ENABLE);

	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOD,&GPIO_InitStructure);

	GPIO_ResetBits(GPIOD,GPIO_Pin_7);

	GPIO_PinAFConfig(GPIOD,GPIO_PinSource0,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource1,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource4,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource10,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource11,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_FSMC);

	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOD,&GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOE,GPIO_PinSource7,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource8,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource10,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource12,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource14,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource15,GPIO_AF_FSMC);

	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOE,&GPIO_InitStructure);

	//msDelay(168000);

	FSMC_NORSRAMTimingInitStructure.FSMC_AccessMode=FSMC_AccessMode_A;
	FSMC_NORSRAMTimingInitStructure.FSMC_AddressHoldTime=0;
	FSMC_NORSRAMTimingInitStructure.FSMC_AddressSetupTime=0x0F;
	FSMC_NORSRAMTimingInitStructure.FSMC_BusTurnAroundDuration=0;
	FSMC_NORSRAMTimingInitStructure.FSMC_CLKDivision=0;
	FSMC_NORSRAMTimingInitStructure.FSMC_DataLatency=0;
	FSMC_NORSRAMTimingInitStructure.FSMC_DataSetupTime=5;

	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable;
	FSMC_NORSRAMInitStructure.FSMC_Bank=FSMC_Bank1_NORSRAM1;
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode=FSMC_BurstAccessMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux=FSMC_DataAddressMux_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode=FSMC_ExtendedMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth=FSMC_MemoryDataWidth_16b;
	FSMC_NORSRAMInitStructure.FSMC_MemoryType=FSMC_MemoryType_SRAM;
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct=&FSMC_NORSRAMTimingInitStructure;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal=FSMC_WaitSignal_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive=FSMC_WaitSignalActive_BeforeWaitState;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity=FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_WrapMode=FSMC_WrapMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst=FSMC_WriteBurst_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation=FSMC_WriteOperation_Enable;
	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1,ENABLE);
}

static void LCD_Initialization(void)
{
	LCD_PinsConfiguration();

	LCD_WriteReg(0x0003,1<<12);
	LCD_WriteReg(0x000c,0x0001);
	msDelay(168000);
	LCD_WriteReg(0x0010,0x1590);
	LCD_WriteReg(0x0011,0x0227);
	msDelay(168000);
	LCD_WriteReg(0x0012,0x009c);
	msDelay(168000);
	LCD_WriteReg(0x0013,0x1900);
	LCD_WriteReg(0x0029,0x0023);
	LCD_WriteReg(0x002b,0x000e);
	msDelay(168000);
	LCD_WriteReg(0x0030,0x0007);
	LCD_WriteReg(0x0031,0x0707);
	LCD_WriteReg(0x0032,0x0006);
	LCD_WriteReg(0x0035,0x0704);
	LCD_WriteReg(0x0036,0x1f04);
	LCD_WriteReg(0x0037,0x0004);
	LCD_WriteReg(0x0038,0x0000);
	LCD_WriteReg(0x0039,0x0706);
	LCD_WriteReg(0x003c,0x0701);
	LCD_WriteReg(0x003d,0x000f);
	msDelay(168000);
	LCD_WriteReg(0x0051,0x00ef);
	LCD_WriteReg(0x0052,0x0000);
	LCD_WriteReg(0x0053,0x013f);
	LCD_WriteReg(0x0060,0x2700);
	LCD_WriteReg(0x0061,0x0001);
	LCD_WriteReg(0x0090,0x0010);
	LCD_WriteReg(0x0095,0x0110);
	LCD_WriteReg(0x0007,0x0133);
	msDelay(168000);
}

static void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue)
{
	LCD_WriteIndex(LCD_Reg);
	LCD_WriteData(LCD_RegValue);
}

static void LCD_WriteIndex(uint16_t index)
{
	LCD_REG=index;
}

static void LCD_WriteData(uint16_t data)
{
	LCD_RAM=data;
}

static void LCD_SetCursor(uint16_t Xpos,uint16_t Ypos)
{
	uint16_t temp;
	Ypos= (MAX_Y-1)-Ypos;
	temp=Ypos;
	Ypos=Xpos;
	Xpos=temp;

	LCD_WriteReg(0x0020,Xpos);
	LCD_WriteReg(0x0021,Ypos);
}

static void LCD_Clear(uint16_t color)
{
	uint32_t index=0;
	LCD_SetCursor(0,0);
	LCD_WriteIndex(0x0022);
	for(index=0;index<MAX_X*MAX_Y;index++)
	{
		LCD_WriteData(color);
	}
}

static void LCD_SetPoint(uint16_t Xpos,uint16_t Ypos,uint16_t color)
{
	if(Xpos>=MAX_X || Ypos>=MAX_Y)
	{
		return;
	}
	LCD_SetCursor(Xpos,Ypos);
	LCD_WriteReg(0x0022,color);
}

static void PutChar(uint16_t Xpos,uint16_t Ypos,uint8_t ASCII, uint16_t color, uint16_t bkcolor)
{
	uint16_t i,j;
	uint8_t buff[16],temp_char;
	GetASCIICode(buff,ASCII);
	for(i=0;i<16;i++)
	{
		temp_char=buff[i];
		for(j=0;j<8;j++)
		{
			if((temp_char>>(7-j)) & 1)
			{
				LCD_SetPoint(Xpos+j,Ypos+i,color);
			}
			else
			{
				LCD_SetPoint(Xpos+j,Ypos+i,bkcolor);
			}

		}
	}
}

static void GUI_Text(uint16_t Xpos, uint16_t Ypos, char *str, uint16_t color, uint16_t bkcolor)
{
	uint8_t tempChar;
		do
		{
			tempChar=*str++;
			PutChar(Xpos,Ypos,tempChar,color,bkcolor);
			if(Xpos < MAX_X-8)
			{
				Xpos +=8;
			}
			else if(Ypos < MAX_Y-16)
			{
				Xpos=0;
				Ypos += 16;
			}
			else
			{
				Xpos=0;
				Ypos=0;
			}
		}while(*str != 0);
}
