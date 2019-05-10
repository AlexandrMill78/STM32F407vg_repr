#include "mcu_ini.h"

//-----------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------
void LEDs_ini(void)
{
	GPIO_InitTypeDef GPIO_init_LED;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); // initialisation timing (RCC) for PortD (stm32f4xx_rcc.h)
	
	GPIO_init_LED.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; // initialisation LED's
	GPIO_init_LED.GPIO_Mode = GPIO_Mode_OUT; // Output push-pull
	GPIO_init_LED.GPIO_Speed = GPIO_Low_Speed;
	GPIO_init_LED.GPIO_OType = GPIO_OType_PP; // Output push-pull (Ground to Pin)
	GPIO_init_LED.GPIO_PuPd = GPIO_PuPd_NOPULL; // (if.. pin is input)
		
	GPIO_Init(GPIOD, &GPIO_init_LED); // ??? &
}
//-------------------------------------------------------------------------------------------------------------------
void Button_ini (void)
{
	GPIO_InitTypeDef GPIO_init_Button;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); // initialisation timing (RCC) for PortA !! (stm32f4xx_rcc.h)
	
	GPIO_init_Button.GPIO_Pin = GPIO_Pin_0; // initialisation Pin A0 (Button)
	GPIO_init_Button.GPIO_Mode = GPIO_Mode_IN; //                                      !   Input push-pull
	GPIO_init_Button.GPIO_Speed = GPIO_Low_Speed;
	GPIO_init_Button.GPIO_OType = GPIO_OType_PP; // Output push-pull (Ground to Pin)
	GPIO_init_Button.GPIO_PuPd = GPIO_PuPd_NOPULL; // (if.. pin is input)
		
	GPIO_Init(GPIOA, &GPIO_init_Button); // ??? PortA !!
}
//-------------------------------------------------------------------------------------------------------------------
void USART2_ini (void)
{
	GPIO_InitTypeDef GPIO_Init_USART;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); // initialisation timing (RCC) for PortA !! (stm32f4xx_rcc.h)
	
	GPIO_Init_USART.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; // initialisation Pin A0 (Button)
	GPIO_Init_USART.GPIO_Mode = GPIO_Mode_AF; //       !! AF - alternative function
	GPIO_Init_USART.GPIO_Speed = GPIO_Speed_50MHz; // GPIO_Fast_Speed
	GPIO_Init_USART.GPIO_OType = GPIO_OType_PP; // Output push-pull (Ground to Pin)
	GPIO_Init_USART.GPIO_PuPd = GPIO_PuPd_NOPULL; // (uasualy is pull-up)      GPIO_PuPd_UP
		
	GPIO_Init(GPIOA, &GPIO_Init_USART); 
	
	//void GPIO_PinAFConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_PinSource, uint8_t GPIO_AF);
	
	// --------------description to AF - alternative function of Pin ---------------------- 
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
	
	// clocking USART2
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	//RCC_APB1Periph_USART2(); ... rcc.h
	
	USART_InitTypeDef USART_InitUser; // ...USART_InitTypeDef*  	
	// fun inizialisation USART (usart.h):
	//!! field's of structure:
	USART_InitUser.USART_BaudRate = 9600; // bit/s
	USART_InitUser.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // apparat control: ..RTS/CTS control
	USART_InitUser.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitUser.USART_Parity = USART_Parity_No; 
	USART_InitUser.USART_StopBits = USART_StopBits_1;
	USART_InitUser.USART_WordLength = USART_WordLength_8b;
	
	//void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct);
	USART_Init (USART2, &USART_InitUser);
	
	//set USART: void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
	USART_Cmd(USART2, ENABLE);
}



 

