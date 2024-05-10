#ifndef NATIVE_TESTING

#include "tone.h"
#include "includes.h"

#define BUZ_BIT PA7
#define BUZ_DDR DDRA
#define BUZ_PORT PORTA

void tone_init()
{
    BUZ_DDR |= (1 << BUZ_BIT);
}

void tone_play(uint16_t frequency, uint16_t duration)
{

    // Calculate the half-period delay in microseconds
    uint16_t delay_us = 500000 / frequency;

    // Calculate the number of cycles needed for the specified duration
    uint16_t loop = (uint16_t)((uint32_t)duration * 1000 / (2 * delay_us));

    // Initialize Timer2 in normal mode
    TCCR2A = 0;
    TCCR2B = 0;

    uint8_t prescaler_bits = 0;
    uint16_t prescaler_value = 0;

    // Choose prescaler based on delay
    if (delay_us > 4000)
    {
        prescaler_bits = (1 << CS22) | (1 << CS21) | (1 << CS20); // 1024
        prescaler_value = 1024;
    }
    else if (delay_us > 2000)
    {
        prescaler_bits = (1 << CS22) | (1 << CS21); // 256
        prescaler_value = 256;
    }
    else if (delay_us > 1000)
    {
        prescaler_bits = (1 << CS22) | (1 << CS20); // 128
        prescaler_value = 128;
    }
    else if (delay_us > 500)
    {
        prescaler_bits = (1 << CS22); // 64
        prescaler_value = 64;
    }
    else if (delay_us > 125)
    {
        prescaler_bits = (1 << CS21) | (1 << CS20); // 32
        prescaler_value = 32;
    }
    else
    {
        prescaler_bits = (1 << CS21); // 8
        prescaler_value = 8;
    }

    // Set the prescaler
    TCCR2B = prescaler_bits;

    // Calculate the number of timer ticks needed for the specified delay
    uint8_t num_ticks = (F_CPU / 1000000UL) * delay_us / prescaler_value;

    // Generate the tone
    for (uint16_t i = 0; i < loop; i++)
    {
        // Set PA1 high
        BUZ_PORT |= (1 << BUZ_BIT);
        // Reset the timer counter
        TCNT2 = 0;

        // Wait until the timer counter reaches the required ticks
        while (TCNT2 < num_ticks)
        {
            // Busy-wait
        }

        // Set PA1 low
        BUZ_PORT &= ~(1 << BUZ_BIT);
        // Reset the timer counter
        TCNT2 = 0;

        // Wait until the timer counter reaches the required ticks
        while (TCNT2 < num_ticks)
        {
            // Busy-wait
        }
    }

    TCCR2B = 0;
}

void tone_play_starwars()
{

    tone_play(392, 500);  // G4 for 500 ms
    tone_play(392, 500);  // G4 for 500 ms
    tone_play(392, 500);  // G4 for 500 ms
    tone_play(311, 350);  // E♭4 for 350 ms
    tone_play(466, 150);  // B4 for 150 ms
    tone_play(392, 500);  // G4 for 500 ms
    tone_play(311, 350);  // E♭4 for 350 ms
    tone_play(466, 150);  // B4 for 150 ms
    tone_play(392, 1000); // G4 for 1000 ms

    tone_play(587, 500);  // D5 for 500 ms
    tone_play(587, 500);  // D5 for 500 ms
    tone_play(587, 500);  // D5 for 500 ms
    tone_play(622, 350);  // D#5 for 350 ms
    tone_play(466, 150);  // B4 for 150 ms
    tone_play(370, 500);  // F#4 for 500 ms
    tone_play(311, 350);  // Eb4 for 350 ms
    tone_play(466, 150);  // B4 for 150 ms
    tone_play(392, 1000); // G4 for 1000 ms
}

