/*
 * system.h
 *
 *  Created on: 2021.04.04
 *      Author: Wulizhaoch
 *
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "common.h"


void RCC_CLK_Enable(void);

void SystemClock_Config(void);

void Error_Handler(void);

void HAL_Delay_US(uint32_t Delay_us);

#endif /* SYSTEM_H_ */
