#include "stm32g070xx.h"
#include "tim.h"

/* Configure timer to timeout every second */
/* Meaning 1Hz */
/* System: 16MHz */
/* APB = PCLK1, Default=System=16 000 000 */
/* APB2 = PCLK2, Default=System=16 000 000 */
/* Divide by 1600 and 10000 to get to 1Hz */
/* Timer Prescalar: 1600 => 10,000 Hz */
/* Timer period (auto reload value) = 10000*/

TIM_HandleTypeDef TIMER;


void tim_timebase_init(void)
{
    /* Enable clock access */
    _TIMx_CLK_ENABLE;
    /* Assign Timer */
    TIMER.Instance = TIM3;
    TIMER.Init.Prescaler = 1600-1;  //-1 because we count from zero
    TIMER.Init.Period = 10000-1;
    TIMER.Init.ClockDivision = TIM_COUNTERMODE_UP;
    TIMER.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_Base_Init(&TIMER);

    /* Setup for interrupt */
    HAL_NVIC_SetPriority(TIMx_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIMx_IRQn);

    /* Start the TIM Base generation in interrupt mode */
    HAL_TIM_Base_Start_IT(&TIMER);
}

void TIMx_IRQHandler(void)
{
    /* Call default ST Timer Handler */
    HAL_TIM_IRQHandler(&TIMER);
}
