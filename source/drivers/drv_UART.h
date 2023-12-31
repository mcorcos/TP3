/***************************************************************************//**
  @file     drv_UART.h
  @brief    Driver for UART
  @author   G4
 ******************************************************************************/


#ifndef _DRV_UART_H_
#define _DRV_UART_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "source/protocols/uart.h"

 /*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define BAUDRATE_DEFAULT 9600
#define DATA_TYPE_SIZE 1
 /*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef struct{
 	char data[DATA_TYPE_SIZE]; // el identificador
 }package_t;


/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
 void initUART(void);
 package_t receivePackage(void);
 void sendPackage(package_t package,uint16_t size);


#endif // _DRV_UART_H_








