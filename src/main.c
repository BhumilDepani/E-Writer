#include "stm32f4xx.h"
#include "ILI9341.c"

void msDelay(__IO  uint32_t count);

int main(void)
{
	while(1)
	{

	}
}

void msDelay(__IO uint32_t count)
{
		while(count--);
}
