#include <Utils/timer_software_init.h>
#include <Utils/timer_software.h>
#include "LPC177x_8x.h"
#include "system_LPC177x_8x.h"
#include <string.h>
#include "parser.h"
#include <stdint.h>
#include <stdio.h>
#include <retarget.h>

#include <DRV\drv_sdram.h>
#include <DRV\drv_lcd.h>
#include <DRV\drv_uart.h>
#include <DRV\drv_touchscreen.h>
#include <DRV\drv_led.h>
#include <utils\timer_software.h>
#include <utils\timer_software_init.h>

uint8_t* at_command_simple="AT\r\n";
timer_software_handler_t handler_main;
timer_software_handler_t handler_timeout;

const char* at_command_csq = "AT+CSQ\r\n";
AT_COMMAND_DATA data;
timer_software_handler_t my_timer_handler;

void TouchScreenCallBack(TouchResult* touchData)
{
	printf("touched X=%3d Y=%3d\n", touchData->X, touchData->Y);		
	
}

void timer_callback_1(timer_software_handler_t h)
{
}

void BoardInit()
{
	//timer_software_handler_t handler;
	
	TIMER_SOFTWARE_init_system();
	
	
	DRV_SDRAM_Init();
	
	initRetargetDebugSystem();
	DRV_LCD_Init();
	DRV_LCD_ClrScr();
	DRV_LCD_PowerOn();	
	
	DRV_TOUCHSCREEN_Init();
	DRV_TOUCHSCREEN_SetTouchCallback(TouchScreenCallBack);
	DRV_LED_Init();
	printf ("Hello\n");	
	
	/*handler = TIMER_SOFTWARE_request_timer();
	TIMER_SOFTWARE_configure_timer(handler, MODE_1, 100, 1);
	TIMER_SOFTWARE_set_callback(handler, timer_callback_1);
	TIMER_SOFTWARE_start_timer(handler);*/
}

void MyTimerCallback(timer_software_handler_t handler)
{
	DRV_LED_Toggle(LED_1);
	DRV_LED_Toggle(LED_2);
	DRV_LED_Toggle(LED_3);
	DRV_LED_Toggle(LED_4);
}

void SendCommand(const char *command)
{
	DRV_UART_FlushRX(UART_3);
	DRV_UART_FlushTX(UART_3);
	DRV_UART_Write(UART_3, (uint8_t*)command, strlen(command));
}

uint8_t CommandResponseValid()
{
	return 1;
}

void GetCommandResponse()
{
	uint8_t ch;
	BOOLEAN ready = FALSE;
	TIMER_SOFTWARE_reset_timer(handler_timeout);
	TIMER_SOFTWARE_start_timer(handler_timeout);
	while ((!TIMER_SOFTWARE_interrupt_pending(handler_timeout)) && (ready == FALSE))
	{
		while (DRV_UART_BytesAvailable(UART_3) > 0)
		{
			/*printf ("Hello again\n");
			TIMER_SOFTWARE_Wait(100);*/
			DRV_UART_ReadByte(UART_3, &ch);
			if (at_command_parse(ch) != STATE_MACHINE_NOT_READY)
			{
				ready = TRUE;
			}
		}
	}
}

void ExecuteCommand(const char *command)
{
	SendCommand(command);
	GetCommandResponse();
} 

int main(void)
{
	
	//uint32_t rssi_value_asu;
	//uint32_t rssi_value_dbmw;
	uint8_t i;
	uint8_t j;
	//DRV_LED_Init();
	//TIMER_SOFTWARE_init_system();
	BoardInit();
	DRV_UART_Configure(UART_3, UART_CHARACTER_LENGTH_8, 115200, UART_PARITY_NO_PARITY, 1, TRUE, 3);
	DRV_UART_Configure(UART_2, UART_CHARACTER_LENGTH_8, 115200, UART_PARITY_NO_PARITY, 1, TRUE, 3);
	DRV_UART_Configure(UART_0, UART_CHARACTER_LENGTH_8, 115200, UART_PARITY_NO_PARITY, 1, TRUE, 3);

	for(i = 0; i < 5; i++)
	{
		DRV_UART_Write(UART_3, at_command_simple, strlen((char*)at_command_simple));
	}
	TIMER_SOFTWARE_Wait(1000);
	
	handler_timeout = TIMER_SOFTWARE_request_timer();	
	if(handler_timeout < 0)
	{
		// the system could not offer a software timer
	}
	
	TIMER_SOFTWARE_configure_timer(handler_timeout, MODE_1, 20000, true);
	
	
	handler_main = TIMER_SOFTWARE_request_timer();	
	if(handler_main < 0)
	{
		// the system could not offer a software timer
	}
	
	TIMER_SOFTWARE_configure_timer(handler_main, MODE_1, 5000, true);
	TIMER_SOFTWARE_start_timer(handler_main);
	
	while(1)
	{
		// user code
		if (TIMER_SOFTWARE_interrupt_pending(handler_main)) 
		{
			
			 ExecuteCommand(at_command_csq);
				//printf("command exec\n");
					//TIMER_SOFTWARE_Wait(100);
			 //printf("command executed\n");
			 //TIMER_SOFTWARE_Wait(100);
			 if (CommandResponseValid())
			 {

				 for (i = 0; i < data.line_count; i++)
				 {  

								printf("%s\n", data.characters[i]);
								TIMER_SOFTWARE_Wait(100);

				 }

			 }
			 TIMER_SOFTWARE_clear_interrupt(handler_main);
		 } 
		
	}

	return 0;
}
