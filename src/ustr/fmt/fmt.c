#include "fmt.h"

#include <assert.h>

#include <ustr/cstr.h>
#include <ustr/cview.h>
#include <ustr/str.h>
#include <ustr/view.h>

#include "type.h"

struct ufmt ufmt_from_ucv32(ucv32_t view) {
    return ufmt_from_uz32_n(UCV32_CEXPAND(view));
}

struct ufmt ufmt_from_us32(const us32_t *str) {
    return ufmt_from_uz32_n(US32_CEXPAND(str));
}

struct ufmt ufmt_from_uv32(uv32_t view) {
    return ufmt_from_uz32_n(UV32_CEXPAND(view));
}

struct ufmt ufmt_from_uz32(const uc32_t *cstr) {
    return ufmt_from_uz32_n(cstr, uz32_len(cstr));
}

struct ufmt ufmt_from_uz32_n(const uc32_t *cstr, size_t n) {
    // TODO
    return (struct ufmt) {};
}

struct ufmt ufmt_from_uz16(const uc16_t *cstr) {
    return ufmt_from_uz16_n(cstr, uz16_len(cstr));
}

struct ufmt ufmt_from_uz16_n(const uc16_t *cstr, size_t n) {
    // TODO
    return (struct ufmt) {};
}

struct ufmt ufmt_from_uz8(const uc8_t *cstr) {
    return ufmt_from_uz8_n(cstr, uz8_len(cstr));
}

struct ufmt ufmt_from_uz8_n(const uc8_t *cstr, size_t n) {
    // TODO
    return (struct ufmt) {};
}

bool ufmt_valid(const struct ufmt *fmt) {
    return fmt 
        && utype_valid(fmt->type);
}