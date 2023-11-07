/***************************************************************************//**
  @file     moduladorHandler.c
  @brief    Handler del modulador FSK
  @author   G4
******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "timers/PIT.h"
#include "drivers/drv_DAC.h"
#include "handlers/moduladorHandler.h"
#include "math.h"
#include "fsm/fsmtable.h"


 /*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define NUM_POINTS 1000
#define TOTAL_NUM_POINTS_0 1833
#define FREQ0 2200
#define FREQ1 1200

#define CHECK_BIT(char_value, bit_index) (((char_value) & (1 << (bit_index))) ? 1 : 0)
#define CHECK_POINTS_1(entry, lim) ((entry) == NUM_POINTS)&&((lim) == NUM_POINTS)

#define COND_ENTRY(entry2, entryAux2) ((entry2) == NUM_POINTS) || (((entry2) == (TOTAL_NUM_POINTS_0 - NUM_POINTS)) &&  (entryAux2) == 1)
#define CHECK_POINTS_0(entry, lim, entryAux) ((COND_ENTRY((entry), (entryAux))) && ((lim) == TOTAL_NUM_POINTS_0))
 /*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
enum{START_SENT, CHARACTER_SENT, PARITY_SENT, STOP_SENT};
enum{SEND0, SEND1, NOTHING};
enum{TIMERCHAR, TIMER0, TIMER1, TIMERHALF0};

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
static double seno_values[NUM_POINTS];
static char localBitstream;

static uint8_t bitCounter;
static uint16_t entryCounter;
static uint16_t entryCounterAux;
static uint8_t oneCounter;
static uint8_t flagState = STOP_SENT;
static uint8_t flagSend = NOTHING;

static bool moduladorReady = false;


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH LOCAL SCOPE
 ******************************************************************************/
void createLookUpTableSin();
void sendCharacter (char* bitstream);
void sendStart();
void sendParity();
void sendStop();
void sendBit();
void send0();
void send1();
double getSinValue();


void initModuladorHandler(){
	createLookUpTableSin();
	//timerCharacter = timerGetId();
	configTimersPIT(TIMERCHAR, FREQ1, sendBit);
	//timerBit = timerGetId();
	configTimersPIT(TIMER1, FREQ1, send1);
	configTimersPIT(TIMER0, FREQ0, send0);
}

void createLookUpTableSin(){

    const double amplitude = 3.3; // Amplitud deseada en voltios

    for (int i = 0; i < NUM_POINTS; i++) {
        double angle = ((double)i / (NUM_POINTS - 1)) * 2 * M_PI; // Ángulo en radianes
        double sin_value = (sin(angle) + 1.0) * (amplitude / 2.0); // Cálculo del valor del seno escalado
        seno_values[i] = sin_value;
    }
}

void getFSKModEvent(uint8_t* event){
	if(moduladorReady){
		*event = MOD_FSK_EVENT;
		moduladorReady = false;
	}
}

void sendCharacter (char* bitstream){
	localBitstream = *bitstream;
	//timerStart(timerCharacter, TIMER_MS2TICKS(2000), TIM_MODE_PERIODIC, sendBit);
	startTimerPIT(TIMERCHAR);
	//sendBit();
	moduladorReady = true;
}

void sendStart(){
	//send0();
	startTimerPIT(TIMER0);
}

void sendParity(){
	if(oneCounter%2){
		//send0();
		startTimerPIT(TIMER0);
	}
	else{
		//send1();
		startTimerPIT(TIMER1);
	}
	oneCounter = 0;
}

void sendStop(){
	//send1();
	startTimerPIT(TIMER1);
}

void sendBit(void){
	switch(flagState){
			case STOP_SENT:{
				sendStart();
				++bitCounter;
				break;
			}
			case START_SENT:{
				if(CHECK_BIT(localBitstream, bitCounter-1)){
					//send1();
					startTimerPIT(TIMER1);
					oneCounter++;
				}
				else{
					//send0();
					startTimerPIT(TIMER0);
				}
				++bitCounter;
				if(bitCounter == 9){
					flagState = CHARACTER_SENT;
				}
				break;
			}
			case CHARACTER_SENT:{
					sendParity();
					++bitCounter;
					flagState = PARITY_SENT;
					break;
				}
			case PARITY_SENT:{
					sendStop();
					++bitCounter;
					flagState = STOP_SENT;
					break;
				}
		}
		if(bitCounter == 11){
			bitCounter = 0;
			//timerStop(timerCharacter);
			stopTimerPIT(TIMERCHAR);

		}
}

void send0(){
	//timerStart(timerBit, TIMER_MS2TICKS(1), TIM_MODE_PERIODIC, getSinValue);
	//startTimerPIT(TIMER0);
	flagSend = SEND0;
	send2DAC(getSinValue());
}

void send1(){
	//timerStart(timerBit, TIMER_MS2TICKS(2), TIM_MODE_PERIODIC, getSinValue);
	//startTimerPIT(TIMER1);
	flagSend = SEND1;
	send2DAC(getSinValue());
}


double getSinValue(void){
	uint16_t limit;
	if(flagSend == SEND1){
		limit = NUM_POINTS;
	}
	else{
		limit = TOTAL_NUM_POINTS_0;
	}

	double value = seno_values[entryCounter];
	entryCounter++;

	if(CHECK_POINTS_1(entryCounter, limit)){
		entryCounter = 0;
		//timerStop(timerBit);
		stopTimerPIT(TIMER1);
		flagSend = NOTHING;
	}
	else if(CHECK_POINTS_0(entryCounter, limit, entryCounterAux)){
		entryCounter = 0;
		++entryCounterAux;
		if(entryCounterAux == 2){
			entryCounterAux = 0;
			//timerStop(timerBit);
			stopTimerPIT(TIMER0);
			flagSend = NOTHING;
		}
	}

	//send2DAC(value);
	return value;
}
