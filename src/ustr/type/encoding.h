#ifndef USTR_TYPE_ENCODING_H
#define USTR_TYPE_ENCODING_H

typedef enum {
    UENCODING_UTF8,
    UENCODING_UTF16_LE,
    UENCODING_UTF16_BE,
    UENCODING_UTF32_LE,
    UENCODING_UTF32_BE,
    UENCODING_COUNT
} uencoding_t;

#endif