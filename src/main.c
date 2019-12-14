#include "stm32f4xx.h"

GPIO_InitTypeDef GPIO_InitSwitch;
USART_InitTypeDef USART_InitReceiver;
NVIC_InitTypeDef NVIC_InitUsart;

void msDelay(__IO uint32_t count);

void usart1PB(void);
void usart2PA(void);
void usart2PD(void);
void usart3PB(void);
void usart3PD(void);
void usart6PC(void);

uint16_t ch;
int i=0;

int main(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);

	GPIO_InitSwitch.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitSwitch.GPIO_OType=GPIO_OType_PP;
	GPIO_InitSwitch.GPIO_Pin=GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitSwitch.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitSwitch.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitSwitch);

	usart6PC();

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

void USART6_IRQHandler(void)                       //change
{
	if(USART_GetITStatus(USART6,USART_IT_RXNE)==SET)   //change
	{
		ch=USART_ReceiveData(USART6);                //change
		if(ch=='A')
		{
			i=0;
		}
		else
		{
			i=1;
		}
	}
	USART_ClearITPendingBit(USART6, USART_IT_RXNE);          //change
}

void usart1PB(void)
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);    //change

		GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_USART1);   //change
		GPIO_InitSwitch.GPIO_Mode=GPIO_Mode_AF;
		GPIO_InitSwitch.GPIO_OType=GPIO_OType_PP;
		GPIO_InitSwitch.GPIO_Pin=GPIO_Pin_7;                      //change
		GPIO_InitSwitch.GPIO_PuPd=GPIO_PuPd_DOWN;
		GPIO_InitSwitch.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOB,&GPIO_InitSwitch);                        //change

		USART_InitReceiver.USART_BaudRate=9600;
		USART_InitReceiver.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
		USART_InitReceiver.USART_Mode=USART_Mode_Rx;
		USART_InitReceiver.USART_Parity=USART_Parity_No;
		USART_InitReceiver.USART_StopBits=USART_StopBits_1;
		USART_InitReceiver.USART_WordLength=USART_WordLength_8b;
		USART_Init(USART1,&USART_InitReceiver);                          //change
	 	USART_Cmd(USART1,ENABLE);                                  //change

		USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);                   //change

		NVIC_InitUsart.NVIC_IRQChannel=USART1_IRQn;                    //change
		NVIC_InitUsart.NVIC_IRQChannelCmd=ENABLE;
		NVIC_InitUsart.NVIC_IRQChannelPreemptionPriority=0;
		NVIC_InitUsart.NVIC_IRQChannelSubPriority=0;
		NVIC_Init(&NVIC_InitUsart);
}

void usart2PA(void)
{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);    //change

		GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);   //change
		GPIO_InitSwitch.GPIO_Mode=GPIO_Mode_AF;
		GPIO_InitSwitch.GPIO_OType=GPIO_OType_PP;
		GPIO_InitSwitch.GPIO_Pin=GPIO_Pin_3;                      //change
		GPIO_InitSwitch.GPIO_PuPd=GPIO_PuPd_DOWN;
		GPIO_InitSwitch.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitSwitch);                        //change

		USART_InitReceiver.USART_BaudRate=9600;
		USART_InitReceiver.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
		USART_InitReceiver.USART_Mode=USART_Mode_Rx;
		USART_InitReceiver.USART_Parity=USART_Parity_No;
		USART_InitReceiver.USART_StopBits=USART_StopBits_1;
		USART_InitReceiver.USART_WordLength=USART_WordLength_8b;
		USART_Init(USART2,&USART_InitReceiver);                          //change
	 	USART_Cmd(USART2,ENABLE);                                  //change

		USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);                   //change

		NVIC_InitUsart.NVIC_IRQChannel=USART2_IRQn;                   //change
		NVIC_InitUsart.NVIC_IRQChannelCmd=ENABLE;
		NVIC_InitUsart.NVIC_IRQChannelPreemptionPriority=0;
		NVIC_InitUsart.NVIC_IRQChannelSubPriority=0;
		NVIC_Init(&NVIC_InitUsart);
}

void usart2PD(void)
{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);    //change

		GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_USART2);   //change
		GPIO_InitSwitch.GPIO_Mode=GPIO_Mode_AF;
		GPIO_InitSwitch.GPIO_OType=GPIO_OType_PP;
		GPIO_InitSwitch.GPIO_Pin=GPIO_Pin_6;                      //change
		GPIO_InitSwitch.GPIO_PuPd=GPIO_PuPd_DOWN;
		GPIO_InitSwitch.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOD,&GPIO_InitSwitch);                        //change

		USART_InitReceiver.USART_BaudRate=9600;
		USART_InitReceiver.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
		USART_InitReceiver.USART_Mode=USART_Mode_Rx;
		USART_InitReceiver.USART_Parity=USART_Parity_No;
		USART_InitReceiver.USART_StopBits=USART_StopBits_1;
		USART_InitReceiver.USART_WordLength=USART_WordLength_8b;
		USART_Init(USART2,&USART_InitReceiver);                          //change
	 	USART_Cmd(USART2,ENABLE);                                  //change

		USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);                   //change

		NVIC_InitUsart.NVIC_IRQChannel=USART2_IRQn;                   //change
		NVIC_InitUsart.NVIC_IRQChannelCmd=ENABLE;
		NVIC_InitUsart.NVIC_IRQChannelPreemptionPriority=0;
		NVIC_InitUsart.NVIC_IRQChannelSubPriority=0;
		NVIC_Init(&NVIC_InitUsart);
}

