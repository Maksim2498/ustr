#ifndef USTR_CHAR_H
#define USTR_CHAR_H

#include <stdbool.h>

#include "type/fmt/case.h"
#include "type/fmt/radix.h"
#include "type/attr.h"
#include "type/char.h"

// Creation

// - Literal

#define uc32(literal) U##literal
#define uc16(literal) u##literal
#define uc8(literal)  u8##literal

// - Convertion

uc32_t uc32_from_uc32(uc32_t from);
uc32_t uc32_from_uc16(const uc16_t *from);
uc32_t uc32_from_uc8(const uc8_t *from);

unsigned uc16_from_uc32(UNULLABLE uc16_t *to, uc32_t from);
unsigned uc16_from_uc16(UNULLABLE uc16_t *to, const uc16_t *from);
unsigned uc16_from_uc8(UNULLABLE uc16_t *to, const uc8_t *from);

unsigned uc8_from_uc32(UNULLABLE uc8_t *to, uc32_t from);
unsigned uc8_from_uc16(UNULLABLE uc8_t *to, const uc16_t *from);
unsigned uc8_from_uc8(UNULLABLE uc8_t *to, const uc8_t *from);

// - Digit from val

uc32_t uc32_bin_from_val(unsigned val);
uc32_t uc32_oct_from_val(unsigned val);
uc32_t uc32_dec_from_val(unsigned val);
uc32_t uc32_hex_from_val(unsigned val);
uc32_t uc32_case_hex_from_val(ucase_t ca, unsigned val);
uc32_t uc32_lower_hex_from_val(unsigned val);
uc32_t uc32_upper_hex_from_val(unsigned val);
uc32_t uc32_radix_from_val(uradix_t radix, unsigned val);
uc32_t uc32_case_radix_from_val(ucase_t ca, uradix_t radix, unsigned val);
uc32_t uc32_lower_radix_from_val(uradix_t radix, unsigned val);
uc32_t uc32_upper_radix_from_val(uradix_t radix, unsigned val);

uc16_t uc16_bin_from_val(unsigned val);
uc16_t uc16_oct_from_val(unsigned val);
uc16_t uc16_dec_from_val(unsigned val);
uc16_t uc16_hex_from_val(unsigned val);
uc16_t uc16_case_hex_from_val(ucase_t ca, unsigned val);
uc16_t uc16_lower_hex_from_val(unsigned val);
uc16_t uc16_upper_hex_from_val(unsigned val);
uc16_t uc16_radix_from_val(uradix_t radix, unsigned val);
uc16_t uc16_case_radix_from_val(ucase_t ca, uradix_t radix, unsigned val);
uc16_t uc16_lower_radix_from_val(uradix_t radix, unsigned val);
uc16_t uc16_upper_radix_from_val(uradix_t radix, unsigned val);

uc8_t uc8_bin_from_val(unsigned val);
uc8_t uc8_oct_from_val(unsigned val);
uc8_t uc8_dec_from_val(unsigned val);
uc8_t uc8_hex_from_val(unsigned val);
uc8_t uc8_case_hex_from_val(ucase_t ca, unsigned val);
uc8_t uc8_lower_hex_from_val(unsigned val);
uc8_t uc8_upper_hex_from_val(unsigned val);
uc8_t uc8_radix_from_val(uradix_t radix, unsigned val);
uc8_t uc8_case_radix_from_val(ucase_t ca, uradix_t radix, unsigned val);
uc8_t uc8_lower_radix_from_val(uradix_t radix, unsigned val);
uc8_t uc8_upper_radix_from_val(uradix_t radix, unsigned val);

// Digit val

int uc32_bin_val(uc32_t c);
int uc32_oct_val(uc32_t c);
int uc32_dec_val(uc32_t c);
int uc32_hex_val(uc32_t c);
int uc32_case_hex_val(uc32_t c, ucase_t ca);
int uc32_lower_hex_val(uc32_t c);
int uc32_upper_hex_val(uc32_t c);
int uc32_radix_val(uc32_t c, uradix_t radix);
int uc32_case_radix_val(uc32_t c, ucase_t ca, uradix_t radix);
int uc32_lower_radix_val(uc32_t c, uradix_t radix);
int uc32_upper_radix_val(uc32_t c, uradix_t radix);

