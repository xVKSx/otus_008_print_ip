cmake_minimum_required(VERSION 3.2)

project(print_ip VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

add_executable(print_ip main.cpp)

set_target_properties(print_ip PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )

#include_directories(ip_address tool)
#
#add_library(ip_address_lib
#        ip_address/ip.h
#        ip_address/ip.cpp
#        )
#
#add_library(tool_dir
#        tool/tokenize.h
#        tool/tokenize.cpp
#        )
#
#target_link_libraries(ip_filter ip_address_lib tool_dir)

install(TARGETS print_ip RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_PACKAGE_CONTACT vks.skv@yandex.ru)
set(CPACK_PACKAGE_NAME print_ip)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_VERSION_TWEAK "${PROJECT_VERSION_TWEAK}")

include(CPack)
