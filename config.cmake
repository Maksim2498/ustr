include(TestBigEndian)

test_big_endian(USTR_BIG_ENDIAN)

configure_file(
    ${PROJECT_SOURCE_DIR}/src/ustr/config.h.in
    ${PROJECT_BINARY_DIR}/config.h
)