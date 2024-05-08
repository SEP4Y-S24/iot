/**
 * @file lcd.h
 * @author Marcus Mitelea
 * @brief 16x2 LCD driver (8bit mode)
 * @version 0.1
 * @date 2024-05-01
 *
 * @copyright Copyright (c) 2024
 */

/* methods are called with "external_screen" keyword because platformio would nag me when I used lcd_init with "did you mean log_init" */

#pragma once

#include <avr/io.h>
#include <util/delay.h>

/* LCD Port and Pin Definitions */
#define LCD_Data_Dir DDRA    /* Define LCD data port direction */
#define LCD_Command_Dir DDRC /* Define LCD command port direction register */
#define LCD_Data_Port PORTA
#define LCD_Command_Port PORTC
#define RS PC0 /* Define Register Select pin */
#define RW PC1 /* Define Read/Write signal pin */
#define EN PC2 /* Define Enable signal pin */

/* LCD Function Prototypes */

/**
 * @brief Sends a command to the external LCD screen.
 * @param cmnd The command to be sent.
 */
void external_screen_command(unsigned char cmnd);

/**
 * @brief Initializes the external LCD screen.
 */
void external_screen_init(void);

/**
 * @brief Clears the display of the external LCD screen.
 */
void external_screen_clear(void);

/* LCD Displaying Stuff */

/**
 * @brief Displays a character on the external LCD screen.
 * @param char_data The character to be displayed.
 */
void external_screen_char(unsigned char char_data);

/**
 * @brief Displays a string on the external LCD screen.
 * @param str The string to be displayed.
 */
void external_screen_string(const char *str);

/**
 * @brief Displays a string on the external LCD screen at a specific position.
 * @param row The row number (0 or 1) where the string will be displayed.
 * @param pos The starting position of the string on the row.
 * @param str The string to be displayed.
 */
void external_screen_string_xy(char row, char pos, const char *str);

/**
 * @brief Displays two strings on the external LCD screen, each on a separate row.
 * @param row1_text The string to be displayed on the first row.
 * @param row1_pos The starting position of the first string on the first row.
 * @param row2_text The string to be displayed on the second row.
 * @param row2_pos The starting position of the second string on the second row.
 */
void external_screen_two_rows(const char *row1_text, char row1_pos, const char *row2_text, char row2_pos);

/**
 * @brief Displays a static text followed by a scrolling text on the external LCD screen.
 * @param static_text The static text to be displayed.
 * @param scroll_text The scrolling text to be displayed.
 * @param delay The delay between each scroll step.
 * @param cycles The number of times the scrolling text should be repeated.
 */
void external_screen_static_with_scroll(const char *static_text, const char *scroll_text, uint16_t delay, int cycles);
