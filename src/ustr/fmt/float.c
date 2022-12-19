#include "float.h"

#include <assert.h>

#include "case.h"
#include "fmt.h"

struct uffmt uffmt_from_ufmt(const struct ufmt *fmt, va_list *args) {
    assert(ufmt_valid(fmt) && args);

    struct uffmt res = UFFMT;

    res.scientific = fmt->f.scientific;
    res.exp_case   = fmt->f.exp_case;
    res.show_plus  = fmt->f.show_plus;

    if (fmt->use_precision)
        res.precision = fmt->arg_precision ? va_arg(*args, size_t) : fmt->precision;

    return res;
}

bool uffmt_valid(const struct uffmt *fmt) {
    return fmt
        && ucv32_valid(fmt->nan)
        && ucv32_valid(fmt->inf)
        && ucase_valid(fmt->exp_case);
}