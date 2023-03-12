/*
 * lcd_driver.h
 *
 *  Created on: Mar 2, 2023
 *      Author: turkm
 */

#ifndef STM32F4XX_HAL_DRIVER_INC_LCD_DRIVER_H_
#define STM32F4XX_HAL_DRIVER_INC_LCD_DRIVER_H_



void Lcd_Init(void);
void send_lcd(char data, int rs);
void send_cmd(char data);
void lcd_print(char data);
void clear_lcd(void);
void lcd_send_string_newline(char *str);
void lcd_put_(int row, int col);

#endif /* STM32F4XX_HAL_DRIVER_INC_LCD_DRIVER_H_ */
