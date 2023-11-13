/***************************************************************************//**
  @file     demoduladorHandler.h
  @brief    Handler del demodulador
  @author   G4
 ******************************************************************************/

#ifndef HANDLERS_DEMODULADORHANDLER_H_
#define HANDLERS_DEMODULADORHANDLER_H_


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
void initDemoduladorHandler();
void getFSKDemodEvent(uint8_t* event);
void recieveADCBitstream(void);
char recieveCharacter(void);

#endif /*  HANDLERS_DEMODULADORHANDLER_H_ */
