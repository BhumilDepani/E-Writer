#include "stm32f4xx.h"
#include "ILI9341.c"

void msDelay(__IO  uint32_t count);

int main(void)
{
	TFT_init();
	while(1)
	{

	}
}

void msDelay(__IO uint32_t count)
{
	uint32_t number=count*16800;
		while(number--);
}
