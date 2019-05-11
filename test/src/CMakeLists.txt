cmake_minimum_required(VERSION 3.2)

project(print_ip_test)

add_executable(test_print_ip test_print_ip.cpp)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

set_target_properties(test_print_ip PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wall;-Wextra"
        )

set_target_properties(test_print_ip PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
        )

target_link_libraries(test_print_ip ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(${PROJECT_NAME}_executable test_print_ip)
