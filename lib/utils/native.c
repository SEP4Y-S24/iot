#include "native.h"
#ifndef NATIVE_TESTING
#include <util/delay.h>
#endif

#ifdef NATIVE_TESTING
void _delay_ms(int ms)
{
    // Do nothing
}
#endif

void native_delay_ms(int ms)
{
    _delay_ms(ms);
}