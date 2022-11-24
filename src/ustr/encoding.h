#ifndef USTR_ENCODING_H
#define USTR_ENCODING_H

#include "type/encoding.h"
#include "cview.h"

static const ucv32_t UENCODING_UTF8_NAME     = ucv32("UTF-8");
static const ucv32_t UENCODING_UTF16_LE_NAME = ucv32("UTF-16LE");
static const ucv32_t UENCODING_UTF16_BE_NAME = ucv32("UTF-16BE");
static const ucv32_t UENCODING_UTF32_LE_NAME = ucv32("UTF-32LE");
static const ucv32_t UENCODING_UTF32_BE_NAME = ucv32("UTF-32BE");

ucv32_t uencoding_name(uencoding_t encoding);

#endif