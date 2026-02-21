
include(FetchContent)

set(GOOGLETEST_SOURCE_DIR "" CACHE PATH "Path to a local googletest source directory")

option(CUSTOMER_USE_SYSTEM_GTEST "Use a system-installed GTest package" OFF)

function(customer_add_googletest)
    if(CUSTOMER_USE_SYSTEM_GTEST)
        find_package(GTest REQUIRED)
        return()
    endif()

    if(GOOGLETEST_SOURCE_DIR)
        add_subdirectory(${GOOGLETEST_SOURCE_DIR} ${CMAKE_BINARY_DIR}/_deps/googletest-build)
        return()
    endif()

    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    )

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    FetchContent_MakeAvailable(googletest)
endfunction()
