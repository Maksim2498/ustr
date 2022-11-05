add_library(ustr
            src/ustr/config.h.in
            src/ustr/all.h
            src/ustr/char_t.h
            src/ustr/char.h       src/ustr/char.c
            src/ustr/cview_t.h
            src/ustr/cview.h      src/ustr/cview.c
            src/ustr/encoding_t.h
            src/ustr/encoding.h   src/ustr/encoding.c
            src/ustr/endian_t.h
            src/ustr/endian.h     src/ustr/endian.c
            src/ustr/io.h         src/ustr/io.c
            src/ustr/mem.h        src/ustr/mem.c
            src/ustr/str_t.h
            src/ustr/str.h        src/ustr/str.c
            src/ustr/types.h
            src/ustr/view_t.h
            src/ustr/view.h       src/ustr/view.c)

set_target_properties(ustr PROPERTIES
                      C_STANDARD 17
                      C_STANDARD_REQUIRED YES
                      C_EXTENSIONS NO)

target_include_directories(ustr
                           PUBLIC /str/ustr
                           PUBLIC $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>)