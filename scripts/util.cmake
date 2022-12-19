include(CheckTypeSize)

check_type_size(int INT_SIZE)


function(set_arg_type type var)
    check_type_size("${type}" type_size)

    if(type_size LESS INT_SIZE)
        string(REGEX MATCHALL "u.*" unsigned ${type})

        if(unsigned)
            set(${var} unsigned PARENT_SCOPE)
        else()
            set(${var} int PARENT_SCOPE)
        endif()
    else()
        set(${var} ${type} PARENT_SCOPE)
    endif()

    unset(type_size CACHE)
    unset(HAVE_type_size CACHE)
endfunction()

function(check_pos_int val)
    check_int(${val})

    if (val LESS_EQUAL 0)
        message(FATAL_ERROR "\"${val}\" must be positive")
    endif()
endfunction()

function(check_int val)
    if (NOT val MATCHES "^\\s*[0-9]+\\s*$")
        message(FATAL_ERROR "\"${val}\" must be an integer")
    endif()
endfunction()