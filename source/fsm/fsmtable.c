/***************************************************************************//**
  @file     fsmtable.h
  @brief    Table for FSM
  @author   G4
 ******************************************************************************/


/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "fsmtable.h"
#include <stdio.h>
#include "fsm.h"
#include "handlers/uartEventHandler.h"
#include "handlers/bitstreamEventHandler.h"


 /*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
 
 

 /*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
 
 

/*Foward Declarations*/

extern STATE idle[]; // evento , Prox estado , rutirna de accion
extern STATE strToBitstream[];
extern STATE mod_fsk[];
extern STATE dac[];
extern STATE demod_fsk[];
extern STATE bitsreamToStr[];
extern STATE sendUart[];

// prototipos

static void do_nothing(void);





/*** tablas de estado ***/

/*** idle ***/

 STATE idle[]=
{
  	{UART_EVENT,strToBitstream,createbitstream},
	{ADC_EVENT,demod_fsk,recieveBitstream},
  	{FIN_TABLA,idle,do_nothing} //SEND 1 CUANDO ESTE EN IDLE!!
};


/*** estado_1 ***/

STATE strToBitstream[]=
{
	{STR2BIT_EVENT,mod_fsk,transmitBitstream},
	{FIN_TABLA,idle,do_nothing}
};

/*** estado_2 ***/

STATE mod_fsk[] =
{
	{MOD_FSK_EVENT,dac,do_nothing},
	{FIN_TABLA,idle,do_nothing}
};

/*** estado_3 ***/

STATE dac[] =
{
	{DAC_EVENT,idle,do_nothing},
	{FIN_TABLA,idle,do_nothing}
};

/*** estado_4 ***/

STATE demod_fsk[] =
{
	{DEMOD_FSK_EVENT,bitsreamToStr,do_nothing},
	{FIN_TABLA,idle,do_nothing}
};

/*** estado_5 ***/

STATE bitsreamToStr[] =
{
	{BIT2STR_EVENT,idle,sendWord},
	{FIN_TABLA,idle,do_nothing}
};

STATE sendUart[] =
{
	{WORD_SENDED_EVENT,idle,do_nothing},
	{FIN_TABLA,idle,do_nothing}
};

//========interfaz=================


STATE *FSM_GetInitState(void)
{
 	return (idle);
}



///=========Rutinas de accion===============



/*Dummy function*/
static void do_nothing(void)
{

}


