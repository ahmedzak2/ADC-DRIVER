/*
 * ADC.h
 *
 *  Created on: Mar 31, 2021
 *    Description: Header file for the ADC driver
 *      Author: Ahmed zakria
 */

#ifndef ADC_H_
#define ADC_H_
#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"
#include "ADC_PBcfg.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* ADC configurations for  */

typedef enum  // Select bite
{
	AREF, AVcc_Extrenalcapcitor,reserved,internal_volt
}Refence_select_bite;
/* to adjust the result to left or right*/
typedef enum
{
	Right,Left
}Adlar_Adcleft;
/* channel of ADC */
typedef enum
{
	channel_zero,channel_one,channel_two,channel_three,
	channel_four,channel_five,
	channel_sex,channel_seven
}Analog_channel;

typedef enum
{
	false_edge,	positive_edge
}Auto_trigger;

typedef struct
{
	/* Member contains the voltage channel belongs to */
	Refence_select_bite bite;

	/* Member contains the result of the Channel is  to where*/
	Adlar_Adcleft adjust;
	/* Member contains the trigger ADC to work on positive edge the Channel is  to where*/
	Auto_trigger trigger;
	uint8 scaler;


}ADC_Config_type;
/* Extern ADC structures to be used by to initlize adc */

extern const ADC_Config_type ADC_Config;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Function responsible for init ADC
 */
void ADC_init(ADC_Config_type * config);

uint16 ADC_ReadChannel(Analog_channel channel);

#endif /* ADC_H_ */
