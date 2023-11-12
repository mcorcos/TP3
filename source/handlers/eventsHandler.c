/***************************************************************************//**
  @file     eventsHandler.c
  @brief    Event handler
  @author   G4
 ******************************************************************************/


/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "eventsHandler.h"
#include "uartEventHandler.h"
#include "bitstreamEventHandler.h"
#include "moduladorHandler.h"
#include "demoduladorHandler.h"
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
 
uint8_t getEvent(void){
	uint8_t event = NO_EVENT;
	getUartEvent(&event);
	getStr2BitsreamEvent(&event);
	getFSKModEvent(&event);
	//getFSKDemodEvent(&event);
	return event;
 }
