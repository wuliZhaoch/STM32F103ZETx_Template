#include "includes.h"



uint32_t main_loop = 0;


int main(void)
{

    HAL_Init();

    SystemClock_Config();

    HAL_Delay_init();

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_RTC_Init();

    System_GetChipID();



    while (1)
    {
        HAL_GPIO_TogglePin(SYSTEM_LED0_GPIO_Port, SYSTEM_LED0_Pin);
        printf("System Mainloop is %ld\r\n", main_loop);
        main_loop++;
        HAL_Delay_us(1000000);



    }

}

