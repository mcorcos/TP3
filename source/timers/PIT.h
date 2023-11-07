/***************************************************************************//**
  @file     PIT.h
  @brief    PIT
  @author   g4
 ******************************************************************************/

#ifndef PIT_H
#define PIT_H

#include <stdbool.h>
#include <stdint.h>

#include "hardware.h"

void initPIT(void);
void configTimersPIT(uint8_t id, uint16_t value, void(*callback)(void));
void startTimerPIT(uint8_t timer_idp);
void stopTimerPIT(uint8_t timer_idp);


#endif /* PIT_H */
