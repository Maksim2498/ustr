#ifndef USTR_CHAR_H
#define USTR_CHAR_H

#include <stdbool.h>

#include "char_t.h"

enum {
    URADIX_MAX = 36
};

#define uc32(literal) U##literal
#define uc16(literal) u##literal
#define uc8(literal)  u8##literal

// Convert

// - To uc32_t

uc32_t uc32_from_uc16(const uc16_t *chars);
uc32_t uc32_from_uc16be(const uc16_t *chars);
uc32_t uc32_from_uc16le(const uc16_t *chars);
uc32_t uc32_from_uc8(const uc8_t *chars);
uc32_t uc32le_from_uc16(const uc16_t *chars);
uc32_t uc32le_from_uc16le(const uc16_t *chars);
uc32_t uc32le_from_uc16be(const uc16_t *chars);
uc32_t uc32le_from_uc8(const uc8_t *chars);
uc32_t uc32be_from_uc16(const uc16_t *chars);
uc32_t uc32be_from_uc16le(const uc16_t *chars);
uc32_t uc32be_from_uc16be(const uc16_t *chars);
uc32_t uc32be_from_uc8(const uc8_t *chars);

// - To uc16_t

void uc16_from_uc32(uc32_t from, uc16_t *to);
void uc16_from_uc32le(uc32_t from, uc16_t *to);
void uc16_from_uc32be(uc32_t from, uc16_t *to);
void uc16_from_uc8(const uc8_t *from, uc16_t *to);
void uc16le_from_uc32(uc32_t from, uc16_t *to);
void uc16le_from_uc32le(uc32_t from, uc16_t *to);
void uc16le_from_uc32be(uc32_t from, uc16_t *to);
void uc16le_from_uc8(const uc8_t *from, uc16_t *to);
void uc16be_from_uc32(uc32_t from, uc16_t *to);
void uc16be_from_uc32le(uc32_t from, uc16_t *to);
void uc16be_from_uc32be(uc32_t from, uc16_t *to);
void uc16be_from_uc8(const uc8_t *from, uc16_t *to);

// - To uc8_t

void uc8_from_uc32(uc32_t from, uc8_t *to);
void uc8_from_uc32le(uc32_t from, uc8_t *to);
void uc8_from_uc32be(uc32_t from, uc8_t *to);
void uc8_from_uc16(const uc16_t *from, uc8_t *to);
void uc8_from_uc16le(const uc16_t *from, uc8_t *to);
void uc8_from_uc16be(const uc16_t *from, uc8_t *to);

// Digit vals

int uc32_dec_val(uc32_t c);
int uc32_hex_val(uc32_t c);
int uc32_oct_val(uc32_t c);
int uc32_bin_val(uc32_t c);
int uc32_rad_val(uc32_t c, unsigned radix);

// Digit

bool uc32_dec(uc32_t c);
bool uc32_hex(uc32_t c);
bool uc32_oct(uc32_t c);
bool uc32_bin(uc32_t c);
bool uc32_rad(uc32_t c, unsigned radix);

// Case chage

uc32_t uc32_to_upper(uc32_t c);
uc32_t uc32_to_lower(uc32_t c);

// Letter categories

bool uc32_letter(uc32_t c);
bool uc32_upper(uc32_t c);
bool uc32_lower(uc32_t c);
bool uc32_title(uc32_t c);
bool uc32_mod(uc32_t c);
bool uc32_oletter(uc32_t c);

// Other

bool uc32_number(uc32_t c);
bool uc32_cntrl(uc32_t c);
bool uc32_space(uc32_t c);
bool uc32_punct(uc32_t c);
bool uc32_priv(uc32_t c);

#endif