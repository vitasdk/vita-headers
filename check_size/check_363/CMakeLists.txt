cmake_minimum_required(VERSION 3.16)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(check_${TARGET_VERSION})
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,-q -Wall -O2 -fno-inline")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -fno-exceptions")

# set(VITA_ELF_CREATE_FLAGS "${VITA_ELF_CREATE_FLAGS} -vvv")
# set(VITA_MAKE_FSELF_FLAGS "${VITA_MAKE_FSELF_FLAGS} -a 0x2808000000000000")

enable_language(C ASM)

link_directories(
)

add_executable(${PROJECT_NAME}-psp2all
  ../psp2all.c
)

target_link_libraries(${PROJECT_NAME}-psp2all
  taihen_stub
)

set_target_properties(${PROJECT_NAME}-psp2all
  PROPERTIES LINK_FLAGS "-nostdlib"
  COMPILE_FLAGS "-DPSP2_SDK_VERSION=${TARGET_VERSION} -DENABLE_VITASDK_BUILD_ASSERT"
)

vita_create_self(${PROJECT_NAME}-psp2all.self ${PROJECT_NAME}-psp2all
  CONFIG ../export_user.yml
  UNSAFE
  STRIPPED
  REL_OPTIMIZE
)

add_executable(${PROJECT_NAME}-psp2
  ../psp2user.c
)

target_link_libraries(${PROJECT_NAME}-psp2
  taihen_stub
)

set_target_properties(${PROJECT_NAME}-psp2
  PROPERTIES LINK_FLAGS "-nostdlib"
  COMPILE_FLAGS "-D__PSP2_USER__ -DPSP2_SDK_VERSION=${TARGET_VERSION} -DENABLE_VITASDK_BUILD_ASSERT"
)

vita_create_self(${PROJECT_NAME}-psp2.suprx ${PROJECT_NAME}-psp2
  CONFIG ../export_user.yml
  UNSAFE
  STRIPPED
  REL_OPTIMIZE
)

add_executable(${PROJECT_NAME}-psp2kern
  ../psp2kernel.c
)

target_link_libraries(${PROJECT_NAME}-psp2kern
  taihenForKernel_stub
  SceCpuForKernel_stub
)

set_target_properties(${PROJECT_NAME}-psp2kern
  PROPERTIES LINK_FLAGS "-nostdlib"
  COMPILE_FLAGS "-D__PSP2_KERNEL__ -DPSP2_SDK_VERSION=${TARGET_VERSION} -DENABLE_VITASDK_BUILD_ASSERT"
)

vita_create_self(${PROJECT_NAME}-psp2kern.skprx ${PROJECT_NAME}-psp2kern
  CONFIG ../export_kernel.yml
  UNSAFE
  STRIPPED
  REL_OPTIMIZE
)
