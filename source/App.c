/***************************************************************************//**
  @file     App.c
  @brief    Application functions
  @author   Grupo 4 Laboratorio de Microprocesadores:
  	  	  	Corcos, Manuel
  	  	  	Lesiuk, Alejandro
  	  	  	Paget, Milagros
  	  	  	Voss, Maria de Guadalupe
  ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "MCAL/board.h"
#include "timers/timer.h" // Llamo para Init timer
#include "drivers/drv_DEVBOARD.h" // Placa creada por el grupo con leds para debuggin
#include "drivers/drv_K64.h" // creamos funciones para acceder a switches y demas de la kinetis
#include "drivers/drv_UART.h"
#include "handlers/uartEventHandler.h"
#include "fsm/fsm.h"	    /*FSM engine (interprete)*/
#include "fsm/fsmtable.h"   /*FSM Table*/
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
//ID de UART0
#define DEFAULT_ID 0

//TIMERS MS DEFINE

//CANTIDADES



/*******************************************************************************
 *******************************************************************************
                        STRUCTS & TYPEDFS
 *******************************************************************************
 ******************************************************************************/


/*******************************************************************************
 *******************************************************************************
                        GLOBAL VARS DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static STATE *p2state=NULL;	/*Used to store FSM state*/
static uint8_t evento;

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION PROTOTYPES
 *******************************************************************************
 ******************************************************************************/

/*******************************************************************************
 *******************************************************************************
						GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



/* Función que se llama 1 vez, al comienzo del programa */
void App_Init (void)
{
	/* Init for drivers and board stuff*/

	init_K64Leds(); //init drv de los leds de la kinetis
	timerInit(); // init de timer
	init_DEVBOARD(); // init de la placa shield creada por el grupo
	initUART(); //Init UART
	initUartHandler(); //Init Rx and Tx for UART

    /* init for FSM */

    p2state=FSM_GetInitState();// Inicializo la FSM con el estado inicial
}


/* Función que se llama constantemente en un ciclo infinito */

void App_Run (void)
{
		evento = getEvent();
		p2state=fsm(p2state,evento);      //Se lo paso a la maquina de estados
}





