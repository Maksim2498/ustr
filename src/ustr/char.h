#ifndef USTR_CHAR_H
#define USTR_CHAR_H

#include <stdbool.h>

#include "type/fmt/case.h"
#include "type/fmt/radix.h"
#include "type/char.h"
#include "type/endian.h"

#define uc32(literal) U##literal
#define uc16(literal) u##literal
#define uc8(literal)  u8##literal

// Convert

// - To uc32_t

bool uc32_from_uc16_e(uc32_t *to, uendian_t to_endian, const uc16_t *from, uendian_t from_endian);
bool uc32_from_uc8_e(uc32_t *to, uendian_t to_endian, const uc8_t *from);
bool uc32_from_uc16(uc32_t *to, const uc16_t *from);
bool uc32_from_uc16be(uc32_t *to, const uc16_t *from);
bool uc32_from_uc16le(uc32_t *to, const uc16_t *from);
bool uc32_from_uc8(uc32_t *to, const uc8_t *from);
bool uc32le_from_uc16(uc32_t *to, const uc16_t *from);
bool uc32le_from_uc16le(uc32_t *to, const uc16_t *from);
bool uc32le_from_uc16be(uc32_t *to, const uc16_t *from);
bool uc32le_from_uc8(uc32_t *to, const uc8_t *from);
bool uc32be_from_uc16(uc32_t *to, const uc16_t *from);
bool uc32be_from_uc16le(uc32_t *to, const uc16_t *from);
bool uc32be_from_uc16be(uc32_t *to, const uc16_t *from);
bool uc32be_from_uc8(uc32_t *to, const uc8_t *from);

// - To uc16_t

int uc16_from_uc32_e(uc16_t *to, uendian_t to_endian, uc32_t from, uendian_t from_endian);
int uc16_from_uc8_e(uc16_t *to, uendian_t to_endian, const uc8_t *from);
int uc16_from_uc32(uc16_t *to, uc32_t from);
int uc16_from_uc32le(uc16_t *to, uc32_t from);
int uc16_from_uc32be(uc16_t *to, uc32_t from);
int uc16_from_uc8(uc16_t *to, const uc8_t *from);
int uc16le_from_uc32(uc16_t *to, uc32_t from);
int uc16le_from_uc32le(uc16_t *to, uc32_t from);
int uc16le_from_uc32be(uc16_t *to, uc32_t from);
int uc16le_from_uc8(uc16_t *to, const uc8_t *from);
int uc16be_from_uc32(uc16_t *to, uc32_t from);
int uc16be_from_uc32le(uc16_t *to, uc32_t from);
int uc16be_from_uc32be(uc16_t *to, uc32_t from);
int uc16be_from_uc8(uc16_t *to, const uc8_t *from);

// - To uc8_t

int uc8_from_uc32_e(uc8_t *to, uc32_t from, uendian_t from_endian);
int uc8_from_uc16_e(uc8_t *to, const uc16_t *from, uendian_t from_endian);
int uc8_from_uc32(uc8_t *to, uc32_t from);
int uc8_from_uc32le(uc8_t *to, uc32_t from);
int uc8_from_uc32be(uc8_t *to, uc32_t from);
int uc8_from_uc16(uc8_t *to, const uc16_t *from);
int uc8_from_uc16le(uc8_t *to, const uc16_t *from);
int uc8_from_uc16be(uc8_t *to, const uc16_t *from);

// uc8_t Traits

// - Digit from val

uc8_t uc8_dec_from_val(unsigned char val);
uc8_t uc8_case_hex_from_val(unsigned char val, ucase_t ca);
uc8_t uc8_upper_hex_from_val(unsigned char val);
uc8_t uc8_lower_hex_from_val(unsigned char val);
uc8_t uc8_oct_from_val(unsigned char val);
uc8_t uc8_bin_from_val(unsigned char val);
uc8_t uc8_case_radix_from_val(unsigned char val, uradix_t radix, ucase_t ca);
uc8_t uc8_upper_radix_from_val(unsigned char val, uradix_t radix);
uc8_t uc8_lower_radix_from_val(unsigned char val, uradix_t radix);

// - Digit val

int uc8_dec_val(uc8_t c);
int uc8_hex_val(uc8_t c);
int uc8_case_hex_val(uc8_t c, ucase_t ca);
int uc8_lower_hex_val(uc8_t c);
int uc8_upper_hex_val(uc8_t c);
int uc8_oct_val(uc8_t c);
int uc8_bin_val(uc8_t c);
int uc8_radix_val(uc8_t c, uradix_t radix);
int uc8_case_radix_val(uc8_t c, uradix_t radix, ucase_t ca);
int uc8_lower_radix_val(uc8_t c, uradix_t radix);
int uc8_upper_radix_val(uc8_t c, uradix_t radix);

