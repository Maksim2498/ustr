#include "bit.h"

bool upower_of_2(intmax_t val) {
    return val && !(val & (val - 1));
}