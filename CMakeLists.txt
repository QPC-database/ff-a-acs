#-------------------------------------------------------------------------------
# Copyright (c) 2021, Arm Limited or its affliates. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#
#-------------------------------------------------------------------------------

project(ff_a_acs LANGUAGES)

### Tool dependency check - start ###

# Set the minimum required version of CMake for the project
cmake_minimum_required(VERSION 3.10)

# cmake_policy
cmake_policy(SET CMP0057 NEW)

### Tool dependency check - end ###

get_filename_component(ROOT_DIR . ABSOLUTE)

# Set internal build directory variable
set(BUILD ${CMAKE_CURRENT_BINARY_DIR} CACHE INTERNAL "Setting build directory to ${BUILD}" FORCE)
file(MAKE_DIRECTORY ${BUILD}/output/)

#### Include cmake support module ###
include(${ROOT_DIR}/tools/cmake/toolchain/utils.cmake)
include(${ROOT_DIR}/tools/cmake/toolchain/default.cmake)
####


### Valid value range for command line argument ###

list(APPEND VERBOSE_LIST 1 2 3 4 5)
list(APPEND PLATFORM_SPMC_EL_LIST 1 2 3)
list(APPEND PLATFORM_SP_EL_LIST 0 1)
list(APPEND PLATFORM_NS_HYPERVISOR_PRESENT_LIST 0 1)
list(APPEND ENABLE_PIE_LIST ON OFF)
list(APPEND CMAKE_BUILD_TYPE_LIST Release Debug)
list(APPEND ARM_ARCH_MAJOR_LIST 8 9)

###

### Command line argument check ###

if(CMAKE_BUILD_TYPE)
    if(NOT ${CMAKE_BUILD_TYPE} IN_LIST CMAKE_BUILD_TYPE_LIST)
        message(FATAL_ERROR "[ACS] : Error: Unspported value for -DCMAKE_BUILD_TYPE=, supported values are : ${CMAKE_BUILD_TYPE_LIST}")
    endif()
    set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE INTERNAL "CMAKE_BUILD_TYPE is set to ${CMAKE_BUILD_TYPE}" FORCE)
else()
    set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE_DFLT} CACHE INTERNAL "Defaulting CMAKE_BUILD_TYPE to ${CMAKE_BUILD_TYPE_DFLT}" FORCE)
endif()

# Check for valid targets
_get_sub_dir_list(TARGET_LIST ${ROOT_DIR}/platform/pal_baremetal/)
if(NOT DEFINED TARGET)
    set(TARGET ${TARGET_DFLT} CACHE INTERNAL "Defaulting target to ${TARGET}" FORCE)
else()
    set(TARGET ${TARGET} CACHE INTERNAL "TARGET is set to ${TARGET}" FORCE)
endif()

if(NOT ${TARGET} IN_LIST TARGET_LIST)
    message(FATAL_ERROR "[ACS] : Error: Unspported value for -DTARGET=, supported targets are : ${TARGET_LIST}")
else()
    message(STATUS "[ACS] : TARGET is set to ${TARGET}")
endif()

# Check for valid suites
_get_sub_dir_list(SUITE_LIST ${ROOT_DIR}/test/)
if(NOT DEFINED SUITE)
    set(SUITE ${SUITE_DFLT} CACHE INTERNAL "Defaulting suite to ${SUITE}" FORCE)
else()
    set(SUITE ${SUITE} CACHE INTERNAL "SUITE is set to ${SUITE}" FORCE)
endif()

list(APPEND SUITE_LIST all)
if(NOT ${SUITE} IN_LIST SUITE_LIST)
    message(FATAL_ERROR "[ACS] : Error: Unspported value for -DSUITE=, supported values are : ${SUITE_LIST}")
else()
    message(STATUS "[ACS] : SUITE is set to ${SUITE}")
endif()

# Check for VERBOSE
if(NOT DEFINED VERBOSE)
    set(VERBOSE ${VERBOSE_DFLT} CACHE INTERNAL "Default VERBOSE value" FORCE)
        message(STATUS "[ACS] : Defaulting VERBOSE to ${VERBOSE}")
else()
    if(NOT ${VERBOSE} IN_LIST VERBOSE_LIST)
        message(FATAL_ERROR "[ACS] : Error: Unspported value for -DVERBOSE=, supported values are : ${VERBOSE_LIST}")
    endif()
    message(STATUS "[ACS] : VERBOSE is set to ${VERBOSE}")
endif()

# Check for PLATFORM_SPMC_EL
if(NOT DEFINED PLATFORM_SPMC_EL)
    set(PLATFORM_SPMC_EL ${PLATFORM_SPMC_EL_DFLT} CACHE INTERNAL "Default PLATFORM_SPMC_EL value" FORCE)
        message(STATUS "[ACS] : Defaulting PLATFORM_SPMC_EL to ${PLATFORM_SPMC_EL}")
else()
    if(NOT ${PLATFORM_SPMC_EL} IN_LIST PLATFORM_SPMC_EL_LIST)
        message(FATAL_ERROR "[ACS] : Error: Unspported value for -DPLATFORM_SPMC_EL=, supported values are : ${PLATFORM_SPMC_EL_LIST}")
    endif()
    message(STATUS "[ACS] : PLATFORM_SPMC_EL is set to ${PLATFORM_SPMC_EL}")
endif()

# Check for PLATFORM_SP_EL
if(NOT DEFINED PLATFORM_SP_EL)
    set(PLATFORM_SP_EL ${PLATFORM_SP_EL_DFLT} CACHE INTERNAL "Default PLATFORM_SP_EL value" FORCE)
        message(STATUS "[ACS] : Defaulting PLATFORM_SP_EL to ${PLATFORM_SP_EL}")
