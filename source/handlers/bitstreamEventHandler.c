/***************************************************************************//**
  @file     bitstreamEventHandler.c
  @brief    Bitstream event handler
  @author   G4
 ******************************************************************************/


/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "bitstreamEventHandler.h"
#include "handlers/moduladorHandler.h"
#include "handlers/demoduladorHandler.h"

 /*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/


 /*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
static unsigned char bitstream[32]={0};
static bool str2BitsreamComplete = false;
/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/


 void stringToBitstream(const char *input) {
    //int bitIndex = 0;
    bitstream[0] = 0;
    int i, j;

    for (int i = 0; i < 8; i++) {
        if (input[0] & (1 << i)) {
            bitstream[0] |= (1 << (7 - i));
        }
    }
	bitstream[0] = input[0];

    str2BitsreamComplete = true;
}
 

void getStr2BitsreamEvent(uint8_t *ev){
 	if(str2BitsreamComplete){
 		str2BitsreamComplete = false; //Clear el flag
 		*ev = STR2BIT_EVENT;
 	}

 }


void transmitBitstream (){
	sendCharacter(bitstream);
}

void recieveBitstream (void){
	bitstream[0] = recieveCharacter();
}
