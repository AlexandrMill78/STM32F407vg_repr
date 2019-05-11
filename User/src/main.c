#include "main.h"
// !!! to Dickovery kit stm32xx.h
// #define HSE_VALUE    ((uint32_t)8000000) /*!< Value of the External oscillator in Hz */
// not 25MHz! 

uint8_t Mode = 0;
uint16_t Mode_count = 0;
uint8_t Mode_new = 1;				// Flag switch-LED

uint8_t Button_count = 0;
uint8_t Button_status = DISABLE;   // Flag Push-BUTTON

uint16_t DELAY = 0;

uint8_t button_check = 0;
uint8_t button_click = 1;

char str[30];
void SendStrtoPS(char* str_p, uint16_t count);// There war conflict of declaration (without)
uint8_t Laser_status = 0;

//--------------------------void SysTick_Handler(void)-----------------------------------------------

void SysTick_Handler(void)  // interrupt 1 ms, and function call 
{
	if (Mode_count > 0)				// time of LED-lighting
	{
		Mode_count--;
	}
	//----------Button--------------------------
	if (BUTTON_READ() == 1)
	{
		if (Button_count < 5)
		{
			Button_count++;
		} else {
			//if (Button_status == DISABLE)
			//{
				Button_status = ENABLE;
				button_check = 1;
				//GPIO_ToggleBits(GPIOD, GPIO_Pin_14); // Toggle RED-LED
			//}				
		}
	}
	else{                           //(BUTTON_READ() = 0)
		if (Button_count > 0)
			{
			Button_count--;
			} else {
				Button_status = DISABLE;	// normal case, button is output
			}
		}
	//----------Laser_Sensor----------------------
	if (LASER_SENSOR_READ() == 0)// NORMAL Output LASER_SENSOR_READ() is PA4 = "1"
		{
			Laser_status = ENABLE;
		} else {
				Laser_status = DISABLE;
			}
}
//-------------------------------delay_button()------------------------------------------------------
void delay_button(void)
{
	if (Button_status == ENABLE)
	{
		//GPIO_ToggleBits(GPIOD, GPIO_Pin_14);		
		DELAY = 100;
		//USART_SendData(USART2, 0xFF); ////void USART_SendData(USART_TypeDef* USARTx, uint16_t Data);
		SendStrtoPS(str, 5); // count is number of symbols
	} else{
		DELAY = 0;
	}
}
//-------------------------------switch_button()-----------------------------------------------------
void switch_button(void)
{
	if (button_check == 1 && Button_status == DISABLE) 		// CASE! button_check (button is output)
	{
		button_check = 0;
		button_click++;
		
		if ((button_click % 2) > 0)
		{
			DELAY = 0;
		} else
			{
				DELAY = 100;
			}
	}
}
//-------------------------------SendStrtoPS()-------------------------------------------------------
void SendStrtoPS(char* str_p, uint16_t count)
{
	uint16_t i = 0;
	//for (i = 0; str_p[i] != 0; i++)
	for (i = 0; i < count; i++)
	{
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == 0) {}		// wait of Flag to send-Data
		{
			//FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, uint16_t USART_FLAG);  (stm32fxx_usart.h)
			//typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;			
			// Flag is TS (translation complete), write Data in COM-Port
			USART_SendData(USART2, str_p[i]);
		}
	}
}
//-------------------------------- MAIN --------------------------------------------------------------
int main(void)
{
	LEDs_ini();
	SysTick_Config(SystemCoreClock/1000); // SystemCoreClock = n takts per secunde, interrupr 1 ms
	//Mode_count = DELAY;
	
	Button_ini();							// inizialisation ! does't forget !!
	USART2_ini();
	
	Laser_Sensor_ini();
	
	//char str[30];
	sprintf(str, "Hello World");
	//SendStrtoPS(str);
	
	while(1)
	{	
		delay_button();				//      only put-button
		//switch_button();				//      switch-button
		
	
	if (Laser_status == ENABLE)  // Laser_status == ENABLE
	{
		DELAY = 100;
	}
		
		if (Mode == MODE_RED)
		{
			RED_ON();
			if (Mode_count == 0)
			{
				RED_OFF();
				Mode = MODE_BLUE;			
				Mode_count = DELAY;
			}
		}
		else if (Mode == MODE_BLUE)
		{ 
			BLUE_ON();
			if (Mode_count == 0)
			{
				BLUE_OFF();
				Mode = MODE_GREEN;			
				Mode_count = DELAY;
			}
		}
		else if (Mode == MODE_GREEN)
		{
		  GREEN_ON();
			if (Mode_count == 0)
			{
				GREEN_OFF();
				Mode = MODE_YELLOW;			
				Mode_count = DELAY;
			}
		}	
		else if (Mode == MODE_YELLOW)
		{
			YELLOW_ON();
			if (Mode_count == 0)
			{
				YELLOW_OFF();
				Mode = MODE_RED;			
				Mode_count = DELAY;
			}
		}
	}
}