else()
    if(NOT ${PLATFORM_SP_EL} IN_LIST PLATFORM_SP_EL_LIST)
        message(FATAL_ERROR "[ACS] : Error: Unspported value for -DPLATFORM_SP_EL=, supported values are : ${PLATFORM_SP_EL_LIST}")
    endif()
    message(STATUS "[ACS] : PLATFORM_SP_EL is set to ${PLATFORM_SP_EL}")
endif()

# Check for PLATFORM_NS_HYPERVISOR_PRESENT
if(NOT DEFINED PLATFORM_NS_HYPERVISOR_PRESENT)
    set(PLATFORM_NS_HYPERVISOR_PRESENT ${PLATFORM_NS_HYPERVISOR_PRESENT_DFLT} CACHE INTERNAL "Default PLATFORM_NS_HYPERVISOR_PRESENT value" FORCE)
        message(STATUS "[ACS] : Defaulting PLATFORM_NS_HYPERVISOR_PRESENT to ${PLATFORM_NS_HYPERVISOR_PRESENT}")
else()
    if(NOT ${PLATFORM_NS_HYPERVISOR_PRESENT} IN_LIST PLATFORM_NS_HYPERVISOR_PRESENT_LIST)
        message(FATAL_ERROR "[ACS] : Error: Unspported value for -DPLATFORM_NS_HYPERVISOR_PRESENT=, supported values are : ${PLATFORM_NS_HYPERVISOR_PRESENT_LIST}")
    endif()
    message(STATUS "[ACS] : PLATFORM_NS_HYPERVISOR_PRESENT is set to ${PLATFORM_NS_HYPERVISOR_PRESENT}")
endif()

# Check for ARM_ARCH_MAJOR
if(NOT DEFINED ARM_ARCH_MAJOR)
    set(ARM_ARCH_MAJOR "${ARM_ARCH_MAJOR_DFLT}" CACHE INTERNAL "Default ARM_ARCH_MAJOR value" FORCE)
        message(STATUS "[ACS] : Defaulting ARM_ARCH_MAJOR to ${ARM_ARCH_MAJOR}")
else()
    if(NOT ${ARM_ARCH_MAJOR} IN_LIST ARM_ARCH_MAJOR_LIST)
        message(FATAL_ERROR "[ACS] : Error: Unspported value for -DARM_ARCH_MAJOR=, supported values are : ${ARM_ARCH_MAJOR_LIST}")
    endif()
    message(STATUS "[ACS] : ARM_ARCH_MAJOR is set to ${ARM_ARCH_MAJOR}")
endif()

# Check for ARM_ARCH_MINOR
if(NOT DEFINED ARM_ARCH_MINOR)
    set(ARM_ARCH_MINOR "${ARM_ARCH_MINOR_DFLT}" CACHE INTERNAL "Default ARM_ARCH_MINOR value" FORCE)
        message(STATUS "[ACS] : Defaulting ARM_ARCH_MINOR to ${ARM_ARCH_MINOR}")
else()
    message(STATUS "[ACS] : ARM_ARCH_MINOR is set to ${ARM_ARCH_MINOR}")
endif()

# Check for ENABLE_PIE
if(NOT DEFINED ENABLE_PIE)
    set(ENABLE_PIE ${ENABLE_PIE_DFLT} CACHE INTERNAL "Default ENABLE_PIE value" FORCE)
        message(STATUS "[ACS] : Defaulting ENABLE_PIE to ${ENABLE_PIE}")
else()
    if(NOT ${ENABLE_PIE} IN_LIST ENABLE_PIE_LIST)
        message(FATAL_ERROR "[ACS] : Error: Unspported value for -DENABLE_PIE=, supported values are : ${ENABLE_PIE_LIST}")
    endif()
    message(STATUS "[ACS] : ENABLE_PIE is set to ${ENABLE_PIE}")
endif()

# Setup toolchain paramters for compilation and link
include(${ROOT_DIR}/tools/cmake/toolchain/common.cmake)

###

### Add compilation macros ###

# Global macro to identify the ACS test suite cmake build
add_definitions(-DCMAKE_BUILD)
add_definitions(-DVERBOSITY=${VERBOSE})
add_definitions(-DPLATFORM_SPMC_EL=${PLATFORM_SPMC_EL})
add_definitions(-DPLATFORM_SP_EL=${PLATFORM_SP_EL})
add_definitions(-DPLATFORM_NS_HYPERVISOR_PRESENT=${PLATFORM_NS_HYPERVISOR_PRESENT})
add_definitions(-DSUITE=${SUITE})
####

### Cmake clean target ###
list(APPEND CLEAN_LIST
        ${CMAKE_CURRENT_BINARY_DIR}/${OUTPUT_HEADER}
        ${CMAKE_CURRENT_BINARY_DIR}/output
)

# Include the files for make clean
foreach(clean_item ${CLEAN_LIST})
        set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES ${clean_item})
endforeach()
###

add_subdirectory(${ROOT_DIR}/tools/cmake/endpoints/sp1)
add_subdirectory(${ROOT_DIR}/tools/cmake/endpoints/sp2)
add_subdirectory(${ROOT_DIR}/tools/cmake/endpoints/sp3)
add_subdirectory(${ROOT_DIR}/tools/cmake/endpoints/vm1)
if(${PLATFORM_NS_HYPERVISOR_PRESENT} STREQUAL 1)
add_subdirectory(${ROOT_DIR}/tools/cmake/endpoints/vm2)
add_subdirectory(${ROOT_DIR}/tools/cmake/endpoints/vm3)
endif()
