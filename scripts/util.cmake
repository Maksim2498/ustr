function(check_pos_int var)
    check_int(${var})

    set(val ${var})

    if (${val} LESS_EQUAL 0)
        message(FATAL_ERROR "\"${val}\" must be positive")
    endif()
endfunction()

function(check_int var)
    set(val ${var})

    if (NOT ${val} MATCHES "^\\s*[0-9]+\\s*$")
        message(FATAL_ERROR "\"${val}\" must be an integer")
    endif()
endfunction()