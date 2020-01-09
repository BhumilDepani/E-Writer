#include "stm32f4xx.h"
#include "ILI9341.h"

void msDelay(__IO  uint32_t count);
void usDelay(__IO  uint16_t count)
{
	uint32_t ncount=17*count;
	while(ncount--);
}

int main(void)
{
	GPIO_InitTypeDef GPIO_InitPins;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	GPIO_InitPins.GPIO_Mode=GPIO_Mode_OUT;
	    GPIO_InitPins.GPIO_OType=GPIO_OType_PP;
	    GPIO_InitPins.GPIO_Pin=GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	    GPIO_InitPins.GPIO_PuPd=GPIO_PuPd_DOWN;
	    GPIO_InitPins.GPIO_Speed=GPIO_Speed_50MHz;
	    GPIO_Init(GPIOD,&GPIO_InitPins);


	TFT_init();
	while(1)
	{
		TFT_fill(Green);
		GPIO_WriteBit(GPIOD,GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15,SET);
		    msDelay(1000);
		    GPIO_WriteBit(GPIOD,GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15,RESET);
		    		    msDelay(1000);
	}
}

void msDelay(__IO uint32_t count)
{
	uint32_t number=count*16800;
		while(number--)
		{

		};
}
