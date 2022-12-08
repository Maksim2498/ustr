include(scripts/util.cmake)

set(USTR_RAISE_FACTOR 2 CACHE STRING "Sets string raise factor")
check_pos_int(USTR_RAISE_FACTOR)

set(USTR_INIT_CAP 8 CACHE STRING "Sets initial string capacity")
check_pos_int(USTR_INIT_CAP)

set(USTR_IO_BUFFER_SIZE 1024 CACHE STRING "Sets I/O buffer size")
check_pos_int(USTR_IO_BUFFER_SIZE)