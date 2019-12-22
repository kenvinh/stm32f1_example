#include "sys.h"

void timer_init(void)
{
    LL_TIM_InitTypeDef tim_init;
    ErrorStatus err;
    LL_RCC_ClocksTypeDef clock_info;
    LL_RCC_GetSystemClocksFreq(&clock_info);
    
    /* Simple calculate preload for LSB and MSB timer count 
     * Target setting for this example is 0.5s or 2 Hz
     * Assume prescaler is 1 (0), then LSB and MSB auto reload calculate: PCLK1 / 2 = TIM1_Count * TIM2_Count
     * For simplicity assume CPU clock always >=8MHz, then TIM1 can be fixed 8000. TIM2_Count = PCLK1 / (2 * TIM1_Count)
     * */
    
    LL_TIM_StructInit(&tim_init);
    tim_init.CounterMode = LL_TIM_COUNTERMODE_DOWN;

    /* Master channel (LSB count): TIM1 */
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1);
    tim_init.Prescaler = 0;
    tim_init.Autoreload = 8000 - 1;
    err = LL_TIM_Init(TIM1, &tim_init);
    LL_TIM_EnableARRPreload(TIM1);
    LL_TIM_SetClockSource(TIM1, LL_TIM_CLOCKSOURCE_INTERNAL);
    LL_TIM_SetTriggerOutput(TIM1, LL_TIM_TRGO_UPDATE);
    LL_TIM_EnableMasterSlaveMode(TIM1);

    /* Slave channel (MSB count): TIM2 */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
    tim_init.Prescaler = 0;
    tim_init.Autoreload = (clock_info.PCLK1_Frequency / 16000) - 1;
    err = LL_TIM_Init(TIM2, &tim_init);
    LL_TIM_EnableARRPreload(TIM2);
    LL_TIM_SetClockSource(TIM2, LL_TIM_CLOCKSOURCE_INTERNAL);
    LL_TIM_SetTriggerInput(TIM2, LL_TIM_TS_ITR0);
    LL_TIM_SetSlaveMode(TIM2, LL_TIM_SLAVEMODE_GATED | LL_TIM_SLAVEMODE_TRIGGER);
    LL_TIM_DisableIT_TRIG(TIM2);
    LL_TIM_DisableDMAReq_TRIG(TIM2);
    LL_TIM_SetTriggerOutput(TIM2, LL_TIM_TRGO_RESET);
    LL_TIM_DisableMasterSlaveMode(TIM2);

    LL_TIM_EnableIT_UPDATE(TIM2);
    LL_TIM_ClearFlag_UPDATE(TIM2);

    NVIC_SetPriority(TIM2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    NVIC_EnableIRQ(TIM2_IRQn);
}

void timer_ch1_start(void)
{
    LL_TIM_EnableCounter(TIM1);
}

void timer_ch2_start(void)
{
    LL_TIM_EnableCounter(TIM2);
}
