////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////    main.c
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"


/* Pololu derived include files. */
#include "digitalAnalog.h"

/* serial interface include file. */
#include "serial.h"

/* i2c Interface include file. */
#include "i2cMultiMaster.h"

/* RTC interface (using I2C) include file */
#include "rtc.h"

/* extended string to integer */
#include "xatoi.h"

/* hd44780 LCD control interface file. */
#include "hd44780.h"

/* Servo PWM Timer include file */
#include "servoPWM.h"

/* Clock include file. */
#include "retrograde.h"


/*--------------Global Variables--------------------*/

TaskHandle_t xTaskWriteRTCRetrograde;	// make a Task handle so we can suspend and resume the Retrograde hands task.

/* Create a Semaphore binary flag for the ADC. To ensure only single access. */
SemaphoreHandle_t xADCSemaphore;

uint8_t * LineBuffer;					// put line buffer on heap (with pvPortMalloc).

#if defined (portRTC_DEFINED)

tm SetTimeDate; // structure for storing the time to be set.

xRTCTempArray xCurrentTempTime; 		// structure to hold the I2C Current time value

xRTCTempArray xMaximumTempTime;
xRTCTempArray xMinimumTempTime;

//  EEPROM structures to hold the extreme temperatures, and the time these were achieved.
xRTCTempArray EEMEM xMaximumEverTempTime;
xRTCTempArray EEMEM xMinimumEverTempTime;

#endif

/*--------------PrivateFunctions-------------------*/

static void get_line (uint8_t *buff, uint8_t len);

static float ReadADCSensors(void);   // Read ADC for Thermal Sensor LM335z

/*--------------Functions---------------------------*/

/* Main program loop */
int main(void) __attribute__((OS_main));

int main(void)
{

    // turn on the serial port for setting or querying the time .
	xSerialPort = xSerialPortInitMinimal( USART0, 38400, portSERIAL_BUFFER_TX, portSERIAL_BUFFER_RX); //  serial port: WantedBaud, TxQueueLength, RxQueueLength (8n1)

    // Memory shortages mean that we have to minimise the number of
    // threads, hence there are no longer multiple threads using a resource.
    // Still, semaphores are useful to stop a thread proceeding, where it should be stopped because it is using a resource.
    if( xADCSemaphore == NULL ) 					// Check to see if the ADC semaphore has not been created.
    {
    	xADCSemaphore = xSemaphoreCreateBinary();	// binary semaphore for ADC - Don't sample temperature when hands are moving (voltage droop).
		if( ( xADCSemaphore ) != NULL )
			xSemaphoreGive( ( xADCSemaphore ) );	// make the ADC available
    }

	// initialise I2C master interface, need to do this once only.
	// If there are two I2C processes, then do it during the system initiation.
	I2C_Master_Initialise((ARDUINO<<I2C_ADR_BITS) | (pdTRUE<<I2C_GEN_BIT));

	avrSerialxPrint_P(&xSerialPort, PSTR("\r\nHello World!\r\n")); // Ok, so we're alive...

    xTaskCreate(
		TaskWriteLCD
		,  (const char *)"WriteLCD"
		,  192
		,  NULL
		,  2
		,  NULL ); // */

   xTaskCreate(
		TaskWriteRTCRetrograde
		,  (const char *)"WriteRTCRetrograde"
		,  120
		,  NULL
		,  1
		,  &xTaskWriteRTCRetrograde ); // */

   xTaskCreate(
		TaskMonitor
		,  (const char *)"SerialMonitor"
		,  256
		,  NULL
		,  3
		,  NULL ); // */

	avrSerialPrintf_P(PSTR("\r\nFree Heap Size: %u\r\n"), xPortGetFreeHeapSize() ); // needs heap_1, heap_2 or heap_4 for this function to succeed.

    vTaskStartScheduler();

	avrSerialPrint_P(PSTR("\r\n\nGoodbye... no space for idle task!\r\n")); // Doh, so we're dead...

#if defined (portHD44780_LCD)
	lcd_Locate (0, 1);
	lcd_Print_P(PSTR("DEAD BEEF!"));
#endif


}

/*-----------------------------------------------------------*/


