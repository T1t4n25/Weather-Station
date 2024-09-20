/*
 * WeatherStation.c
 *
 * Created: 19/09/2024 10:05:36 ص
 * Author : Meteor
 */ 
#define F_CPU 16000000UL

#include <stdio.h>
#include <util/delay.h>
// MCAL
#include "../MCAL/DIO_interface.h"
#include "../MCAL/PWM0_interface.h"

// HAL
#include "../HAL/ADC_interface.h"
#include "../HAL/LCD_interface.h"
#include "../HAL/LM35_interface.h"

#define DC_Driver_In1_Port			PORTD
#define DC_Driver_In1_Pin			DIO_PIN0

#define DC_Driver_In2_Port			PORTD
#define DC_Driver_In2_Pin			DIO_PIN1

#define DC_Driver_En_Port			PORTB
#define DC_Driver_En_Pin			DIO_PIN3


int main(void)
{
	// Initialization
	ADC_voidInit(ADC_REFERENCE_INTRNAL);
	LCD_voidInit();
	PWM0_voidInit ();
	LM35_voidInit();
	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN3, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN0, DIO_PIN_OUTPUT);
	u8 temprature;
	//u8 fanSpeed;
	u8 lineOneInfo[17] = "Temperature: ";
	u8 lineTwoInfo[17] = "Fan Speed : ";
	
    /* Replace with your application code */
    while (1) 
    {
		LM35_voidGetTemperature(&temprature);
		snprintf((char *)lineOneInfo, 17,"Temperature: %luC", (u32)temprature);
		LCD_voidClear();
		LCD_voidGoToSpecificPosition(0, 0);
		LCD_voidDisplayString(lineOneInfo);
		LCD_voidGoToSpecificPosition(1, 0);
		LCD_voidDisplayString(lineTwoInfo);
		if (temprature < 20)			{
			PWM0_voidStop();
			DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN0, DIO_PIN_INPUT);
			snprintf((char *)lineTwoInfo, 17,"Fan OFF %c", 8);
		}
		else if (temprature >= 20 && temprature <= 25){
			DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN0, DIO_PIN_OUTPUT);
			PWM0_voidGeneratePWM(50);
			snprintf((char *)lineTwoInfo, 17,"Fan Speed : %lu%%", (u32)50);
		}
		else if (temprature > 25 && temprature <= 30){
			DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN0, DIO_PIN_OUTPUT);
			PWM0_voidGeneratePWM(70);
			snprintf((char *)lineTwoInfo, 17,"Fan Speed : %lu%%", (u32)70);
		}
		else if (temprature > 30 && temprature <= 35){
			DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN0, DIO_PIN_OUTPUT);
			PWM0_voidGeneratePWM(85);
			snprintf((char *)lineTwoInfo, 17,"Fan Speed : %lu%%", (u32)85);
		}
		else if (temprature > 35 && temprature <= 40){
			DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN0, DIO_PIN_OUTPUT);
			PWM0_voidGeneratePWM(100);
			snprintf((char *)lineTwoInfo, 17,"Fan Speed : %lu%%", (u32)100);
		}
		else{
			DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN0, DIO_PIN_OUTPUT);
			PWM0_voidGeneratePWM(100);
			snprintf((char *)lineTwoInfo, 17,"Fan Speed : %lu%%", (u32)100);
		}
		_delay_ms(250);
    }
}