// - Digit

bool uc8_dec(uc8_t c);
bool uc8_hex(uc8_t c);
bool uc8_case_hex(uc8_t c, ucase_t ca);
bool uc8_lower_hex(uc8_t c);
bool uc8_upper_hex(uc8_t c);
bool uc8_oct(uc8_t c);
bool uc8_bin(uc8_t c);
bool uc8_radix(uc8_t c, uradix_t radix);
bool uc8_case_radix(uc8_t c, uradix_t radix, ucase_t ca);
bool uc8_lower_radix(uc8_t c, uradix_t radix);
bool uc8_upper_radix(uc8_t c, uradix_t radix);

// - Case chage

uc8_to_case_len_func_t uc8_to_case_len_func_from_ucase(ucase_t ca);
int uc8_to_case_len(const uc8_t *c, ucase_t ca);
int uc8_to_upper_len(const uc8_t *c);
int uc8_to_lower_len(const uc8_t *c);

uc8_to_case_func_t uc8_to_case_func_from_ucase(ucase_t ca);
int uc8_to_case(uc8_t *c, ucase_t ca);
int uc8_to_upper(uc8_t *c);
int uc8_to_lower(uc8_t *c);

// - Letter categories

bool uc8_letter(const uc8_t *c);
bool uc8_upper(const uc8_t *c);
bool uc8_lower(const uc8_t *c);
bool uc8_title(const uc8_t *c);
bool uc8_mod(const uc8_t *c);
bool uc8_oletter(const uc8_t *c);

// - Other

bool uc8_number(const uc8_t *c);
bool uc8_cntrl(const uc8_t *c);
bool uc8_space(const uc8_t *c);
bool uc8_wspace(const uc8_t *c);
bool uc8_punct(const uc8_t *c);
bool uc8_priv(const uc8_t *c);
bool uc8_srgt(const uc8_t *c);
bool uc8_srgt_low(const uc8_t *c);
bool uc8_srgt_high(const uc8_t *c);

// - Order

bool uc8_lead(uc8_t c);
bool uc8_trail(uc8_t c);

// - Len

int uc8_len(uc8_t c);
int uc8_uc16_len(uc8_t c);

// - Valid

int uc8_valid(const uc8_t *c);

// uc16_t Traits

// - Digit from val

uc16_t uc16_dec_from_val(unsigned char val);
uc16_t uc16_case_hex_from_val(unsigned char val, ucase_t ca);
uc16_t uc16_upper_hex_from_val(unsigned char val);
uc16_t uc16_lower_hex_from_val(unsigned char val);
uc16_t uc16_oct_from_val(unsigned char val);
uc16_t uc16_bin_from_val(unsigned char val);
uc16_t uc16_case_radix_from_val(unsigned char val, uradix_t radix, ucase_t ca);
uc16_t uc16_upper_radix_from_val(unsigned char val, uradix_t radix);
uc16_t uc16_lower_radix_from_val(unsigned char val, uradix_t radix);

// - Digit val

int uc16_dec_val(uc16_t c);
int uc16_hex_val(uc16_t c);
int uc16_case_hex_val(uc16_t c, ucase_t ca);
int uc16_lower_hex_val(uc16_t c);
int uc16_upper_hex_val(uc16_t c);
int uc16_oct_val(uc16_t c);
int uc16_bin_val(uc16_t c);
int uc16_radix_val(uc16_t c, uradix_t radix);
int uc16_case_radix_val(uc16_t c, uradix_t radix, ucase_t ca);
int uc16_lower_radix_val(uc16_t c, uradix_t radix);
int uc16_upper_radix_val(uc16_t c, uradix_t radix);

// - Digit

bool uc16_dec(uc16_t c);
bool uc16_hex(uc16_t c);
bool uc16_case_hex(uc16_t c, ucase_t ca);
bool uc16_hex_lower(uc16_t c);
bool uc16_upper_hex(uc16_t c);
bool uc16_oct(uc16_t c);
bool uc16_bin(uc16_t c);
bool uc16_rad(uc16_t c, uradix_t radix);
bool uc16_rad_case(uc16_t c, uradix_t radix, ucase_t ca);
bool uc16_rad_lower(uc16_t c, uradix_t radix);
bool uc16_upper_radix(uc16_t c, uradix_t radix);

