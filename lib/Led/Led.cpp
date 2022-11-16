#include <Led.h>

/*!
    @brief Sets the pin directions and writes initial values.
*/
void Led::Init() {
    pinMode(_pin, OUTPUT);
    write(_state);
}