/***************************************************************************//**
  @file     board.h
  @brief    Board management
  @author   G4
 ******************************************************************************/


/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "bitstreamEventHandler.h"

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
    int bitIndex = 0;
    int byteIndex = 0;
    int i, j;

    for (i = 0; input[i] != '\0'; i++) {
        char character = input[i];

        // Convertir el carácter a su representación binaria y agregar los bits al bitstream
        for (j = 7; j >= 0; j--) {
            bitstream[byteIndex] |= ((character >> j) & 1) << bitIndex;

            if (bitIndex == 7) {
                bitIndex = 0;
                byteIndex++;
            } else {
                bitIndex++;
            }
        }
    }

    // Asegurarse de que el último byte esté completo
    if (bitIndex > 0) {
        byteIndex++;
    }

    // Agregar un byte nulo al final para indicar el final del bitstream
    bitstream[byteIndex] = 0;

    str2BitsreamComplete = true;
}
 

void getStr2BitsreamEvent(uint8_t *ev){
 	if(str2BitsreamComplete){
 		str2BitsreamComplete = false; //Clear el flag
 		*ev = STR2BIT_EVENT;
 	}

 }
