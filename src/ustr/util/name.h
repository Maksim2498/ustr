#ifndef USTR_UTIL_NAME_H
#define USTR_UTIL_NAME_H

#include <ustr/type/cview.h>

#include "export.h"

#define UNAME(var_prefix, name)                              \
    static const ucv32_t var_prefix##_NAME_32 = ucv32(name); \
    static const ucv16_t var_prefix##_NAME_16 = ucv16(name); \
    static const ucv8_t  var_prefix##_NAME_8  =  ucv8(name);

#define UEXPORT_NAME(var_prefix, name)                               \
    UEXPORT static const ucv32_t var_prefix##_NAME_32 = ucv32(name); \
    UEXPORT static const ucv16_t var_prefix##_NAME_16 = ucv16(name); \
    UEXPORT static const ucv8_t  var_prefix##_NAME_8  =  ucv8(name);

#endif