int uc16_bin_val(uc16_t c);
int uc16_oct_val(uc16_t c);
int uc16_dec_val(uc16_t c);
int uc16_hex_val(uc16_t c);
int uc16_case_hex_val(uc16_t c, ucase_t ca);
int uc16_lower_hex_val(uc16_t c);
int uc16_upper_hex_val(uc16_t c);
int uc16_radix_val(uc16_t c, uradix_t radix);
int uc16_case_radix_val(uc16_t c, ucase_t ca, uradix_t radix);
int uc16_lower_radix_val(uc16_t c, uradix_t radix);
int uc16_upper_radix_val(uc16_t c, uradix_t radix);

int uc8_bin_val(uc8_t c);
int uc8_oct_val(uc8_t c);
int uc8_dec_val(uc8_t c);
int uc8_hex_val(uc8_t c);
int uc8_case_hex_val(uc8_t c, ucase_t ca);
int uc8_lower_hex_val(uc8_t c);
int uc8_upper_hex_val(uc8_t c);
int uc8_radix_val(uc8_t c, uradix_t radix);
int uc8_case_radix_val(uc8_t c, ucase_t ca, uradix_t radix);
int uc8_lower_radix_val(uc8_t c, uradix_t radix);
int uc8_upper_radix_val(uc8_t c, uradix_t radix);

// Digit categories

bool uc32_bin(uc32_t c);
bool uc32_oct(uc32_t c);
bool uc32_dec(uc32_t c);
bool uc32_hex(uc32_t c);
bool uc32_case_hex(uc32_t c, ucase_t ca);
bool uc32_lower_hex(uc32_t c);
bool uc32_upper_hex(uc32_t c);
bool uc32_radix(uc32_t c, uradix_t radix);
bool uc32_case_radix(uc32_t c, ucase_t ca, uradix_t radix);
bool uc32_lower_radix(uc32_t c, uradix_t radix);
bool uc32_upper_radix(uc32_t c, uradix_t radix);

bool uc16_bin(uc16_t c);
bool uc16_oct(uc16_t c);
bool uc16_dec(uc16_t c);
bool uc16_hex(uc16_t c);
bool uc16_case_hex(uc16_t c, ucase_t ca);
bool uc16_lower_hex(uc16_t c);
bool uc16_upper_hex(uc16_t c);
bool uc16_radix(uc16_t c, uradix_t radix);
bool uc16_case_radix(uc16_t c, ucase_t ca, uradix_t radix);
bool uc16_lower_radix(uc16_t c, uradix_t radix);
bool uc16_upper_radix(uc16_t c, uradix_t radix);

bool uc8_bin(uc8_t c);
bool uc8_oct(uc8_t c);
bool uc8_dec(uc8_t c);
bool uc8_hex(uc8_t c);
bool uc8_case_hex(uc8_t c, ucase_t ca);
bool uc8_lower_hex(uc8_t c);
bool uc8_upper_hex(uc8_t c);
bool uc8_radix(uc8_t c, uradix_t radix);
bool uc8_case_radix(uc8_t c, ucase_t ca, uradix_t radix);
bool uc8_lower_radix(uc8_t c, uradix_t radix);
bool uc8_upper_radix(uc8_t c, uradix_t radix);

// Case change

uc32_to_case_func_t uc32_to_case_func_from_ucase(ucase_t ca);
uc32_t uc32_to_case(uc32_t c, ucase_t ca);
uc32_t uc32_to_lower(uc32_t c);
uc32_t uc32_to_upper(uc32_t c);

