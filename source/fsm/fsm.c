/***************************************************************************//**
  @file     board.h
  @brief    Board management
  @author   G4
 ******************************************************************************/


/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "fsm.h"
#include <stdio.h>


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
 
 

STATE* fsm(STATE *p_tabla_estado,BYTE evento_actual)
{

   	while (p_tabla_estado -> evento != evento_actual && p_tabla_estado -> evento != FIN_TABLA)//Recorre las tablas de estado
		++p_tabla_estado;
	(*p_tabla_estado -> p_rut_accion)();          /*rutina de accion corresondiente*/
	p_tabla_estado=p_tabla_estado -> proximo_estado;   /*siguiente estado*/


      return(p_tabla_estado);

}

