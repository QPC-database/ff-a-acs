#-------------------------------------------------------------------------------
# Copyright (c) 2021, Arm Limited or its affliates. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#
#-------------------------------------------------------------------------------

if(_TOOLCHAIN_CMAKE_LOADED)
  return()
endif()
set(_TOOLCHAIN_CMAKE_LOADED TRUE)

get_filename_component(_CMAKE_C_TOOLCHAIN_LOCATION "${CMAKE_C_COMPILER}" PATH)

set(CMAKE_ASM_COMPILER "${CMAKE_C_COMPILER}" CACHE FILEPATH "The Clang asm" FORCE)
set(CMAKE_AR "${CROSS_COMPILE}ar" CACHE FILEPATH "The Clang archiver" FORCE)

# Set the compiler's target architecture profile based on ARM_ARCH_MINOR option
if(${ARM_ARCH_MINOR} STREQUAL 0)
    set(TARGET_SWITCH "-march=armv${ARM_ARCH_MAJOR}-a -target aarch64-elf")
else()
    set(TARGET_SWITCH "-march=armv${ARM_ARCH_MAJOR}.${ARM_ARCH_MINOR}-a -target aarch64-elf ")
endif()

if(${ENABLE_PIE})
    set(COMPILE_PIE_SWITCH "-fpie")
    add_definitions(-DENABLE_PIE)
else()
    set(COMPILE_PIE_SWITCH "")
endif()

set(CMAKE_C_FLAGS          "${TARGET_SWITCH}  ${COMPILE_PIE_SWITCH} ${COMPILE_DEBUG_OPTIONS} -ffunction-sections -fdata-sections -mstrict-align -Os -ffreestanding -Wall -Werror -std=gnu99 -mgeneral-regs-only -Wmissing-prototypes -Wmissing-declarations -Wstrict-prototypes -Wextra -Wconversion -Wsign-conversion -Wcast-align -Wstrict-overflow ")
set(CMAKE_ASM_FLAGS        "${TARGET_SWITCH} ${COMPILE_DEBUG_OPTIONS} -c -x assembler-with-cpp -Wall -Werror -ffunction-sections -fdata-sections -Wmissing-prototypes -Wmissing-declarations -Wstrict-prototypes -Wextra -Wconversion -Wsign-conversion -Wcast-align -Wstrict-overflow")
