#include "stm32f4xx_hal.h"
#include "HC_SR04.h"
#include "Delay_driver.h"


extern TIM_HandleTypeDef htim1;
uint16_t counter1 = 0;
uint16_t counter2 = 0;
uint16_t distance = 0;


/*
 * @brief This function specifies the return value of the distance in cm
 *
 */


uint16_t Get_Hcsr04_distance(void)
{

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);
		delay_us(10);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);

	counter1 = __HAL_TIM_GET_COUNTER(&htim1);

	while( !HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_8) );

	counter1 = __HAL_TIM_GET_COUNTER(&htim1);

	while( HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_8) )
	{
		counter2 = __HAL_TIM_GET_COUNTER(&htim1);

	}

	distance = (counter2-counter1)/58;   //  distance in cm  =  time / 58

return distance;



}