void usart3PB(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);    //change

	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3);   //change
	GPIO_InitSwitch.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitSwitch.GPIO_OType=GPIO_OType_PP;
	GPIO_InitSwitch.GPIO_Pin=GPIO_Pin_11;                      //change
	GPIO_InitSwitch.GPIO_PuPd=GPIO_PuPd_DOWN;
	GPIO_InitSwitch.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitSwitch);                        //change

	USART_InitReceiver.USART_BaudRate=9600;
	USART_InitReceiver.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitReceiver.USART_Mode=USART_Mode_Rx;
	USART_InitReceiver.USART_Parity=USART_Parity_No;
	USART_InitReceiver.USART_StopBits=USART_StopBits_1;
	USART_InitReceiver.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART3,&USART_InitReceiver);                          //change
 	USART_Cmd(USART3,ENABLE);                                  //change

	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);                   //change

	NVIC_InitUsart.NVIC_IRQChannel=USART3_IRQn;                    //change
	NVIC_InitUsart.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitUsart.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitUsart.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitUsart);
}

void usart3PC(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);    //change

	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_USART3);   //change
	GPIO_InitSwitch.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitSwitch.GPIO_OType=GPIO_OType_PP;
	GPIO_InitSwitch.GPIO_Pin=GPIO_Pin_11;                      //change
	GPIO_InitSwitch.GPIO_PuPd=GPIO_PuPd_DOWN;
	GPIO_InitSwitch.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitSwitch);                        //change

	USART_InitReceiver.USART_BaudRate=9600;
	USART_InitReceiver.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitReceiver.USART_Mode=USART_Mode_Rx;
	USART_InitReceiver.USART_Parity=USART_Parity_No;
	USART_InitReceiver.USART_StopBits=USART_StopBits_1;
	USART_InitReceiver.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART3,&USART_InitReceiver);                          //change
 	USART_Cmd(USART3,ENABLE);                                  //change

	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);                   //change

	NVIC_InitUsart.NVIC_IRQChannel=USART3_IRQn;                    //change
	NVIC_InitUsart.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitUsart.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitUsart.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitUsart);
}


void usart3PD(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);    //change

	GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_USART3);   //change
	GPIO_InitSwitch.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitSwitch.GPIO_OType=GPIO_OType_PP;
	GPIO_InitSwitch.GPIO_Pin=GPIO_Pin_9;                      //change
	GPIO_InitSwitch.GPIO_PuPd=GPIO_PuPd_DOWN;
	GPIO_InitSwitch.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitSwitch);                        //change

	USART_InitReceiver.USART_BaudRate=9600;
	USART_InitReceiver.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitReceiver.USART_Mode=USART_Mode_Rx;
	USART_InitReceiver.USART_Parity=USART_Parity_No;
	USART_InitReceiver.USART_StopBits=USART_StopBits_1;
	USART_InitReceiver.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART3,&USART_InitReceiver);                          //change
 	USART_Cmd(USART3,ENABLE);                                  //change

	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);                   //change

	NVIC_InitUsart.NVIC_IRQChannel=USART3_IRQn;                    //change
	NVIC_InitUsart.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitUsart.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitUsart.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitUsart);
}

void usart6PC(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);    //change

	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_USART6);   //change
	GPIO_InitSwitch.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitSwitch.GPIO_OType=GPIO_OType_PP;
	GPIO_InitSwitch.GPIO_Pin=GPIO_Pin_7;                      //change
	GPIO_InitSwitch.GPIO_PuPd=GPIO_PuPd_DOWN;
	GPIO_InitSwitch.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitSwitch);                        //change

	USART_InitReceiver.USART_BaudRate=9600;
	USART_InitReceiver.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitReceiver.USART_Mode=USART_Mode_Rx;
	USART_InitReceiver.USART_Parity=USART_Parity_No;
	USART_InitReceiver.USART_StopBits=USART_StopBits_1;
	USART_InitReceiver.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART6,&USART_InitReceiver);                          //change
 	USART_Cmd(USART6,ENABLE);                                  //change

	USART_ITConfig(USART6,USART_IT_RXNE,ENABLE);                   //change

	NVIC_InitUsart.NVIC_IRQChannel=USART6_IRQn;                    //change
	NVIC_InitUsart.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitUsart.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitUsart.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitUsart);
}
