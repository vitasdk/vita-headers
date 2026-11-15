cmake_minimum_required(VERSION 3.16)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(vita-headers-check)

set(TARGET_VERSION "0x3600011")
add_subdirectory(check_360)

set(TARGET_VERSION "0x3630011")
add_subdirectory(check_363)

add_library(check_abi_regressions OBJECT abi_regressions.cpp)
target_include_directories(check_abi_regressions PRIVATE ../include)
target_compile_definitions(check_abi_regressions PRIVATE ENABLE_VITASDK_BUILD_ASSERT)
target_compile_options(check_abi_regressions PRIVATE -fshort-enums -Werror)
set_target_properties(check_abi_regressions PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED YES
)
