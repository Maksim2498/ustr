function(check_int var)
    set(var ${val})

    if (NOT ${var} MATCHES "^\\s*[0-9]+\\s*$")
        message(FATAL_ERROR "\"${val}\" must be an integer")
    endif()
endfunction()