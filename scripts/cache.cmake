include(scripts/util.cmake)

set(USTR_RAISE_FACTOR 2 CACHE STRING "Sets string raise factor")
check_int(USTR_RAISE_FACTOR)

set(USTR_INIT_CAP 8 CACHE STRING "Sets initial string capacity")
check_int(USTR_INIT_CAP)