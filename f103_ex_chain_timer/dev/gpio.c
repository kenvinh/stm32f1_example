#include "sys.h"

void gpio_init(void)
{
    LL_GPIO_InitTypeDef gpio_config;

    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);

    gpio_config.Mode = LL_GPIO_MODE_OUTPUT;
    gpio_config.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    gpio_config.Pin = LL_GPIO_PIN_13;
    gpio_config.Pull = LL_GPIO_PULL_UP;
    gpio_config.Speed = LL_GPIO_SPEED_FREQ_LOW;
    LL_GPIO_Init(GPIOC, &gpio_config);

}