static void TaskMonitor(void *pvParameters) // Monitor for Serial Interface
{
    (void) pvParameters;

	uint8_t *ptr;
	int32_t p1;

	// create the buffer on the heap (so they can be moved later).
	if(LineBuffer == NULL) // if there is no Line buffer allocated (pointer is NULL), then allocate buffer.
		if( !(LineBuffer = (uint8_t *) pvPortMalloc( sizeof(uint8_t) * LINE_SIZE )))
			xSerialPrint_P(PSTR("pvPortMalloc for *LineBuffer fail..!\r\n"));


    while(1)
    {
    	xSerialPutChar(&xSerialPort, '>');

		ptr = LineBuffer;
		get_line(ptr, (uint8_t)(sizeof(uint8_t)* LINE_SIZE)); //sizeof (Line);

		switch (*ptr++) {

		case 'h' : // help
			xSerialPrint_P( PSTR("rt - reset maximum & minimum temperatures\r\n") );
			xSerialPrint_P( PSTR("t  - show the time\r\n") );
			xSerialPrint_P( PSTR("t  - set the time\r\nt [<year [yy]yy> <month mm> <date dd> <day: Sun=0> <hour hh> <minute mm> <second ss>]\r\n") );
			break;

#ifdef portRTC_DEFINED
		case 't' :	/* t [<year yy> <month mm> <date dd> <day: Sun=0> <hour hh> <minute mm> <second ss>] */

			if (xatoi(&ptr, &p1)) {
				SetTimeDate.tm_year = (uint8_t)p1 -Y2K;
				xatoi(&ptr, &p1); SetTimeDate.tm_mon = (uint8_t)p1 -1;
				xatoi(&ptr, &p1); SetTimeDate.tm_mday = (uint8_t)p1;
				xatoi(&ptr, &p1); SetTimeDate.tm_wday = (uint8_t)p1;
				xatoi(&ptr, &p1); SetTimeDate.tm_hour = (uint8_t)p1;
				xatoi(&ptr, &p1); SetTimeDate.tm_min = (uint8_t)p1;
				if (!xatoi(&ptr, &p1))
					break;
				SetTimeDate.tm_sec = (uint8_t)p1;

				xSerialPrintf_P(PSTR("Set: %4u/%2u/%2u %2u:%02u:%02u\r\n"), SetTimeDate.tm_year +Y2K, SetTimeDate.tm_mon +1, SetTimeDate.tm_mday, SetTimeDate.tm_hour, SetTimeDate.tm_min, SetTimeDate.tm_sec);
				if (setDateTimeDS1307( &SetTimeDate ) == pdTRUE)
					xSerialPrint_P( PSTR("Setting successful\r\n") );

			} else {

				if (getDateTimeDS1307( &xCurrentTempTime.DateTime) == pdTRUE)
					xSerialPrintf_P(PSTR("Current: %4u/%2u/%2u %2u:%02u:%02u\r\n"), xCurrentTempTime.DateTime.tm_year +Y2K, xCurrentTempTime.DateTime.tm_mon +1, xCurrentTempTime.DateTime.tm_mday, xCurrentTempTime.DateTime.tm_hour, xCurrentTempTime.DateTime.tm_min, xCurrentTempTime.DateTime.tm_sec);
			}
			break;
#endif

		case 'r' : // reset
			switch (*ptr++) {
			case 't' : // temperature

				xMaximumTempTime = xCurrentTempTime;
				xMinimumTempTime = xCurrentTempTime;
				// Now we commit the time and temperature to the EEPROM, forever...
				eeprom_update_block(&xMaximumTempTime, &xMaximumEverTempTime, sizeof(xRTCTempArray));
				eeprom_update_block(&xMinimumTempTime, &xMinimumEverTempTime, sizeof(xRTCTempArray));
				break;

			default :
				break;
			}
			break;

		default :
			break;
		}
// 		xSerialPrintf_P(PSTR("\r\nSerial Monitor: Stack HighWater @ %u"), uxTaskGetStackHighWaterMark(NULL));
//		xSerialPrintf_P(PSTR("\r\nFree Heap Size: %u\r\n"), xPortGetMinimumEverFreeHeapSize() ); // needs heap_1, heap_2 or heap_4 for this function to succeed.

    }

}


/*-----------------------------------------------------------*/


