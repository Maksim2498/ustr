install(CODE "message(\"Installing ustr library\")")

install(TARGETS   ustr                         DESTINATION lib          COMPONENT Runtime     EXPORT  ustr-targets)
install(EXPORT    ustr-targets                 DESTINATION lib)
install(DIRECTORY src/ustr                     DESTINATION include      COMPONENT Development PATTERN *.c EXCLUDE)
install(FILES     ${CMAKE_BINARY_DIR}/config.h DESTINATION include/ustr COMPONENT Development)

install(CODE "message(\"Done installing ustr library\")")