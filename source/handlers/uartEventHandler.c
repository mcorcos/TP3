/***************************************************************************//**
  @file     board.h
  @brief    Board management
  @author   G4
 ******************************************************************************/


/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "uartEventHandler.h"
#include "fsm/fsmtable.h"
#include "drivers/drv_UART.h"
#include "timers/timer.h" // Llamo para Init timer

 /*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
 
#define TIMER_MS 10

 //Timers para UART. Para transmitir parte del mensaje cada X ms
//Para chequear si se ingreso algo por teclado.
static tim_id_t timerTx;
static tim_id_t timerRx;
static char bufferWord[256] = "A";
static bool	wordReceivedUart = false;
static uint16_t wordIterator = 0;
 /*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
void callbackTimerTx(void);
void callbackTimerRx(void);

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

void initUartHandler(void){

	/* Timers stuff */
	timerTx = timerGetId();//inicio los timers de UART
	timerRx = timerGetId();

	timerStart(timerTx, TIMER_MS2TICKS(TIMER_MS), TIM_MODE_PERIODIC, callbackTimerTx); //info para los timers
	timerStart(timerRx, TIMER_MS2TICKS(TIMER_MS), TIM_MODE_PERIODIC, callbackTimerRx); //info para los timers
}



void sendWord(void){ //callback para transmision de datos por UART
	package_t package;
	uint16_t size = 5; //dummy
	package.data[0] = &bufferWord;
	sendPackage(package,size);
}


void callbackTimerRx(void){ //Callback para recepecion de datos de UART

	if(getRxInterruptFlag()){

		clearRxInterrupt();

		package_t package = receivePackage();

		bufferWord[wordIterator++] = package.data[0];
		if((package.data[0] == '\n') || package.data[0] == '\r'){ //se termino el string
			wordReceivedUart = true;
			wordIterator = 0;
		}
	}
}


void callbackTimerTx(void){ //Callback para recepecion de datos de UART

	package_t package;
	uint16_t size = 1; //dummy
    for (int i = 0; i < size; i++) {
        package.data[i] = bufferWord[i];
    }

//	sendPackage(package,size);

}


void getUartEvent(uint8_t *ev){
	if(wordReceivedUart){
		wordReceivedUart = false; //Clear el flag
		*ev = UART_EVENT;
	}
}
void cleanUartEventFlag(void){
	wordReceivedUart = false;
}


void createbitstream(void){
	stringToBitstream(bufferWord);
}