static void TaskWriteLCD(void *pvParameters) // Write to LCD
{
    (void) pvParameters;

    TickType_t xLastWakeTime;
	/* The xLastWakeTime variable needs to be initialised with the current tick
	count.  Note that this is the only time we access this variable.  From this
	point on xLastWakeTime is managed automatically by the vTaskDelayUntil()
	API function. */
	xLastWakeTime = xTaskGetTickCount();

	uint8_t temperature_print; // true if temperature can be displayed.

    eeprom_read_block(&xMaximumTempTime, &xMaximumEverTempTime, sizeof(xRTCTempArray));
    eeprom_read_block(&xMinimumTempTime, &xMinimumEverTempTime, sizeof(xRTCTempArray));

    lcd_Init();	// initialise LCD, move cursor to start of top line

    while(1)
    {
    	if(getDateTimeDS1307(&xCurrentTempTime.DateTime))
    	{
			if ( (xCurrentTempTime.Temperature = ReadADCSensors())) // if non 0 then a reading returned.
			{	// trigger a temperature reading

				temperature_print = true;
				xCurrentTempTime.Temperature -= 273.15; // Convert from Kelvin to Celcius

				if( (xCurrentTempTime.Temperature < 65) && (xCurrentTempTime.Temperature > xMaximumTempTime.Temperature)) // check for maximum temp
				// we don't expect the temperature sensor to work above 65C
				{
					xMaximumTempTime = xCurrentTempTime;

					// Now we commit the time and temperature to the EEPROM, forever...
					eeprom_update_block(&xMaximumTempTime, &xMaximumEverTempTime, sizeof(xRTCTempArray));
				}

				if( (xCurrentTempTime.Temperature > (-30)) && (xCurrentTempTime.Temperature < xMinimumTempTime.Temperature)) // and check for minimum temp
				// we don't expect the temperature sensor to work below -30C
				{
					xMinimumTempTime = xCurrentTempTime;

					// Now we commit the time and temperature to the EEPROM, forever...
					eeprom_update_block(&xMinimumTempTime, &xMinimumEverTempTime, sizeof(xRTCTempArray));
				}
			}
			else temperature_print = false;

			lcd_Locate(0, 0);  // go to the first character of the first LCD line
			switch( xCurrentTempTime.DateTime.tm_wday )
			{
				case SUNDAY:
					lcd_Print_P(PSTR("Sunday   "));
					break;
				case MONDAY:
					lcd_Print_P(PSTR("Monday   "));
					break;
				case TUESDAY:
					lcd_Print_P(PSTR("Tuesday  "));
					break;
				case WEDNESDAY:
					lcd_Print_P(PSTR("Wednesday"));
					break;
				case THURSDAY:
					lcd_Print_P(PSTR("Thursday "));
					break;
				case FRIDAY:
					lcd_Print_P(PSTR("Friday   "));
					break;
				case SATURDAY:
					lcd_Print_P(PSTR("Saturday "));
					break;
				default:
					lcd_Print_P(PSTR("NotMyDay "));
					break;
			}

			// display Day Date/Month/Year
			lcd_Locate(0, 10);              // go to the eleventh character of the first LCD line
			lcd_Printf_P( PSTR("%2u/%2u/%4u"), xCurrentTempTime.DateTime.tm_mday, xCurrentTempTime.DateTime.tm_mon +1, xCurrentTempTime.DateTime.tm_year +Y2K );

			// display the current temperature
			lcd_Locate(1, 1);			// LCD cursor to third character of the second LCD line
			if ( temperature_print )	// print the temperature if you got it
				lcd_Printf_P( PSTR("%6.2f"), xCurrentTempTime.Temperature); // print Celcius temperature

			// display the current time
			lcd_Locate(1, 9);             // go to the ninth character of the second LCD line
			lcd_Printf_P(PSTR("%2u:%02u:%02u"),xCurrentTempTime.DateTime.tm_hour, xCurrentTempTime.DateTime.tm_min, xCurrentTempTime.DateTime.tm_sec);

			// display the maximum temperature, time and date
			lcd_Locate(2, 0);          // go to the first character of the third LCD line
			lcd_Printf_P(PSTR("Max%5.1f"),xMaximumTempTime.Temperature);			// print the maximum temperature value

			lcd_Locate(2, 9);          // go to the ninth character of the third LCD line
			lcd_Printf_P(PSTR("%2u:%02u %2u/%2u"),xMaximumTempTime.DateTime.tm_hour, xMaximumTempTime.DateTime.tm_min, xMaximumTempTime.DateTime.tm_mday, xMaximumTempTime.DateTime.tm_mon +1 );

			// display the m temperature, time and date
			lcd_Locate(3, 0);          // go to the first character of the forth LCD line
			lcd_Printf_P(PSTR("Min%5.1f"),xMinimumTempTime.Temperature);			// print the minimum temperature value

			lcd_Locate(3, 9);          // go to the ninth character of the fourth LCD line
			lcd_Printf_P(PSTR("%2u:%02u %2u/%2u"),xMinimumTempTime.DateTime.tm_hour, xMinimumTempTime.DateTime.tm_min, xMinimumTempTime.DateTime.tm_mday, xMinimumTempTime.DateTime.tm_mon +1 );

			if(xCurrentTempTime.DateTime.tm_sec == 0)
			// resume the xTaskWriteRTCRetrograde() task, now that we need to write the analogue hands.
				vTaskResume( xTaskWriteRTCRetrograde );
    	}
//		xSerialPrintf_P(PSTR("LCD: Stack HighWater @ %u\r\n"), uxTaskGetStackHighWaterMark(NULL));
        vTaskDelayUntil( &xLastWakeTime, ( 200 / portTICK_PERIOD_MS ) );
	}
}


