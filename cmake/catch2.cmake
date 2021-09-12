include_guard()

option(CATCH2_COLOUR_OUTPUT "Use coloured output when running tests with ctest." ON)

function(add_catch2_test target)
    if (CATCH2_COLOUR_OUTPUT)
        set(colour "--use-colour=yes")
    endif()
    add_test(NAME ${target} COMMAND ${target} ${colour})
endfunction()
