########################################
#GENERIC
########################################
cmake_minimum_required(VERSION 3.12)
project(hello-world-pass LANGUAGES CXX)

########################################
# 1. VERIFY LLVM INSTALLATION DIR
########################################
# Set this to a valid LLVM installation dir
set(EXTERNAL_LLVM_INSTALL_DIR "" CACHE PATH "LLVM installation directory")

# A bit of a sanity checking
set(EXTERNAL_LLVM_INCLUDE_DIR "${EXTERNAL_LLVM_INSTALL_DIR}/include/llvm")
if(NOT EXISTS "${EXTERNAL_LLVM_INCLUDE_DIR}")
message(FATAL_ERROR
  " EXTERNAL_LLVM_INSTALL_DIR (${EXTERNAL_LLVM_INCLUDE_DIR}) is invalid.")
endif()

set(EXTERNAL_LLVM_CMAKE_FILE "${EXTERNAL_LLVM_INSTALL_DIR}/lib/cmake/llvm/LLVMConfig.cmake")
if(NOT EXISTS "${EXTERNAL_LLVM_CMAKE_FILE}")
message(FATAL_ERROR
    " EXTERNAL_LLVM_CMAKE_FILE (${EXTERNAL_LLVM_CMAKE_FILE}) is invalid.")
endif()

########################################
#LLVM CONFIG
########################################
# Add the location of LLVMConfig.cmake to CMake search paths (so that
# find_package can locate it)
list(APPEND CMAKE_PREFIX_PATH "${EXTERNAL_LLVM_INSTALL_DIR}/lib/cmake/llvm/")

find_package(LLVM 11.0.0 REQUIRED CONFIG)

# Sanity check
if(NOT "11" VERSION_EQUAL "${LLVM_VERSION_MAJOR}")
  message(FATAL_ERROR "Found LLVM ${LLVM_VERSION_MAJOR}, but need LLVM 12")
endif()

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${EXTERNAL_LLVM_INSTALL_DIR}")

message("LLVM STATUS:
  Definitions ${LLVM_DEFINITIONS}
  Includes    ${LLVM_INCLUDE_DIRS}
  Libraries   ${LLVM_LIBRARY_DIRS}
  Targets     ${LLVM_TARGETS_TO_BUILD}"
)

# Set the LLVM header and library paths
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})
add_definitions(${LLVM_DEFINITIONS})

########################################
#PROJECT CONFIG
########################################

# Use the same C++ standard as LLVM does
set(CMAKE_CXX_STANDARD 14 CACHE STRING "")

# LLVM is normally built without RTTI. Be consistent with that.
if(NOT LLVM_ENABLE_RTTI)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
endif()

########################################
#TARGET CONFIG
########################################
add_executable(toolexe ${CMAKE_CURRENT_SOURCE_DIR}/lib/tool.cpp)
target_link_libraries(toolexe PRIVATE LLVMCore LLVMSupport)
target_include_directories(toolexe PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(lib)