uc16_to_case_func_t uc16_to_case_func_from_ucase(ucase_t ca);
unsigned uc16_to_case(UNULLABLE uc16_t *to, const uc16_t *from, ucase_t ca);
unsigned uc16_to_lower(UNULLABLE uc16_t *to, const uc16_t *from);
unsigned uc16_to_upper(UNULLABLE uc16_t *to, const uc16_t *from);

uc8_to_case_func_t uc8_to_case_func_from_ucase(ucase_t ca);
unsigned uc8_to_case(UNULLABLE uc8_t *to, const uc8_t *from, ucase_t ca);
unsigned uc8_to_lower(UNULLABLE uc8_t *to, const uc8_t *from);
unsigned uc8_to_upper(UNULLABLE uc8_t *to, const uc8_t *from);

// Case change length

uc8_case_len_func_t uc8_case_len_func_from_ucase(ucase_t ca);
unsigned uc8_case_len(const uc8_t *c, ucase_t ca);
unsigned uc8_lower_len(const uc8_t *c);
unsigned uc8_upper_len(const uc8_t *c);

// Letter categories

bool uc32_letter(uc32_t c);
bool uc32_case(uc32_t c, ucase_t ca);
bool uc32_lower(uc32_t c);
bool uc32_upper(uc32_t c);
bool uc32_title(uc32_t c);
bool uc32_mod(uc32_t c);
bool uc32_oletter(uc32_t c);

bool uc16_letter(const uc16_t *c);
bool uc16_case(const uc16_t *c, ucase_t ca);
bool uc16_lower(const uc16_t *c);
bool uc16_upper(const uc16_t *c);
bool uc16_title(const uc16_t *c);
bool uc16_mod(const uc16_t *c);
bool uc16_oletter(const uc16_t *c);

bool uc8_letter(const uc8_t *c);
bool uc8_case(const uc8_t *c, ucase_t ca);
bool uc8_lower(const uc8_t *c);
bool uc8_upper(const uc8_t *c);
bool uc8_title(const uc8_t *c);
bool uc8_mod(const uc8_t *c);
bool uc8_oletter(const uc8_t *c);

// Other categories

bool uc32_number(uc32_t c);
bool uc32_cntrl(uc32_t c);
bool uc32_space(uc32_t c);
bool uc32_wspace(uc32_t c);
bool uc32_punct(uc32_t c);
bool uc32_priv(uc32_t c);

bool uc16_number(const uc16_t *c);
bool uc16_cntrl(const uc16_t *c);
bool uc16_space(const uc16_t *c);
bool uc16_wspace(const uc16_t *c);
bool uc16_punct(const uc16_t *c);
bool uc16_priv(const uc16_t *c);
bool uc16_srgt(uc16_t c);
bool uc16_srgt_low(uc16_t c);
bool uc16_srgt_high(uc16_t c);

bool uc8_number(const uc8_t *c);
bool uc8_cntrl(const uc8_t *c);
bool uc8_space(const uc8_t *c);
bool uc8_wspace(const uc8_t *c);
bool uc8_punct(const uc8_t *c);
bool uc8_priv(const uc8_t *c);
bool uc8_lead(uc8_t c);
bool uc8_trail(uc8_t c);

// Length

unsigned uc32_len(uc32_t c);
unsigned uc32_n_len(uc32_t c, unsigned n);
unsigned uc32_32_len(uc32_t c);
unsigned uc32_16_len(uc32_t c);
unsigned uc32_8_len(uc32_t c);

unsigned uc16_len(uc16_t c);
unsigned uc16_n_len(uc16_t c, unsigned n);
unsigned uc16_32_len(uc16_t c);
unsigned uc16_16_len(uc16_t c);
unsigned uc16_8_len(uc16_t c);

unsigned uc8_len(uc8_t c);
unsigned uc8_n_len(uc8_t c, unsigned n);
unsigned uc8_32_len(uc8_t c);
unsigned uc8_16_len(uc8_t c);
unsigned uc8_8_len(uc8_t c);

// Valid

bool uc32_valid(uc32_t c);
unsigned uc16_valid(const uc16_t *c);
unsigned uc8_valid(const uc8_t *c);

#endif