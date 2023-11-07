/***************************************************************************//**
  @file     bitstreamEventHandler.h
  @brief    Bitstream event handler
  @author   G4
******************************************************************************/

#ifndef HANDLERS_BITSTREAMEVENTHANDLER_H_
#define HANDLERS_BITSTREAMEVENTHANDLER_H_


/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "fsm/fsmtable.h"
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
 void stringToBitstream(const char *input);
 void getStr2BitsreamEvent(uint8_t *ev);
 void transmitBitstream (void);
 void recieveBitstream (void);
 
#endif /*  HANDLERS_BITSTREAMEVENTHANDLER_H_ */
