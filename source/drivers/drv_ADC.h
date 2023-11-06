
/******************************************************************************
  @file     drv_ADC.h
  @brief    Driver ADC
  @author   G4
 ******************************************************************************/
#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define ADC0_DP0	0b00000
#define DISABLE		0b11111

typedef uint32_t ADCdata_t;

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

void initADC(void (*callback)(void));

void ADC_enableModule(void);

void ADC_disableModule(void);

double recieveFromADC(void);

#endif /*ADC_H_*/
