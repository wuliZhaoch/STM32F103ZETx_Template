/**
  ******************************************************************************
  * File Name          : RTC.c
  * Description        : This file provides code for the configuration
  *                      of the RTC instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "rtc.h"

/* USER CODE BEGIN 0 */

RTC_DateTypeDef GetData;
RTC_TimeTypeDef GetTime;

/* USER CODE END 0 */

RTC_HandleTypeDef hrtc;

/* RTC init function */
void MX_RTC_Init(void)
{
    RTC_TimeTypeDef sTime ={0};
    RTC_DateTypeDef DateToUpdate = {0};
    RTC_DateTypeDef DateBuff = {0};

    __HAL_RCC_BKP_CLK_ENABLE();
    __HAL_RCC_PWR_CLK_ENABLE();

    /** Initialize RTC Only */
    hrtc.Instance = RTC;
    hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
    hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
    if (HAL_RTC_Init(&hrtc) != HAL_OK)
    {
        Error_Handler();
    }

    /* USER CODE BEGIN Check_RTC_BKUP */
    if (HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR1) != BKUP_SET_FLAG)
    {
        /* USER CODE END Check_RTC_BKUP */

        /** Initialize RTC and set the Time and Date
         */
        sTime.Hours = 0x19;
        sTime.Minutes = 0x30;
        sTime.Seconds = 0x0;

        if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
        {
            Error_Handler();
        }
        DateToUpdate.WeekDay = RTC_WEEKDAY_TUESDAY;
        DateToUpdate.Month = RTC_MONTH_MAY;
        DateToUpdate.Date = 0x4;
        DateToUpdate.Year = 0x21;

        if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BCD) != HAL_OK)
        {
            Error_Handler();
        }

        __HAL_RTC_SECOND_ENABLE_IT(&hrtc,RTC_IT_SEC);    //开启RTC时钟秒中断
        DateBuff = DateToUpdate;  //把日期数据拷贝到自己定义的data中
        HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, BKUP_SET_FLAG);//向指定的后备区域寄存器写入数据
        HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR2, (uint16_t)DateBuff.Year);
        HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR3, (uint16_t)DateBuff.Month);
        HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR4, (uint16_t)DateBuff.Date);
        HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR5, (uint16_t)DateBuff.WeekDay);
    } else {

        DateBuff.Year    = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR2);
        DateBuff.Month   = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR3);
        DateBuff.Date    = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR4);
        DateBuff.WeekDay = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR5);
        DateToUpdate = DateBuff;
        if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BCD) != HAL_OK)
        {
          Error_Handler();
        }
//        __HAL_RTC_SECOND_ENABLE_IT(&hrtc,RTC_IT_SEC);    //开启RTC时钟秒中断
    }



}

void HAL_RTC_MspInit(RTC_HandleTypeDef* rtcHandle)
{

  if(rtcHandle->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspInit 0 */

  /* USER CODE END RTC_MspInit 0 */
    HAL_PWR_EnableBkUpAccess();
    /* Enable BKP CLK enable for backup registers */
    __HAL_RCC_BKP_CLK_ENABLE();
    /* RTC clock enable */
    __HAL_RCC_RTC_ENABLE();

    /* RTC interrupt Init */
    HAL_NVIC_SetPriority(RTC_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(RTC_IRQn);
    HAL_NVIC_SetPriority(RTC_Alarm_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(RTC_Alarm_IRQn);
  /* USER CODE BEGIN RTC_MspInit 1 */

  /* USER CODE END RTC_MspInit 1 */
  }
}

void HAL_RTC_MspDeInit(RTC_HandleTypeDef* rtcHandle)
{

  if(rtcHandle->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspDeInit 0 */

  /* USER CODE END RTC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_RTC_DISABLE();

    /* RTC interrupt Deinit */
    HAL_NVIC_DisableIRQ(RTC_IRQn);
    HAL_NVIC_DisableIRQ(RTC_Alarm_IRQn);
  /* USER CODE BEGIN RTC_MspDeInit 1 */

  /* USER CODE END RTC_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
