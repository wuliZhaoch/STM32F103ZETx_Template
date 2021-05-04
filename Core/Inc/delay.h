#ifndef _DELAY_H
#define _DELAY_H
#include "system.h"
#include "main.h"

void HAL_Delay_init(void);
void HAL_Delay_ms(uint16_t nms);
void HAL_Delay_us(uint32_t nus);

#endif

