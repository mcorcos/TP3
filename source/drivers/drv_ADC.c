
/***************************************************************************//**
  @file     drv_ADC.c
  @brief    ADC driver
  @author   G4
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "drv_ADC.h"
#include "MK64F12.h"

static ADC_Type* ADC0_ptr = ADC0;
static SIM_Type* sim_ptr = SIM;

static ADCdata_t dataADC;

static double value;

void (*ADCcallback)(void);

/*******************************************************************************
* CONSTANT AND MACRO DEFINITIONS USING #DEFINE
******************************************************************************/
#define DEFAULT_CH 0
#define MAP_CONST 1024.0
/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void initADC(void (*callback)(void))
{
	ADCcallback = callback;

	// CLOCK GATING
	sim_ptr->SCGC6 &= ~SIM_SCGC6_ADC0_MASK;
	sim_ptr->SCGC6 |= SIM_SCGC6_ADC0(1);

	// Enable Interrupt on ADC0
	NVIC_EnableIRQ(ADC0_IRQn);

	// Modo 16-bits
	ADC0_ptr->CFG1 &= ~( ADC_CFG1_ADLPC_MASK |
						 ADC_CFG1_ADIV_MASK |
						 ADC_CFG1_ADLSMP_MASK |
						 ADC_CFG1_MODE_MASK |
						 ADC_CFG1_ADICLK_MASK );
	ADC0_ptr->CFG1 |= ( ADC_CFG1_ADLPC(1) |
						ADC_CFG1_ADIV(1) |
						ADC_CFG1_ADLSMP(0) |
						ADC_CFG1_MODE(0x3) |
						ADC_CFG1_ADICLK(1) );

	ADC0_ptr->CFG2 &= ~(ADC_CFG2_MUXSEL_MASK |
					    ADC_CFG2_ADACKEN_MASK |
					    ADC_CFG2_ADHSC_MASK |
					    ADC_CFG2_ADLSTS_MASK);
	ADC0_ptr->CFG2 |=  (ADC_CFG2_MUXSEL(0) |
						ADC_CFG2_ADACKEN(0) |
						ADC_CFG2_ADHSC(0) |
						ADC_CFG2_ADLSTS(0));

	ADC0_ptr->SC2 &= ~( ADC_SC2_ADTRG_MASK |
					   ADC_SC2_ACFE_MASK |
					   ADC_SC2_DMAEN_MASK |
					   ADC_SC2_REFSEL_MASK);
	ADC0_ptr->SC2 |= ( ADC_SC2_ADTRG(0) |
					   ADC_SC2_ACFE(0) |
					   ADC_SC2_DMAEN(0) |
					   ADC_SC2_REFSEL(0));

	ADC0_ptr->SC3 &= ~ADC_SC3_CAL_MASK;
	ADC0_ptr->SC3 |= ADC_SC3_CAL(1);

	while((ADC0_ptr->SC3) & (ADC_SC3_CAL_MASK))
	{
		//mientras calibra el ADC
	}

	ADC0_ptr->SC3 &= ~( ADC_SC3_ADCO_MASK |
						ADC_SC3_AVGE_MASK |
						ADC_SC3_AVGS_MASK);
	ADC0_ptr->SC3 |= ( ADC_SC3_ADCO(1) |
					   ADC_SC3_AVGE(1) |
					   ADC_SC3_AVGS(0));

	ADC0_ptr->SC1[0] &= ~( ADC_SC1_AIEN_MASK |
					       ADC_SC1_DIFF_MASK |
						   ADC_SC1_ADCH_MASK);
	ADC0_ptr->SC1[0] |= ( ADC_SC1_AIEN(1) |
						  ADC_SC1_DIFF(0) |
						  ADC_SC1_ADCH(DEFAULT_CH));
}

void ADC0_IRQHandler(void){
	dataADC = ADC0_ptr->R[0];
	value = dataADC/MAP_CONST;
	ADCcallback();
}

void ADC_enableModule(void){
	ADC0_ptr->SC1[0] &= ~ADC_SC1_ADCH_MASK;
	ADC0_ptr->SC1[0] |= ADC_SC1_ADCH(DEFAULT_CH);
}

void ADC_disableModule(void){
	ADC0_ptr->SC1[0] &= ~ADC_SC1_ADCH_MASK;
	ADC0_ptr->SC1[0] |= ADC_SC1_ADCH(DISABLE);
}

double recieveFromADC(void){
	return value;
}

