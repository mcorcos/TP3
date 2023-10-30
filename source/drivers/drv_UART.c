
/***************************************************************************//**
  @file     drv_UART.C
  @brief    Driver for UART
  @author   G4
 ******************************************************************************/


/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "drv_UART.h"

 /*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/


#define DEFAULT_ID 0

#define SIZE_OF_PACKAGE_RX 1
 /*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

 void initUART(void){
	 uint8_t id = DEFAULT_ID;
	 uart_cfg_t configure = {.baudrate = UART_HAL_DEFAULT_BAUDRATE};
	 uartInit(id, configure);
 }

 package_t receivePackage(void){
	 package_t package;
	 if(uartIsRxMsg(DEFAULT_ID)){
		 if(uartGetRxMsgLength(DEFAULT_ID) >= SIZE_OF_PACKAGE_RX  ){
			 uartReadMsg(DEFAULT_ID,package.data, SIZE_OF_PACKAGE_RX);
		 }
	 }
	 return package;

 }

 void sendPackage(package_t package,uint16_t size){
	 if(uartIsTxMsgComplete(DEFAULT_ID)){
		 uartWriteMsg(DEFAULT_ID, package.data, size);
	 }
	 else{


	 }


 }
