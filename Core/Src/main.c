#include "includes.h"



SystemChipIDTypeDef ChipID_Val = {0};


uint32_t main_loop = 0;


int main(void)
{

    HAL_Init();

    SystemClock_Config();

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_USART1_UART_Init();


    if (SystemChipID(&ChipID_Val) == HAL_OK)
    {
        printf("SystemChipID is %lx %lx %lx\r\n", ChipID_Val.ChcipID_H,
                ChipID_Val.ChcipID_M, ChipID_Val.ChcipID_L);
    }


    while (1)
    {
        HAL_GPIO_TogglePin(SYSTEM_LED0_GPIO_Port, SYSTEM_LED0_Pin);
        printf("System Mainloop is %ld\r\n", main_loop);
        main_loop++;
        HAL_Delay_US(1000000);

    }

}

