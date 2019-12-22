#include "sys.h"

void example_chain_timer_callback(void)
{
    LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_13);
}

/**
* @brief: Example1: Chaining TIM2 and TIM3 to form a 32bit timer for 1 seconds count
*                   SYSCLK: 48MHz --> AHB div 2 --> HCLK: 24MHz --> APB1 div 1--> APBCLK: 24MHz
*                   On interval of 1s, PC13 will be toggle
* @param: void 
* @retval: void 
*/
void run_example(void)
{
    peripheral_init();
    
    /* Starting required peripherals */
    /* Slave start before master */
    timer_ch2_start();
    timer_ch1_start();

    for (;;)
    {
        //Led would be toggle by the chain timer above
    }
}