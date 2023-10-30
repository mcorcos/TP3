/***************************************************************************//**
  @file     uartEventHandler.h
  @brief    UART event handler
  @author   G4
*****************************************************************************/

#ifndef HANDLERS_UARTEVENTHANDLER_H_
#define HANDLERS_UARTEVENTHANDLER_H_


/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdint.h>


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

 void initUartHandler(void);

 void sendWord(void);

void getUartEvent(uint8_t *ev);
void cleanUartEventFlag(void);
void createbitstream(void);

#endif /*  HANDLERS_UARTEVENTHANDLER_H_ */