// - Case chage

uc16_to_case_func_t uc16_to_case_func_from_ucase(ucase_t ca);
int uc16_to_case(uc16_t *c, ucase_t ca);
int uc16_to_upper(uc16_t *c);
int uc16_to_lower(uc16_t *c);

// - Letter categories

bool uc16_letter(const uc16_t *c);
bool uc16_upper(const uc16_t *c);
bool uc16_lower(const uc16_t *c);
bool uc16_title(const uc16_t *c);
bool uc16_mod(const uc16_t *c);
bool uc16_oletter(const uc16_t *c);

// - Other

bool uc16_number(const uc16_t *c);
bool uc16_cntrl(const uc16_t *c);
bool uc16_space(const uc16_t *c);
bool uc16_wspace(const uc16_t *c);
bool uc16_punct(const uc16_t *c);
bool uc16_priv(const uc16_t *c);
bool uc16_srgt(uc16_t c);
bool uc16_srgt_low(uc16_t c);
bool uc16_srgt_high(uc16_t c);

// - Len

int uc16_len(uc16_t c);
int uc16_uc8_len(uc16_t c);

// - Valid

bool uc16_valid(const uc16_t *c);

// uc32_t Traits

// - Digit from val

uc32_t uc32_dec_from_val(unsigned char val);
uc32_t uc32_case_hex_from_val(unsigned char val, ucase_t ca);
uc32_t uc32_upper_hex_from_val(unsigned char val);
uc32_t uc32_lower_hex_from_val(unsigned char val);
uc32_t uc32_oct_from_val(unsigned char val);
uc32_t uc32_bin_from_val(unsigned char val);
uc32_t uc32_case_radix_from_val(unsigned char val, uradix_t radix, ucase_t ca);
uc32_t uc32_upper_radix_from_val(unsigned char val, uradix_t radix);
uc32_t uc32_lower_radix_from_val(unsigned char val, uradix_t radix);

// - Digit val

int uc32_dec_val(uc32_t c);
int uc32_hex_val(uc32_t c);
int uc32_case_hex_val(uc32_t c, ucase_t ca);
int uc32_lower_hex_val(uc32_t c);
int uc32_upper_hex_val(uc32_t c);
int uc32_oct_val(uc32_t c);
int uc32_bin_val(uc32_t c);
int uc32_radix_val(uc32_t c, uradix_t radix);
int uc32_case_radix_val(uc32_t c, uradix_t radix, ucase_t ca);
int uc32_lower_radix_val(uc32_t c, uradix_t radix);
int uc32_radix_upper_val(uc32_t c, uradix_t radix);

// - Digit

bool uc32_dec(uc32_t c);
bool uc32_hex(uc32_t c);
bool uc32_case_hex(uc32_t c, ucase_t ca);
bool uc32_lower_hex(uc32_t c);
bool uc32_upper_hex(uc32_t c);
bool uc32_oct(uc32_t c);
bool uc32_bin(uc32_t c);
bool uc32_radix(uc32_t c, uradix_t radix);
bool uc32_case_radix(uc32_t c, uradix_t radix, ucase_t ca);
bool uc32_lower_radix(uc32_t c, uradix_t radix);
bool uc32_upper_radix(uc32_t c, uradix_t radix);

// - Case chage

uc32_to_case_func_t uc32_to_case_func_from_ucase(ucase_t ca);
uc32_t uc32_to_case(uc32_t c, ucase_t ca);
uc32_t uc32_to_upper(uc32_t c);
uc32_t uc32_to_lower(uc32_t c);

// - Letter categories

bool uc32_letter(uc32_t c);
bool uc32_upper(uc32_t c);
bool uc32_lower(uc32_t c);
bool uc32_title(uc32_t c);
bool uc32_mod(uc32_t c);
bool uc32_oletter(uc32_t c);

// - Other

bool uc32_number(uc32_t c);
bool uc32_cntrl(uc32_t c);
bool uc32_space(uc32_t c);
bool uc32_wspace(uc32_t c);
bool uc32_punct(uc32_t c);
bool uc32_priv(uc32_t c);
bool uc32_srgt(uc32_t c);
bool uc32_srgt_low(uc32_t c);
bool uc32_srgt_high(uc32_t c);

// - Len

int uc32_uc16_len(uc32_t c);
int uc32_uc8_len(uc32_t c);

// - Valid

bool uc32_valid(uc32_t c);

#endif