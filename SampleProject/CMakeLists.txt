cmake_minimum_required(VERSION 4.2)

set(libs "${CMAKE_SOURCE_DIR}/libs")
set(src "${CMAKE_SOURCE_DIR}/src")

project(TXProject)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERIFY_INTERFACE_HEADER_SETS ON)

# install
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/.local" CACHE PATH "Install prefix to ~/.local" FORCE)
endif()

add_subdirectory("${CMAKE_SOURCE_DIR}/../" "${CMAKE_BINARY_DIR}/UII")
set(CMakeUtils "${TXLib_SOURCE_DIR}/cmake")

add_executable(TXProject 
	"${src}/main.cpp"
	"${src}/Project.hpp"
	"${src}/utility_dump.hpp")
target_include_directories(TXProject PRIVATE 
	"${CMAKE_SOURCE_DIR}"
	"${libs}"
	"${src}"
)

# project settings
target_compile_features(TXProject PUBLIC cxx_std_23)

# dependencies
target_link_libraries(TXProject PRIVATE 
	UII
)

# optimization
include("${CMakeUtils}/set_compile_flags.cmake")
tx_set_compile_flags(TXProject PRIVATE)

# build
set_target_properties(TXProject PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# executable environment
#include("${CMakeUtils}/link_dir_to_bin.cmake")
#tx_link_dir_to_bin(TXProject "${CMAKE_SOURCE_DIR}/assets")

install(TARGETS TXProject
    RUNTIME DESTINATION bin
)