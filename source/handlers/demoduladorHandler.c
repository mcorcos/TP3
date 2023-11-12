/***************************************************************************//**
  @file     demoduladorHandler.c
  @brief    Handler del demodulador FSK
  @author   G4
******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "timers/PIT.h"
#include "drivers/drv_ADC.h"
#include "handlers/demoduladorHandler.h"
#include "math.h"
#include "fsm/fsmtable.h"


 /*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define NUM_POINTS 1000
#define FREQ0 2200.0
#define FREQ1 1200.0
#define TIMERHALF0 ((((1/FREQ0)/NUM_POINTS)*1000.0)/2)
#define TIMERDEMODCHAR (1/FREQ1)*1000.0

#define ZERO_ERROR 0.2
#define ZERO 1.65
#define BIT_VALUE(x) ((((x) <= (ZERO + ZERO_ERROR)) && ((x) >= (ZERO - ZERO_ERROR))) ? 0 : 1)

#define SHIFT_VALUE(pos, value) ((value)<<(pos))


 /*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
enum{ADC_IDLE, ADC_RECIEVE};

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
static char localBitstream;

static uint8_t bitCounter = 0;

static bool demoduladorReady = false;
static uint8_t stateDemod = ADC_IDLE;

static bool startBitFlag = false;

static uint8_t auxPrevBit;


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH LOCAL SCOPE
 ******************************************************************************/
void getBitValue(void);
void recieveBit(void);


void initDemoduladorHandler(){
/*	timerDemodChar = timerGetId();
	timerHalf0 = timerGetId();
	timerStart(timerDemodChar, TIMER_MS2TICKS(2000), TIM_MODE_PERIODIC, recieveBit);
	timerStart(timerHalf0, TIMER_MS2TICKS(2000), TIM_MODE_SINGLESHOT, getBitValue);*/

}

void getFSKDemodEvent(uint8_t* event){
	if(demoduladorReady){
		*event = DEMOD_FSK_EVENT;
		demoduladorReady = false;
	}
}

char recieveCharacter(void){
	return localBitstream;
}

void recieveADCBitstream(void){
	demoduladorReady = true;
}

void recieveBit(void){
}

void getBitValue(void){
	uint8_t newBit = BIT_VALUE(recieveFromADC());
	if(!startBitFlag){
		if(newBit!=auxPrevBit){
			startBitFlag = true;
			stateDemod = ADC_RECIEVE;
		}
		else{
			stateDemod = ADC_IDLE;
		}
	}
	auxPrevBit = newBit;
	if(startBitFlag){
		if(stateDemod == ADC_RECIEVE){
			++bitCounter;
			if((bitCounter>1)&&(bitCounter<9)){
				localBitstream |= SHIFT_VALUE(bitCounter-1, newBit);
			}
			if(bitCounter == 11){
				bitCounter = 0;
				//timerStop(timerDemodChar);
				stateDemod = ADC_IDLE;
			}
		}
	}
}

