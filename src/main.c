#include "stm32f4xx.h"

GPIO_InitTypeDef GPIO_InitSwitch;
USART_InitTypeDef USART_InitReceiver;
NVIC_InitTypeDef NVIC_InitUsart;

void msDelay(__IO uint32_t count);

uint16_t ch;
int i=0;

int main(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);

	GPIO_InitSwitch.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitSwitch.GPIO_OType=GPIO_OType_PP;
	GPIO_InitSwitch.GPIO_Pin=GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitSwitch.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitSwitch.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitSwitch);

	GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_USART3);
	GPIO_InitSwitch.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitSwitch.GPIO_OType=GPIO_OType_PP;
	GPIO_InitSwitch.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitSwitch.GPIO_PuPd=GPIO_PuPd_DOWN;
	GPIO_InitSwitch.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitSwitch);

	USART_InitReceiver.USART_BaudRate=9600;
	USART_InitReceiver.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitReceiver.USART_Mode=USART_Mode_Rx;
	USART_InitReceiver.USART_Parity=USART_Parity_No;
	USART_InitReceiver.USART_StopBits=USART_StopBits_1;
	USART_InitReceiver.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART3,&USART_InitReceiver);
	USART_Cmd(USART3,ENABLE);

	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);

	NVIC_InitUsart.NVIC_IRQChannel=USART3_IRQn;
	NVIC_InitUsart.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitUsart.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitUsart.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitUsart);

	while(1)
	{
		if(i==0)
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

void USART3_IRQHandler(void)
{
	if(USART_GetITStatus(USART3,USART_IT_RXNE)==SET)
	{
		ch=USART_ReceiveData(USART3);
		if(ch=='A')
		{
			i=0;
		}
		else
		{
			i=1;
		}
	}
	USART_ClearITPendingBit(USART3, USART_IT_RXNE);
}
