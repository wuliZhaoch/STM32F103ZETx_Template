/*
 * chip_id.h
 *
 *  Created on: 2021-04-02
 *      Author: wuliZhao_ch
 */
#ifndef CHIP_ID_H_
#define CHIP_ID_H_

#include "main.h"
#include "system.h"
#include "usart.h"

#define CHIPID_LEN 3


typedef struct {
    uint32_t Chip_ID_H;
    uint32_t Chip_ID_M;
    uint32_t Chip_ID_L;
} ChipIDTypeDef;

void GET_ChipID(ChipIDTypeDef *CHIPID);
void System_GetChipID(void);

#endif
