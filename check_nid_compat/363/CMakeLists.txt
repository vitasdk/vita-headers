cmake_minimum_required(VERSION 3.0)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(check_nid_compat_363)
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,-q -Wall -O2 -nostdlib")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -fno-exceptions")

add_executable(${PROJECT_NAME}
  ${CMAKE_SOURCE_DIR}/main.c
)

target_link_libraries(${PROJECT_NAME}
  SceDebugForDriver_stub
  SceCpuForKernel_363_stub
  SceDebugForKernel_363_stub
  SceExcpmgrForKernel_363_stub
  SceIntrmgrForKernel_363_stub
  SceModulemgrForKernel_363_stub
  SceProcessmgrForKernel_363_stub
  SceSysmemForKernel_363_stub
  SceThreadmgrForKernel_363_stub
  SceUartForKernel_363_stub
)

set_target_properties(${PROJECT_NAME}
  PROPERTIES LINK_FLAGS "-nostdlib"
  COMPILE_FLAGS "-DPSP2_SDK_VERSION=0x3630000"
)

vita_create_self(${PROJECT_NAME}.skprx ${PROJECT_NAME}
  CONFIG ${CMAKE_SOURCE_DIR}/exports.yml
  UNSAFE
)