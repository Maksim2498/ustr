add_library(ustr
            src/ustr/fmt/all.h
            src/ustr/fmt/case.h       src/ustr/fmt/case.c
            src/ustr/fmt/radix.h      src/ustr/fmt/radix.c
            src/ustr/type/fmt/all.h
            src/ustr/type/fmt/case.h
            src/ustr/type/fmt/int.h
            src/ustr/type/all.h
            src/ustr/type/char.h
            src/ustr/type/cview.h
            src/ustr/type/encoding.h
            src/ustr/type/endian.h
            src/ustr/type/str.h
            src/ustr/type/view.h
            src/ustr/util/all.h
            src/ustr/util/endian.h    src/ustr/util/endian.c
            src/ustr/util/mem.h       src/ustr/util/mem.c
            src/ustr/config.h.in
            src/ustr/all.h
            src/ustr/char.h           src/ustr/char.c
            src/ustr/cstr.h           src/ustr/cstr.c
            src/ustr/cview.h          src/ustr/cview.c
            src/ustr/encoding.h       src/ustr/encoding.c
            src/ustr/io.h             src/ustr/io.c
            src/ustr/str.h            src/ustr/str.c
            src/ustr/view.h           src/ustr/view.c)

set_target_properties(ustr PROPERTIES
                      C_STANDARD 17
                      C_STANDARD_REQUIRED YES
                      C_EXTENSIONS NO)

target_include_directories(ustr
                           PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>/src
                           PUBLIC $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
                           PUBLIC $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>/ustr)