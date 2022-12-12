#include "encoding.h"

#include <assert.h>

ucv32_t uencoding_name(uencoding_t encoding) {
    assert(uencoding_valid(encoding));
    
    switch (encoding) {
        case UENCODING_UTF8:
			return UENCODING_UTF8_NAME;

        case UENCODING_UTF16_LE:
			return UENCODING_UTF16_LE_NAME;

        case UENCODING_UTF16_BE:
			return UENCODING_UTF16_BE_NAME;

        case UENCODING_UTF32_LE:
			return UENCODING_UTF32_LE_NAME;
            
        case UENCODING_UTF32_BE:
			return UENCODING_UTF32_BE_NAME;

        default:
            return ucv32("unknown encoding");
    }
}

bool uencoding_valid(uencoding_t encoding) {
    return encoding <= UENCODING_COUNT;
}