/*
 * lcd_driver.c
 *
 *  Created on: Mar 2, 2023
 *      Author: turkm
 */

#include "lcd_driver.h"
#include "stm32f4xx_hal.h"
#include "Delay_driver.h"


/*
 * @brief This function contains lcd start commands
 *
 */


void Lcd_Init(void)
{
	send_cmd(0x28);         // 4 bit, 2 line, 5x8
		HAL_Delay(1);
	send_cmd (0x08); 		//Display on/off control --> D=0,C=0, B=0  ---> display off
	    HAL_Delay(1);
	send_cmd (0x01);  		// clear display
	    HAL_Delay(1);
	    HAL_Delay(1);
	send_cmd(0x6);    		// I/D dicrements
		HAL_Delay(1);
	send_cmd(0x0C);  		//display on

}



/*
 * @brief This function sends 8-bit data to the LCD screen as 4 bits each.
 *
 * @param Takes character and cmd commands
 * @param when sending cmd commands to lcd display rs = low
 * 		  when sending character to lcd display    rs = high
 */


void send_lcd(char data, int rs)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, rs);

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, ((data>>3)&0x01));
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, ((data>>2)&0x01));
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, ((data>>1)&0x01));
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, ((data>>0)&0x01));

   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 1);
   delay_us(20);
   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 0);
     delay_us(20);

}




// set instruction

void send_cmd(char data)
{
	char val;

	// MSB bit
	val = ((data>>4)&0x0f);
	send_lcd(val,0);

	// LSB bit
	val = ((data)&0x0f);
	send_lcd(val,0);
}

/*
 * @brief Arranges the 8-bit character to be sent to the LCD screen as MSB 4 bit and LSB 4 bit
 *
 * @param  data gets character data
 */

void lcd_print(char data)
{
	char val;

	// MSB bit
	val = ((data>>4)&0x0f);
	send_lcd(val, 1);

	// LSB bit
	val = ((data)&0x0f);
	 send_lcd(val, 1);

}


/*
 * @brief Determines the starting line and
 * 		  column number of the characters to be sent to the LCD screen
 *
 * @param row ->  gets the line number, col -> gets the column  number
 */


void lcd_put_(int row, int col)
{
    switch (row)
    {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
    }
    send_cmd (col);
}


/*
 * @brief this function clears the lcd screen
 *
 */

void clear_lcd(void)
{
	send_cmd(0x01);
	HAL_Delay(2);
}



/*
 * @brief This function gets the characters and characters to be sent to the lcd display
 *
 * @param *str -> Gets the starting address of the characters and characters to be sent to the LCD screen
 *
 */


void lcd_send_string_newline(char *str)
{
	while(*str)
		lcd_print(*str++);
}

