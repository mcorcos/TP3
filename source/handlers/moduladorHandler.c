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
#include "timers/PIT.h"
#include "drivers/drv_DAC.h"
#include "handlers/moduladorHandler.h"
#include "math.h"
#include "fsm/fsmtable.h"


 /*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/


#define NUM_POINTS	100

#define BITSTREAM_LEN 8
#define WORD_LEN 11


 /*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
enum{START_SENT, CHARACTER_SENT, PARITY_SENT, STOP_SENT};
enum{SEND_BITSTREAM, IDLE};
enum{SEND0, SEND1, NOTHING};
enum{TIMERCHAR, TIMER0, TIMER1, TIMERHALF0};

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

static char localBitstream;
static char  completeWord[WORD_LEN];
static double seno_values[NUM_POINTS];
static uint8_t bitCounter = 0;
static uint16_t entryCounter = 0;
static uint16_t entryCounterAux = 0;
static uint8_t oneCounter = 0;
static uint8_t flagState = STOP_SENT;
static uint8_t flagSend = NOTHING;
static uint8_t modemStatus = IDLE;

static bool moduladorReady = false;

static tim_id_t timerChar;
static tim_id_t timerSend0;
static tim_id_t timerSend1;

static uint16_t value;

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
void nextState(void);
char parity(void);
void decimalToBinaryArrayWithPadding(int decimalValue, char binaryArray[]);

void initModuladorHandler(){
	createLookUpTableSin();
	timerChar = timerGetId();
	timerSend0 = timerGetId();
	timerSend1 = timerGetId();

	timerStart(timerChar,83, TIM_MODE_PERIODIC, sendBit);
	timerStart(timerSend0, 4, TIM_MODE_PERIODIC, send0);
	timerStart(timerSend1,8, TIM_MODE_PERIODIC, send1);



}


void getFSKModEvent(uint8_t* event){
	if(moduladorReady){
		*event = MOD_FSK_EVENT;
		moduladorReady = false;
	}
}
void createLookUpTableSin(){

    const double amplitude = 3.3; // Amplitud deseada en voltios

    for (int i = 0; i < NUM_POINTS; i++) {
        double angle = ((double)i / (NUM_POINTS - 1)) * 2 * M_PI; // Ángulo en radianes
        double sin_value = (sin(angle) + 1.0) * (amplitude / 2.0); // Cálculo del valor del seno escalado
        seno_values[i] = sin_value;
    }
}

void createWord(char  bitstream){

	completeWord[0] = '0';
	decimalToBinaryArrayWithPadding( bitstream , &completeWord[1] );
	completeWord[WORD_LEN - 2] = parity();
	completeWord[WORD_LEN - 1] = '1';

}


char parity(void){
	oneCounter = 0;
	for(uint8_t i = 1 ; i<BITSTREAM_LEN ; i++){
		if(completeWord[i]){
			oneCounter++;
		}
	}
	return ((oneCounter % 2 == 0 ) ? '1' : '0');
}


// Función para convertir un número decimal a binario con una longitud específica y almacenarlo en un arreglo
void decimalToBinaryArrayWithPadding(int decimalValue, char binaryArray[]) {
    // Asegurarse de que la longitud sea 8 bits
    const int length = 8;

    int index = 0;

    // Inicializar el arreglo con ceros
    for (int i = 0; i < length; i++) {
        binaryArray[i] = '0';
    }

    // Caso especial: si el número es 0
    if (decimalValue == 0) {
        binaryArray[length - 1] = '0';
    }

    // Convertir el número a binario
    while (decimalValue > 0 && index < length) {
        int remainder = decimalValue % 2;
        binaryArray[index] = (char)(remainder + '0');
        decimalValue /= 2;
        index++;
    }

}

void sendCharacter (char* bitstream){
	localBitstream = *bitstream;
	createWord(localBitstream);

	modemStatus = SEND_BITSTREAM;
	moduladorReady = true;
}


void sendBit(void){
	if(modemStatus == SEND_BITSTREAM){
		flagSend = NOTHING;
		if(completeWord[bitCounter] == '1'){
			flagSend = SEND1;
		}
		else{
			flagSend = SEND0;
		}

	}
	else{
	}
}

void send0(){

	if(flagSend == SEND0){

		send2DAC(getSinValue());

	}

}

void send1(){

	if(flagSend == SEND1){
		send2DAC(getSinValue());
	}

}


double getSinValue(void){

	value = seno_values[entryCounter];
	entryCounter++;
	if(flagSend == SEND0){
		if(entryCounter == 18){ //numpoint*1.83
				entryCounter = 0;
				flagSend = NOTHING;
				bitCounter++;
		}
	}
	else{
		if(entryCounter == NUM_POINTS){
		entryCounter = 0;
		flagSend = NOTHING;
		bitCounter++;
		}
	}

	if(bitCounter == 11){
		modemStatus = IDLE;
	}


	return value;
}