static void TaskWriteRTCRetrograde(void *pvParameters) // Write RTC to Retrograde Hands
{
    (void) pvParameters;

    uint16_t servoHours_uS = 1500;
    uint16_t servoMinutes_uS = 1500;
    uint8_t firstPass = pdTRUE;

	if( xSemaphoreTake( xADCSemaphore, portMAX_DELAY ) == pdTRUE )
	{
		// We were able to obtain the semaphore and can now access the shared resource.
		// We don't want anyone using the ADC during servo moves, so take the semaphore.
		// There is too much noise on Vcc to get a clean sample.

		start_PWM_hardware();  // start the PWM TimerX hardware depending on the Timer #define in FreeRTOSConfig.h
		// Servos driving the hands, drags the Vcc down, drastically affecting the ADC0 (temperature) reading.

		// delay 2000mS to ensure hands are stopped before releasing.
		vTaskDelay( 2000 / portTICK_PERIOD_MS );

		xSemaphoreGive( xADCSemaphore ); // now the ADC can be used again.
	}

    while(1)
    {
		if( firstPass == pdTRUE) // Set hour hand servo on power-on once,
		{
			// convert to a range of 700uS to 2300uS over 24 hours.
			servoHours_uS = (uint16_t)(2300 - ((float)xCurrentTempTime.DateTime.tm_min + (float)xCurrentTempTime.DateTime.tm_hour*60 )/1439*(2300-700));
			firstPass = pdFALSE;

		} else {

			switch( xCurrentTempTime.DateTime.tm_min )  // otherwise update the hour hand once every quarter hour.
			{
				case 0:
				case 15:
				case 30:
				case 45:
					// convert to a range of 700uS to 2300uS over 24 hours.
					servoHours_uS = (uint16_t)(2300 - ((float)xCurrentTempTime.DateTime.tm_min + (float)xCurrentTempTime.DateTime.tm_hour*60 )/1439*(2300-700));
					break;
				default:
					break;
			}

		}

		// convert to a range of 700uS to 2300uS over 60 minutes.
		servoMinutes_uS = (uint16_t)(2300 - (float)xCurrentTempTime.DateTime.tm_min/59*(2300-700));

		// See if we can obtain the ADC semaphore.  If the semaphore is not available
		// wait for as long as we can to see if it becomes free.
		if( xSemaphoreTake( xADCSemaphore, portMAX_DELAY ) == pdTRUE )
		{
			// We were able to obtain the semaphore and can now access the shared resource.
			// We don't want anyone using the ADC during servo moves, so take the semaphore.
			// There is too much noise on Vcc to get a clean sample.

			set_PWM_hardware( servoHours_uS, servoMinutes_uS );

			// Servos driving, drags the Vcc down, drastically affecting the ADC0 reading.
			// delay 2000mS to ensure hands are stopped before releasing.
			vTaskDelay( 2000 / portTICK_PERIOD_MS );
			xSemaphoreGive( xADCSemaphore ); // now the ADC can be used again.
		}

    	vTaskSuspend( NULL );	// suspend ourselves, until we're needed again. */
//		xSerialPrintf_P(PSTR("RTC Servo: Stack HighWater @ %u\r\n"), uxTaskGetStackHighWaterMark(NULL));
	}
}


