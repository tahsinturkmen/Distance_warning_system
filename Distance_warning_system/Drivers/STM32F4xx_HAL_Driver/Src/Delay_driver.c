
#include "stm32f4xx_hal.h"
#include "Delay_driver.h"

#define TIMER htim1

extern TIM_HandleTypeDef TIMER;


/* @brief This function provides minimum delay ( in microseconds)
 *
 * @note: Delay is provided by a timer
 *
 * @param  us specifies the delay time length, in microseconds.
 * */


void delay_us(uint16_t us)
{

	__HAL_TIM_SET_COUNTER(&TIMER,0);

	while(__HAL_TIM_GET_COUNTER(&TIMER) < us);

}
