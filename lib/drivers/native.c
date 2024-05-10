#ifndef NATIVE_TESTING
#include <util/delay.h>
#endif

void native_delay_ms(int ms)
{
    _delay_ms(ms);
}