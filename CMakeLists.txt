cmake_minimum_required(VERSION 3.22)

project(CustomerModernized
    VERSION 1.0.0
    LANGUAGES CXX
)

option(CUSTOMER_BUILD_TESTS "Build unit and integration tests" ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(CompilerWarnings)

# Library
add_library(customer_lib)
add_library(customer::lib ALIAS customer_lib)

target_sources(customer_lib
    PRIVATE
        src/customer_archive.cpp
        src/customer_formatter.cpp
        src/in_memory_store.cpp
)

target_include_directories(customer_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(customer_lib PUBLIC cxx_std_20)

customer_apply_strict_warnings(customer_lib)

# Console application
add_executable(customer_console
    apps/customer_console/main.cpp
)

target_link_libraries(customer_console PRIVATE customer::lib)
customer_apply_strict_warnings(customer_console)

# Tests
if(CUSTOMER_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
