/*
 * ADC.c
 *
 *  Created on: Mar 31, 2021
 *    Description: Source file for the ADC driver
 *      Author: Ahmed zakria
 *      SET_BIT(ADMUX,REFS0);
 *       */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
#include"ADC.h"

void ADC_init(ADC_Config_type * config)
{
	/* TO MAKE CHAANEL ZERO aS INTTIAL*/
	ADMUX = 0;
	if(config->bite == AREF ) // to select volt is internal VREF if off
	{
		CLEAR_BIT(ADMUX,REFS0);
		CLEAR_BIT(ADMUX,REFS1);
	}
	if( config->bite == AVcc_Extrenalcapcitor ) // to select volt is AVCC
	{
		SET_BIT(ADMUX,REFS0);
		CLEAR_BIT(ADMUX,REFS1);
	}
	if( config->bite == reserved )
	{
		SET_BIT(ADMUX,REFS1);
		CLEAR_BIT(ADMUX,REFS0);
	}
	if( config->bite == internal_volt )// to select volt is 2.5 Volt with external reference
	{
		SET_BIT(ADMUX,REFS1);
		SET_BIT(ADMUX,REFS0);
	}


	if(config->adjust == Right ) // to select adjust the result to right in ADC register
	{
		CLEAR_BIT(ADMUX,ADLAR);
	}
	else if(config->adjust == Left) // to select adjust the result to left  in ADC register
	{
		SET_BIT(ADMUX,ADLAR);
	}
	if(config->trigger == positive_edge) // ADC will start conversion with positive edge
	{
		SET_BIT(ADCSRA,ADATE);
	}
	else if (config->trigger == false_edge) // ADC will start conversion with false edge
	{
		CLEAR_BIT(ADCSRA,ADATE);
	}
	if (config->scaler == 2)
	{
		SET_BIT(ADCSRA,ADEN);
		SET_BIT(ADCSRA,ADPS0);
		CLEAR_BIT(ADCSRA,ADPS1);
		CLEAR_BIT(ADCSRA,ADPS2);

	}
	else if (config->scaler == 4)
	{
		SET_BIT(ADCSRA,ADEN);
		SET_BIT(ADCSRA,ADPS1);
		CLEAR_BIT(ADCSRA,ADPS0);
		CLEAR_BIT(ADCSRA,ADPS2);
	}
	else if (config->scaler == 8)
	{
		SET_BIT(ADCSRA,ADEN);
		SET_BIT(ADCSRA,ADPS0);
		SET_BIT(ADCSRA,ADPS1);
		CLEAR_BIT(ADCSRA,ADPS2);
	}
	else if (config->scaler == 16)
	{
		SET_BIT(ADCSRA,ADEN);
		SET_BIT(ADCSRA,ADPS2);
		CLEAR_BIT(ADCSRA,ADPS0);
		CLEAR_BIT(ADCSRA,ADPS1);
	}
	else if (config->scaler == 32)
	{
		SET_BIT(ADCSRA,ADEN);
		SET_BIT(ADCSRA,ADPS2);
		SET_BIT(ADCSRA,ADPS0);
		CLEAR_BIT(ADCSRA,ADPS1);
	}
	else if (config->scaler == 64)
	{
		SET_BIT(ADCSRA,ADEN);
		SET_BIT(ADCSRA,ADPS2);
		SET_BIT(ADCSRA,ADPS1);
		CLEAR_BIT(ADCSRA,ADPS0);
	}
	else if (config->scaler == 128)
	{
		SET_BIT(ADCSRA,ADEN);
		SET_BIT(ADCSRA,ADPS2);
		SET_BIT(ADCSRA,ADPS1);
		SET_BIT(ADCSRA,ADPS0);
	}


}
uint16 ADC_ReadChannel(Analog_channel channel)
{
	ADMUX &= 0xE0;
	if (channel == channel_zero)
	{
		CLEAR_BIT(ADMUX,MUX0);
		CLEAR_BIT(ADMUX,MUX1);
		CLEAR_BIT(ADMUX,MUX2);
		CLEAR_BIT(ADMUX,MUX3);
		CLEAR_BIT(ADMUX,MUX4);
	}
	else if (channel == channel_one)
	{
		SET_BIT(ADMUX,MUX0);
		CLEAR_BIT(ADMUX,MUX1);
		CLEAR_BIT(ADMUX,MUX2);
		CLEAR_BIT(ADMUX,MUX3);
		CLEAR_BIT(ADMUX,MUX4);
	}
	else if (channel == channel_two)
	{
		CLEAR_BIT(ADMUX,MUX0);
		SET_BIT(ADMUX,MUX1);
		CLEAR_BIT(ADMUX,MUX2);
		CLEAR_BIT(ADMUX,MUX3);
		CLEAR_BIT(ADMUX,MUX4);
	}
	else if (channel == channel_three)
	{
		SET_BIT(ADMUX,MUX0);
		SET_BIT(ADMUX,MUX1);
		CLEAR_BIT(ADMUX,MUX2);
		CLEAR_BIT(ADMUX,MUX3);
		CLEAR_BIT(ADMUX,MUX4);
	}
	else if (channel == channel_four)
	{
		CLEAR_BIT(ADMUX,MUX0);
		CLEAR_BIT(ADMUX,MUX1);
		SET_BIT(ADMUX,MUX2);
		CLEAR_BIT(ADMUX,MUX3);
		CLEAR_BIT(ADMUX,MUX4);
	}
	else if (channel == channel_five)
	{
		SET_BIT(ADMUX,MUX0);
		CLEAR_BIT(ADMUX,MUX1);
		SET_BIT(ADMUX,MUX2);
		CLEAR_BIT(ADMUX,MUX3);
		CLEAR_BIT(ADMUX,MUX4);
	}
	else if (channel == channel_sex)
	{
		CLEAR_BIT(ADMUX,MUX0);
		SET_BIT(ADMUX,MUX1);
		SET_BIT(ADMUX,MUX2);
		CLEAR_BIT(ADMUX,MUX3);
		CLEAR_BIT(ADMUX,MUX4);
	}
	else if (channel == channel_seven)
	{
		SET_BIT(ADMUX,MUX0);
		SET_BIT(ADMUX,MUX1);
		SET_BIT(ADMUX,MUX2);
		CLEAR_BIT(ADMUX,MUX3);
		CLEAR_BIT(ADMUX,MUX4);
	}
	SET_BIT(ADCSRA,ADSC); // Enable ADC  to start conversion
	while(!(ADCSRA&(1<<ADIF)))
	{
	}
	SET_BIT(ADCSRA,ADIF);
	return ADC;
}

