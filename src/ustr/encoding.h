#ifndef USTR_ENCODING_H
#define USTR_ENCODING_H

#include <stdbool.h>

#include "type/util/endian.h"
#include "type/encoding.h"
#include "type/cview.h"
#include "util/export.h"

// Endian

UEXPORT uendian_t uencoding_endian(uencoding_t encoding);

// Name

UEXPORT ucv32_t uencoding_name_32(uencoding_t encoding);
UEXPORT ucv16_t uencoding_name_16(uencoding_t encoding);
UEXPORT ucv8_t uencoding_name_8(uencoding_t encoding);

// Valid

UEXPORT bool uencoding_valid(uencoding_t encoding);

#endif