cmake_minimum_required(VERSION 3.12)

project(ustr
        VERSION     0.1.0
        LANGUAGES   C
        DESCRIPTION "Small C library for unicode strings handling"
        HOMEPAGE_URL https://github.com/Maksim2498/ustr)

add_library(${PROJECT_NAME}
            src/ustr/all.h
            src/ustr/char_t.h
            src/ustr/char.h       src/ustr/char.c
            src/ustr/cview_t.h
            src/ustr/cview.h      src/ustr/cview.c
            src/ustr/encoding_t.h
            src/ustr/encoding.h   src/ustr/encoding.c
            src/ustr/io.h         src/ustr/io.c
            src/ustr/mem.h        src/ustr/mem.c
            src/ustr/str_t.h
            src/ustr/str.h        src/ustr/str.c
            src/ustr/types.h
            src/ustr/view_t.h
            src/ustr/view.h       src/ustr/view.c)

set_target_properties(${PROJECT_NAME} PROPERTIES
                      C_STANDARD 17
                      C_STANDARD_REQUIRED YES
                      C_EXTENSIONS NO)

target_include_directories(${PROJECT_NAME} PUBLIC /str/ustr)

install(TARGETS ${PROJECT_NAME} DESTINATION lib)