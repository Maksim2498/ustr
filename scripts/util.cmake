function(check_int var)
    set(var ${val})

    if (NOT ${var} MATCHES "$[0-9]+$")
        message(FATAL_ERROR "${val} must be an integer")
    endif()
endfunction()