#include "stm32f4xx.h"

GPIO_InitTypeDef GPIO_InitLED;
EXTI_InitTypeDef EXTI_InitSwitch;
NVIC_InitTypeDef NVIC_InitSwitch;
int i=0;

void msDelay(__IO uint32_t count);

int main(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);

	GPIO_InitLED.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitLED.GPIO_OType=GPIO_OType_PP;
	GPIO_InitLED.GPIO_Pin=GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitLED.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitLED.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitLED);

	GPIO_InitLED.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitLED.GPIO_OType=GPIO_OType_PP;
	GPIO_InitLED.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitLED.GPIO_PuPd=GPIO_PuPd_DOWN;
	GPIO_InitLED.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitLED);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource1);

	EXTI_InitSwitch.EXTI_Line=EXTI_Line1;
	EXTI_InitSwitch.EXTI_LineCmd=ENABLE;
	EXTI_InitSwitch.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitSwitch.EXTI_Trigger=EXTI_Trigger_Rising_Falling;
	EXTI_Init(&EXTI_InitSwitch);

	NVIC_InitSwitch.NVIC_IRQChannel=EXTI1_IRQn;
	NVIC_InitSwitch.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitSwitch.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitSwitch.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitSwitch);

	while(1)
	{
		if(i==1)
		{
			GPIO_WriteBit(GPIOD,GPIO_Pin_14 | GPIO_Pin_15, Bit_RESET);
			GPIO_WriteBit(GPIOD,GPIO_Pin_12 | GPIO_Pin_13, Bit_SET);
			msDelay(16800000);
			GPIO_WriteBit(GPIOD,GPIO_Pin_12 | GPIO_Pin_13, Bit_RESET);
			msDelay(16800000);
		}
		else
		{
			GPIO_WriteBit(GPIOD,GPIO_Pin_12 | GPIO_Pin_13, Bit_RESET);
			GPIO_WriteBit(GPIOD,GPIO_Pin_14 | GPIO_Pin_15, Bit_SET);
			msDelay(16800000);
			GPIO_WriteBit(GPIOD,GPIO_Pin_14 | GPIO_Pin_15, Bit_RESET);
			msDelay(16800000);
		}
	}
}

void msDelay(__IO uint32_t count)
{
	while(count--);
}

void EXTI1_IRQHandler(void)
{
	msDelay(168000);
	if(EXTI_GetITStatus(EXTI_Line1)!=RESET)
	{

	if(i==0)
	{
		i=1;
	}
	else
	{
		i=0;
	}
	}
	EXTI_ClearITPendingBit(EXTI_Line1);
}
