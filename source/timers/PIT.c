/***************************************************************************//**
  @file     PIT.c
  @brief    PIT
  @author   grupo4
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "PIT.h"
#include "MK64F12.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define FREQ_2_TICKS(freq) ((50000000U)/(freq))
#define TICKSCHAR 41667
#define TICKS1 41667
#define TICKS0 22727

static PIT_Type* PIT_ptr = PIT;
static SIM_Type* sim_ptr = SIM;

void (*callback0)(void);
void (*callback1)(void);
void (*callback2)(void);
void (*callback3)(void);

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
void initPIT(void){
	// Clock Gating for PIT
	sim_ptr->SCGC6 |= SIM_SCGC6_PIT_MASK;
	// PIT Module enable
	PIT_ptr->MCR &= ~(PIT_MCR_MDIS_MASK | PIT_MCR_FRZ_MASK);
	PIT_ptr->MCR |= (PIT_MCR_MDIS(0) | PIT_MCR_FRZ(1));
}

void configTimersPIT(uint8_t id, uint16_t freq, void(*callback)(void)){
	switch (id) {
		case 0:
			NVIC_EnableIRQ(PIT0_IRQn);
			NVIC_SetPriority(PIT0_IRQn, 0);
			callback0 = callback;
			break;
		case 1:
			NVIC_EnableIRQ(PIT1_IRQn);
			NVIC_SetPriority(PIT1_IRQn, 0);
			callback1 = callback;
			break;
		case 2:
			NVIC_EnableIRQ(PIT2_IRQn);
			NVIC_SetPriority(PIT2_IRQn, 0);
			callback2 = callback;
			break;
		case 3:
			NVIC_EnableIRQ(PIT3_IRQn);
			NVIC_SetPriority(PIT3_IRQn, 0);
			callback3 = callback;
			break;
	}

	PIT_ptr->CHANNEL[id].LDVAL = (PIT_LDVAL_TSV( FREQ_2_TICKS(freq - 1)));

	PIT_ptr->CHANNEL[id].TCTRL &= ~(PIT_TCTRL_CHN_MASK);
	PIT_ptr->CHANNEL[id].TCTRL |=(PIT_TCTRL_CHN(0));

	PIT_ptr->CHANNEL[id].TCTRL &= ~(PIT_TCTRL_TIE_MASK);
	PIT_ptr->CHANNEL[id].TCTRL |=(PIT_TCTRL_TIE(0));

	PIT_ptr->CHANNEL[id].TCTRL &= ~(PIT_TCTRL_TEN_MASK);
	PIT_ptr->CHANNEL[id].TCTRL |=(PIT_TCTRL_TEN(0));
}

void PIT0_IRQHandler(void){
	callback0();
	//NVIC_ClearPendingIRQ(PIT0_IRQn);
	PIT_ptr->CHANNEL[0].TFLG = PIT_TFLG_TIF(1);
}

void PIT1_IRQHandler(void){
	callback1();
	//NVIC_ClearPendingIRQ(PIT1_IRQn);
	PIT_ptr->CHANNEL[1].TFLG = PIT_TFLG_TIF(1);
}

void PIT2_IRQHandler(void){
	callback2();
	//NVIC_ClearPendingIRQ(PIT2_IRQn);
	PIT_ptr->CHANNEL[2].TFLG = PIT_TFLG_TIF(1);
}

void PIT3_IRQHandler(void){
	callback3();
	//NVIC_ClearPendingIRQ(PIT3_IRQn);
	PIT_ptr->CHANNEL[3].TFLG = PIT_TFLG_TIF(1);
}

void startTimerPIT(uint8_t timer_id){
	PIT_ptr->CHANNEL[timer_id].TCTRL &= ~(PIT_TCTRL_TIE_MASK);
	PIT_ptr->CHANNEL[timer_id].TCTRL |=(PIT_TCTRL_TIE(1));

	PIT_ptr->CHANNEL[timer_id].TCTRL &= ~(PIT_TCTRL_TEN_MASK);
	PIT_ptr->CHANNEL[timer_id].TCTRL |=(PIT_TCTRL_TEN(1));
}

void stopTimerPIT(uint8_t timer_id){
	PIT_ptr->CHANNEL[timer_id].TCTRL &= ~(PIT_TCTRL_TIE_MASK);
	PIT_ptr->CHANNEL[timer_id].TCTRL |=(PIT_TCTRL_TIE(0));

	PIT_ptr->CHANNEL[timer_id].TCTRL &= ~(PIT_TCTRL_TEN_MASK);
	PIT_ptr->CHANNEL[timer_id].TCTRL |=(PIT_TCTRL_TEN(0));
}

