#include "sys.h"

void peripheral_init(void)
{
    clock_init();
    gpio_init();
    timer_init();
}

void peripheral_init_failed_trap(void)
{
    /* Trap initialization if it failed on init */
    
}