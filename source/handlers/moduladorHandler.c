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
#include "timers/timer.h"
#include "drivers/drv_DAC.h"
#include "handlers/moduladorHandler.h"


 /*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define NUM_POINTS 1000
#define FREQ0 2200
#define FREQ1 1200
#define TIMER0 ((1/FREQ0)/NUM_POINTS)
#define TIMER1 ((1/FREQ1)/NUM_POINTS)
#define TIMERCHAR 1/FREQ1

#define CHECK_BIT(char_value, bit_index) (((char_value) & (1 << (bit_index))) ? 1 : 0)

 /*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
enum{START_SENT, CHARACTER_SENT, PARITY_SENT, STOP_SENT};

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
static double seno_values[NUM_POINTS];
static char localBitstream;
static tim_id_t timerCharacter;
static tim_id_t timerBit;

static uint8_t bitCounter;
static uint16_t entryCounter;
static uint8_t oneCounter;

static uint8_t flagState = STOP_SENT;

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
void getSinValue();


void initModuladorHandler(){
	createLookUpTableSin();
	timerCharacter = timerGetId();
	timerBit = timerGetId();
}

void createLookUpTableSin(){

    const double amplitude = 3.3; // Amplitud deseada en voltios
    double seno_values[NUM_POINTS];

    for (int i = 0; i < NUM_POINTS; i++) {
        double angle = ((double)i / (NUM_POINTS - 1)) * 2 * M_PI; // Ángulo en radianes
        double sin_value = (sin(angle) + 1.0) * (amplitude / 2.0); // Cálculo del valor del seno escalado
        seno_values[i] = sin_value;
    }
}

void getFSKEvent(uint8_t* event){
	if(moduladorReady){
		*event = MOD_FSK_EVENT;
		moduladorReady = false;
	}
}

void sendCharacter (char* bitstream){
	localBitstream = *bitstream;
	timerStart(timerCharacter, TIMER_MS2TICKS(TIMERCHAR), TIM_MODE_PERIODIC, sendBit);
	moduladorReady = true;
}

void sendStart(){
	send0();
}

void sendParity(){
	if(oneCounter%2){
		send0();
	}
	else{
		send1();
	}
	oneCounter = 0;
}

void sendStop(){
	send1();
}

void sendBit(){
	switch(flagState){
		case STOP_SENT:{
			sendStart();
			flagState = START_SENT;
			++bitCounter;
			break;
		}
		case START_SENT:{
			if(CHECK_BIT(localBitstream, bitCounter)){
				send1();
				oneCounter++;
			}
			else{
				send0();
			}
			++bitCounter;
			if(bitCounter == 8){
				flagState = CHARACTER_SENT;
			}
			break;
		}
		case CHARACTER_SENT:{
				sendParity();
				flagState = PARITY_SENT;
				++bitCounter;
				break;
			}
		case PARITY_SENT:{
				sendStop();
				flagState = STOP_SENT;
				++bitCounter;
				break;
			}
	}
	if(bitCounter == 10){
		bitCounter = 0;
		timerStop(timerCharacter);

	}
}

void send0(){
	timerStart(timerBit, TIMER_MS2TICKS(TIMER0), TIM_MODE_PERIODIC, getSinValue);
}

void send1(){
	timerStart(timerBit, TIMER_MS2TICKS(TIMER1), TIM_MODE_PERIODIC, getSinValue);
}

void getSinValue(){
	double value = seno_values[entryCounter];
	entryCounter++;
	if(entryCounter == NUM_POINTS){
		entryCounter = 0;
		timerStop(timerBit);
	}
	send2DAC(value);
}

