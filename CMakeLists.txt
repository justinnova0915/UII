cmake_minimum_required(VERSION 4.2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERIFY_INTERFACE_HEADER_SETS ON)

# dependencies

set(libs "${CMAKE_CURRENT_SOURCE_DIR}/libs")
set(src "${CMAKE_CURRENT_SOURCE_DIR}/src")

include("${libs}/add_txlib.cmake")

# TXLib
tx_add_txlib(
	LOCAL_DIR "$ENV{HOME}/Programming/dev/libs/TXLib"
)
set(TXLib_SOURCE_DIR ${TXLib_SOURCE_DIR} PARENT_SCOPE)
set(CMakeUtils "${TXLib_SOURCE_DIR}/cmake")

add_library(UII STATIC
	"${CMAKE_CURRENT_SOURCE_DIR}/include/uii/uii.h"

	"${CMAKE_CURRENT_SOURCE_DIR}/src/hello.cpp"
)
target_include_directories(UII PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# project settings
target_compile_features(UII PUBLIC cxx_std_23)

# dependencies
target_link_libraries(UII PUBLIC
	TXLib
)

# optimization
include("${CMakeUtils}/set_compile_flags.cmake")
tx_set_compile_flags(UII PUBLIC)