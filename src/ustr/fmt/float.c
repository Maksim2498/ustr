#include "float.h"

#include "case.h"

bool uffmt_valid(const struct uffmt *fmt) {
    return fmt
        && ucv32_valid(fmt->nan)
        && ucv32_valid(fmt->inf)
        && ucase_valid(fmt->exp_case);
}