/*-----------------------------------------------------------*/
/* Additional helper functions */
/*-----------------------------------------------------------*/

float ReadADCSensors(void) // Read ADC Sensor for Thermal LM335z
{
	// Variables for the analogue conversion on ADC Sensors

    uint32_t samples = 0;               		// holds the summated samples for decimation
    uint16_t i = (uint16_t) _BV(2 * ADC_SAMPLES); // 4 ^ ADC_SAMPLES

	if( xADCSemaphore != NULL )
	{
		// See if we can obtain the semaphore.  If the semaphore is not available
		// wait 5 ticks to see if it becomes free.

		if( xSemaphoreTake( xADCSemaphore, ( TickType_t ) 5 ) == pdTRUE )
		{
			// We were able to obtain the semaphore and can now access the shared resource.
			// We want to have the ADC for us alone, as it takes some time to sample,
			// so we don't want it getting stolen during the middle of a conversion.

		    setAnalogMode(MODE_10_BIT);	// 10-bit analogue-to-digital conversions

		    // Disable the digital IO circuit on the ADC0 pin, used for the temperature sensor.
			DIDR0 = _BV(ADC5D)|_BV(ADC4D)|_BV(ADC3D)|_BV(ADC2D)|_BV(ADC1D)|_BV(ADC0D); // turn off digital inputs
			DIDR1 = _BV(AIN1D)|_BV(AIN0D);

			do
			{
				startAnalogConversion(0, EXTERNAL_REF);   // start next conversion
				do _delay_loop_1(F_CPU / 5e5);     // wait until conversion read. This is about 6 uS, which should be enough.
				while( analogIsConverting() );

				samples += analogConversionResult();	// sum the results

			} while (--i);

			xSemaphoreGive( xADCSemaphore );

			samples >>= ADC_SAMPLES; 		// Decimate the samples (to get better accuracy), see AVR8003.doc

			/*
			For the LM335Z we want to calculate the resistance R1 required to ensure that we have 500 uA minimum at the maximum
			temperature we intend to measure.
			Assume maximum 60C this is 273K + 60 = 333K or will be measured at 3330mV

			If Vcc is 4.9V (USB) then the R = V/I calculation gives (4.9 - 3.3)/ 0.0005 = 3200 Ohm

			This leads to using a 3200 Ohm resistor, or there about being 3300 Ohm.

			Testing gives us 0.58mA with the resistor actual at 3250 Ohm.

			Analogue testing gives with this set up: 2.952V at 20C actual... or 22C indicated

			Lets see what the Arduino ADC gives us...
			*/

			// The 497 is the Power Supply Voltage in mV / 10. _BV(10 + ADC_SAMPLES) is the number of ADC values.
			// 271.15 is the adjustment from Kelvin (273.15) and the offset relating to the Temp Sensor error correction.
		} else {
			return 0; // no sample taken so return 0.
		}
	}
	return ( (float) samples * 497.0 / (((uint16_t)_BV(10 + ADC_SAMPLES)) -1) );  // and return the current Kelvin temp
}

/*-----------------------------------------------------------*/
/* Monitor                                                   */
/*-----------------------------------------------------------*/

static
void get_line (uint8_t *buff, uint8_t len)
{
	uint8_t c;
	uint8_t i = 0;

	for (;;) {
		while ( ! xSerialGetChar( &xSerialPort, &c ))
			vTaskDelay( 1 );

		if (c == '\r') break;
		if ((c == '\b') && i) {
			--i;
			xSerialPutChar( &xSerialPort, c );
			continue;
		}
		if (c >= ' ' && i < len - 1) {	/* Visible chars */
			buff[i++] = c;
			xSerialPutChar( &xSerialPort, c );
		}
	}
	buff[i] = 0;
	xSerialPrint((uint8_t *)"\r\n");
}