void tone_play_despacito()
{
    // Notes frequencies (Hz)
    const int C4 = 262;
    const int D4 = 294;
    const int E4 = 330;
    const int F4 = 349;
    const int G4 = 392;
    const int A4 = 440;
    const int B4 = 494;
    const int C5 = 523;
    const int D5 = 587;

    // Note durations (ms)
    const int quarter = 500;
    const int eighth = quarter / 2;
    const int dotted_eighth = (int)(eighth * 1.5);

    // Play melody
    tone_play(E4, dotted_eighth);
    // _delay_ms(dotted_eighth);
    tone_play(D4, eighth);
    // _delay_ms(eighth);
    tone_play(C4, eighth);
    // _delay_ms(eighth);
    tone_play(D4, dotted_eighth);
    // _delay_ms(dotted_eighth);
    tone_play(E4, eighth);
    // _delay_ms(eighth);
    tone_play(E4, eighth);
    // _delay_ms(eighth);
    tone_play(E4, dotted_eighth);
    // _delay_ms(dotted_eighth);
    tone_play(D4, eighth);
    // _delay_ms(eighth);
    tone_play(D4, eighth);
    // _delay_ms(eighth);
    tone_play(D4, dotted_eighth);
    // _delay_ms(dotted_eighth);
    tone_play(E4, eighth);
    // _delay_ms(eighth);
    tone_play(G4, quarter);
    // _delay_ms(quarter);
    tone_play(G4, eighth);
    // _delay_ms(eighth);
    tone_play(G4, quarter);
    // _delay_ms(quarter);
    tone_play(F4, eighth);
    // _delay_ms(eighth);
    tone_play(F4, eighth);
    // _delay_ms(eighth);
    tone_play(F4, eighth);
    // _delay_ms(eighth);
    tone_play(E4, quarter);
    // _delay_ms(quarter);
    tone_play(E4, eighth);
    // _delay_ms(eighth);
    tone_play(E4, eighth);
    // _delay_ms(eighth);
    tone_play(E4, eighth);
    // _delay_ms(eighth);
    tone_play(E4, eighth);
    // _delay_ms(eighth);
    tone_play(E4, eighth);
    // _delay_ms(eighth);
    tone_play(F4, eighth);
    // _delay_ms(eighth);
    tone_play(G4, quarter);
    // _delay_ms(quarter);
    tone_play(G4, eighth);
    // _delay_ms(eighth);
    tone_play(G4, quarter);
    // _delay_ms(quarter);
    tone_play(F4, eighth);
    // _delay_ms(eighth);
    tone_play(F4, eighth);
    // _delay_ms(eighth);
    tone_play(F4, eighth);
    // _delay_ms(eighth);
    tone_play(E4, quarter);
    // _delay_ms(quarter);
    tone_play(E4, eighth);
    // _delay_ms(eighth);
    tone_play(E4, eighth);
    // _delay_ms(eighth);
    tone_play(E4, eighth);
    // _delay_ms(eighth);
    tone_play(E4, eighth);
    // _delay_ms(eighth);
    tone_play(E4, eighth);
    // _delay_ms(eighth);
    tone_play(F4, eighth);
    // _delay_ms(eighth);
    tone_play(G4, quarter);
    // _delay_ms(quarter);
    tone_play(G4, eighth);
    // _delay_ms(eighth);
    tone_play(G4, quarter);
    // _delay_ms(quarter);
    tone_play(F4, eighth);
    // _delay_ms(eighth);
    tone_play(F4, eighth);
    // _delay_ms(eighth);
    tone_play(F4, eighth);
    // _delay_ms(eighth);
    tone_play(E4, quarter);
    // _delay_ms(quarter);
    tone_play(E4, eighth);
    // _delay_ms(eighth);
    tone_play(G4, quarter);
    // _delay_ms(quarter);
    tone_play(G4, eighth);
    // _delay_ms(eighth);
    tone_play(A4, quarter);
    // _delay_ms(quarter);
    tone_play(A4, eighth);
    // _delay_ms(eighth);
    tone_play(B4, quarter);
    // _delay_ms(quarter);
    tone_play(B4, eighth);
    // _delay_ms(eighth);
    tone_play(C5, quarter);
    // _delay_ms(quarter);
    tone_play(C5, eighth);
    // _delay_ms(eighth);
    tone_play(D5, quarter);
    // _delay_ms(quarter);
    tone_play(B4, quarter);
    // _delay_ms(quarter);
    tone_play(A4, quarter);
    // _delay_ms(quarter);
    tone_play(G4, quarter);
    // _delay_ms(quarter);
}

#endif