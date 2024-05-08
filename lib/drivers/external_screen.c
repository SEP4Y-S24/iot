
#ifndef NATIVE_TESTING
#include "external_screen.h" /* Include the correct header file */

/* Send a command to the LCD */
void external_screen_command(unsigned char cmnd)
{
    LCD_Data_Port = cmnd;
    LCD_Command_Port &= ~(1 << RS); /* RS=0 command register */
    LCD_Command_Port &= ~(1 << RW); /* RW=0 write operation */
    LCD_Command_Port |= (1 << EN);  /* Enable pulse */
    _delay_us(1);
    LCD_Command_Port &= ~(1 << EN);
    _delay_ms(3);
}

/* Send a character to the LCD */
void external_screen_char(unsigned char char_data)
{
    LCD_Data_Port = char_data;
    LCD_Command_Port |= (1 << RS);  /* RS=1 Data register */
    LCD_Command_Port &= ~(1 << RW); /* RW=0 write operation */
    LCD_Command_Port |= (1 << EN);  /* Enable Pulse */
    _delay_us(1);
    LCD_Command_Port &= ~(1 << EN);
    _delay_ms(1);
}

/* Initialize the LCD */
void external_screen_init(void)
{
    LCD_Command_Dir = 0xFF; /* Make LCD command port direction as output */
    LCD_Data_Dir = 0xFF;    /* Make LCD data port direction as output */
    _delay_ms(20);          /* LCD Power ON delay always >15ms */

    external_screen_command(0x38); /* Initialization of 16x2 LCD in 8-bit mode */
    external_screen_command(0x0C); /* Display ON, Cursor OFF */
    external_screen_command(0x06); /* Auto Increment cursor */
    external_screen_command(0x01); /* Clear display */
    external_screen_command(0x80); /* Cursor at home position */
}

/* Display a string on the LCD */
void external_screen_string(const char *str)
{
    external_screen_clear();
    while (*str)
    {
        external_screen_char(*str++);
    }
}

/* Display a string on the LCD at a specific row and position */
void external_screen_string_xy(char row, char pos, const char *str)
{
    if (row == 1 && pos < 16)
        external_screen_command((pos & 0x0F) | 0x80); /* Command for first row */
    else if (row == 2 && pos < 16)
        external_screen_command((pos & 0x0F) | 0xC0); /* Command for second row */

    external_screen_string(str); /* Call external_screen_string function */
}

/* Clear the LCD */
void external_screen_clear(void)
{
    external_screen_command(0x01); /* Clear display */
    external_screen_command(0x80); /* Cursor at home position */
}

/* Display two strings on two separate rows at specified positions */
void external_screen_two_rows(const char *row1_text, char row1_pos, const char *row2_text, char row2_pos)
{
    external_screen_string_xy(1, row1_pos, row1_text); /* Display on the first row */
    external_screen_string_xy(2, row2_pos, row2_text); /* Display on the second row */
}

/* Function to scroll text on the LCD for a specified number of cycles */
void external_screen_static_with_scroll(const char *static_text, const char *scroll_text, uint16_t delay, int cycles)
{
    /* Display a static string on the first row */
    external_screen_string_xy(1, 0, static_text);

    int text_length = 0;
    while (scroll_text[text_length] != '\0')
        text_length++; /* Calculate the length of the scrolling text */

    int display_length = 16; /* Length of LCD row */
    int start_pos = 0;

    for (int cycle = 0; cycle < cycles; cycle++)
    {
        while (start_pos < text_length - display_length)
        {
            /* Display the current segment of the scrolling string */
            external_screen_string_xy(2, 0, &scroll_text[start_pos]);

            /* Wait for a short period to give the scrolling effect */
            _delay_ms(delay);

            /* Update the starting position for scrolling */
            start_pos++;
        }

        start_pos = 0; /* Reset start position for scrolling */

        /* Clear the second row */
        external_screen_command(0xC0);
        for (int i = 0; i < display_length; i++)
        {
            external_screen_char(' '); // Clear the display
        }
    }
}
#endif