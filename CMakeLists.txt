cmake_minimum_required(VERSION 4.2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERIFY_INTERFACE_HEADER_SETS ON)

# dependencies

find_package(SDL3 QUIET)
find_package(SDL3_mixer QUIET)
find_package(SDL3_ttf QUIET)

set(libs "${CMAKE_CURRENT_SOURCE_DIR}/libs")
set(src "${CMAKE_CURRENT_SOURCE_DIR}/src")

include("${libs}/add_txlib.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/txlib-path.cmake")

# TXLib
tx_add_txlib(
	LOCAL_DIR ${TXLib_LOCAL_DIR}
    VERSION refactor/lib-structure
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
	SDL3::SDL3
    SDL3_mixer::SDL3_mixer
    SDL3_ttf::SDL3_ttf
)

# optimization
include("${CMakeUtils}/set_compile_flags.cmake")
tx_set_compile_flags(UII PUBLIC)
