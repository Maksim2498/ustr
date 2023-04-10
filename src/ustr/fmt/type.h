#ifndef USTR_FMT_TYPE_H
#define USTR_FMT_TYPE_H

#include <stdbool.h>

#include <ustr/type/fmt/type.h>
#include <ustr/type/cview.h>

// Type group

// - Name

ucv32_t utgroup_name_32(utgroup_t group);
ucv16_t utgroup_name_16(utgroup_t group);
ucv8_t utgroup_name_8(utgroup_t group);

// - Valid

bool utgroup_valid(utgroup_t group);

// Type

// - Name

ucv32_t utype_name_32(utype_t type);
ucv16_t utype_name_16(utype_t type);
ucv8_t utype_name_8(utype_t type);

// - Group

utgroup_t utype_group(utype_t type);

// - Valid

bool utype_valid(utype_t type);

#endif