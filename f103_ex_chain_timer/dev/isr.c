#include "sys.h"

/* User include goes here */
extern void example_chain_timer_callback(void);

/* TIMER */
void TIM2_IRQHandler(void)
{
    if (LL_TIM_IsActiveFlag_UPDATE(TIM2))
    {
        example_chain_timer_callback();
        LL_TIM_ClearFlag_UPDATE(TIM2);
    }
}