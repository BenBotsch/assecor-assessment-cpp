include(CompilerWarnings)

include(${CMAKE_CURRENT_LIST_DIR}/../cmake/Dependencies.cmake)

customer_add_googletest()

# Determine the correct gtest_main target name.
if(TARGET GTest::gtest_main)
    set(CUSTOMER_GTEST_MAIN_TARGET GTest::gtest_main)
elseif(TARGET gtest_main)
    set(CUSTOMER_GTEST_MAIN_TARGET gtest_main)
else()
    message(FATAL_ERROR "gtest_main target not found")
endif()

add_executable(customer_unit_tests
    unit/test_customer_archive.cpp
    unit/test_customer_formatter.cpp
)

target_link_libraries(customer_unit_tests
    PRIVATE
        customer::lib
        ${CUSTOMER_GTEST_MAIN_TARGET}
)

target_compile_features(customer_unit_tests PRIVATE cxx_std_20)
customer_apply_strict_warnings(customer_unit_tests)


add_test(NAME customer_unit_tests COMMAND customer_unit_tests)

add_executable(customer_integration_tests
    integration/test_end_to_end.cpp
)

target_link_libraries(customer_integration_tests
    PRIVATE
        customer::lib
        ${CUSTOMER_GTEST_MAIN_TARGET}
)

target_compile_features(customer_integration_tests PRIVATE cxx_std_20)
customer_apply_strict_warnings(customer_integration_tests)


add_test(NAME customer_integration_tests COMMAND customer_integration_tests)
