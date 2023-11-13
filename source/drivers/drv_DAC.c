
/***************************************************************************//**
  @file     drv_DAC.c
  @brief    DAC driver
  @author   G4
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "drv_DAC.h"
#include "MK64F12.h"

 /*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define DACData_LOW_LEN	8
#define MAP_CONST 1024

 /*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef struct dataDAC{
	uint8_t dataDACL;
	uint8_t dataDACH;
}dataDAC_t;

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
static DAC_Type* DAC0_ptr = DAC0;
static SIM_Type* sim_ptr = SIM;

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
	// Clock Gating
	sim_ptr->SCGC2 |= SIM_SCGC2_DAC0_MASK;

	DAC0_ptr->C0 &= ~(DAC_C0_DACEN_MASK |
					 DAC_C0_DACRFS_MASK |
					 DAC_C0_DACTRGSEL_MASK |
					 DAC_C0_LPEN_MASK);
	DAC0_ptr->C0 |= (DAC_C0_DACEN(1) |			// Enable module
					 DAC_C0_DACRFS(1) |			// Reference voltage DACREF_2
					 DAC_C0_DACTRGSEL(1) |		// Software triggered
					 DAC_C0_LPEN(1));			// Low-power mode

	DAC0_ptr->C1 &= ~(DAC_C1_DMAEN_MASK  |
					 DAC_C1_DACBFMD_MASK |
					 DAC_C1_DACBFEN_MASK);
	DAC0_ptr->C1 |= (DAC_C1_DMAEN(0) |			// DMA disabled
					 DAC_C1_DACBFMD(0) |		// Normal Mode (circular buffer)
					 DAC_C1_DACBFEN(0));		// Buffer Disabled


}

void send2DAC(double value){
	//Habría que mandarle a un pin el value :P
	value *= MAP_CONST;
	DAC0_ptr->DAT->DATL = DAC_DATL_DATA0((uint16_t)value);
	DAC0_ptr->DAT->DATH = DAC_DATH_DATA1(((uint16_t)value) >> DACData_LOW_LEN);
}
