////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////    main.c
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <util/delay.h>
#include <avr/io.h>

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "uIP/sys/ttimer.h"
#include "uIP/sys/stimer.h"

/* serial interface include file. */
#include "serial.h"

#include "spi.h"

#include "xatoi.h"

#include "lib_SIM900.h"

/*-----------------------------------------------------------*/

static void TaskCharEcho( void *pvParameters);		//* The task that echos characters between serial ports. */

/* Optionally, create a reference to the handle for the serial port, USART0. */
extern xComPortHandle xSerialPort;
/* Optionally, create a reference to the handle for the other serial port, USART1. */
extern xComPortHandle xSerial1Port;

/*-----------------------------------------------------------*/

/* Main program loop */
int16_t main(void) __attribute__((OS_main));

int16_t main(void)
{

    // turn on the serial port for debugging or for other USART reasons.
	xSerialPort = xSerialPortInitMinimal( USART0, 115200, portSERIAL_BUFFER_TX, portSERIAL_BUFFER_RX); //  serial port: USART, WantedBaud, TxQueueLength, RxQueueLength (8n1)

	avrSerialxPrint_P(&xSerialPort, PSTR("\r\n\nHello World!\r\n")); // Ok, so we're alive...

#ifdef portW5200
	spiBegin(SDCard); // make sure the SDCard SS line is high, to disable its MISO, and prevent it from disturbing the SPI bus.
#endif

/*    xTaskCreate(
    	vuIP_Task
		,  (const char *)"uIP Task" // IP task including httpd
		,  1024
		,  NULL
		,  3
		,  NULL); // */

    xTaskCreate(
    	TaskCharEcho
		,  (const char *)"Char Echo Task" // Echo characters
		,  3072
		,  NULL
		,  3
		,  NULL); // */

	avrSerialxPrintf_P(&xSerialPort, PSTR("\r\nFree Heap Size: %u\r\n"), xPortGetFreeHeapSize() ); // needs heap_1, heap_2 or heap_4 for this function to succeed.

	vTaskStartScheduler();

	avrSerialxPrint_P(&xSerialPort, PSTR("\r\nGoodbye... no space for idle task!\r\n")); // Doh, so we're dead...
}

/*-----------------------------------------------------------*/
/* Standard Tasks                                            */
/*-----------------------------------------------------------*/

static void TaskCharEcho(void *pvParameters) // Echo characters from one USART port to the other for SIM900 testing
{
    (void) pvParameters;

//  portTickType xLastWakeTime;
	/* The xLastWakeTime variable needs to be initialised with the current tick
	count.  Note that this is the only time we access this variable.  From this
	point on xLastWakeTime is managed automatically by the vTaskDelayUntil()
	API function. */
//	xLastWakeTime = xTaskGetTickCount();

    // turn on the other serial port for communicating with the Arduino GSM Shield SIM900.
//	xSerial1Port = xSerialPortInitMinimal( USART1, 115200, 64, 64); //  serial port: USART, WantedBaud, TxQueueLength, RxQueueLength (8n1)

    uint8_t character;
	seconds_timer secs_timer;

	SIM900StateHandle libelium; // set up a SIM900 state structure

	SIM900PowerOn( &libelium, USART1, SIM900_BUFFER_CMD, SIM900_BUFFER_PACKET); // turn on the SIM900, and allocate buffers, etc

	SIM900CheckNetwork(&libelium, 30); // check for 30 seconds

	SIM900ShowAPN(&libelium);

	if( SIM900WhoAmI(&libelium) )
	{
		xSerialxPrintf_P(&xSerialPort, PSTR("Who Am I: %s\r\n"), libelium.buffer_command);
	}

	if( SIM900FirmwareVersion(&libelium) )
	{
		xSerialxPrintf_P(&xSerialPort, PSTR("Firmware: %s\r\n"), libelium.buffer_command);
	}

	if( SIM900GetCurrentOperator(&libelium) )
	{
		xSerialxPrintf_P(&xSerialPort, PSTR("Operator: %s\r\n"), libelium.buffer_command);
	}


	xSerialxPrintf_P(&xSerialPort, PSTR("IP State Actual: %u\r\n\nInitialise GPRS Config:\r\n"), SIM900CheckIPstatus(&libelium));

/*
	SIM900ConfigureGPRS_TCP_UDP( &libelium, SIM900_SINGLE_CONNECTION, SIM900_TRANSPARENT, IP_PROCESSING);

	if( SIM900GetIPfromDNS( &libelium, "google.com") )
	{
		xSerialxPrintf_P(&xSerialPort, PSTR("Google IP: %s\r\n"), libelium.buffer_command);
	}

	xSerialxPrintf_P(&xSerialPort, PSTR("IP State Actual: %u\r\nNow connect to Google.\r\n"), SIM900CheckIPstatus(&libelium));

	if( SIM900CreateSocket(&libelium, TCP_CLIENT, 0,  (const uint8_t *)libelium.buffer_command, (const uint8_t *)"80") )
	{
		xSerialxPrintf_P(&xSerialPort, PSTR("Connected to Google IP address\r\n"));
	}
*/

	seconds_timer call_secs_timer;
	uint8_t hungup = 0;
	if( SIM900MakeCall(&libelium, "04xxxxxxxx") )
	{
		xSerialxPrint_P(&xSerialPort, PSTR("Called: 04xxxxxxxx\r\n"));
	    stimer_set( &call_secs_timer, 120 ); // hold the call for 120 seconds
	}

    stimer_set( &secs_timer, 4 ); // flush every 4 seconds
    while(1)
    {
    	if( xSerialGetChar( &xSerial1Port, &character ) )
		{
			stimer_reset( &secs_timer );
			xSerialPutChar( &xSerialPort, character);
		}

    	if( xSerialGetChar( &xSerialPort, &character ) )
		{
			stimer_reset( &secs_timer );
    		xSerialPutChar( &xSerial1Port, character);
//    		xSerialPutChar( &xSerialPort, character); // echo characters typed.
		}

		if(stimer_expired(&secs_timer))
		{
			xSerialRxFlush( &xSerialPort ); // always flush Rx regularly
			xSerialRxFlush( &xSerial1Port ); // always flush Rx regularly
			stimer_reset( &secs_timer ); // reset the timer once per flush cycle.
		}

		if(stimer_expired(&call_secs_timer) && hungup != 1)
		{
			if( SIM900HangUp(&libelium) )
			{
				xSerialxPrint_P(&xSerialPort, PSTR("Hung Up: 0433220688\r\n"));
				hungup = 1;
			}
		}
    }
}

/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( TaskHandle_t xTask,
                                    signed char *pcTaskName )
{
	DDRB  |= _BV(DDB7);
	PORTB |= _BV(PORTB7);       // main (red PB7) LED on. Goldilocks LED on and die.
	while(1);
}

/*-----------------------------------------------------------*/
