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
    BUILD_RPATH "$ORIGIN"
)

# executable environment
include("${CMakeUtils}/link_dir_to_bin.cmake")
tx_link_dir_to_bin(TXProject "${CMAKE_SOURCE_DIR}/assets")

# release packaging
find_package(SDL3 REQUIRED)
find_package(SDL3_ttf REQUIRED)

set(RELEASE_STAGE_DIR "${CMAKE_BINARY_DIR}/release_pkg")

add_custom_target(release_zip
    COMMAND ${CMAKE_COMMAND} -E remove_directory "${RELEASE_STAGE_DIR}"
    COMMAND ${CMAKE_COMMAND} -E make_directory "${RELEASE_STAGE_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:TXProject>"
        "${RELEASE_STAGE_DIR}/TXProject"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:SDL3::SDL3>"
        "${RELEASE_STAGE_DIR}/$<TARGET_SONAME_FILE_NAME:SDL3::SDL3>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:SDL3_ttf::SDL3_ttf>"
        "${RELEASE_STAGE_DIR}/$<TARGET_SONAME_FILE_NAME:SDL3_ttf::SDL3_ttf>"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "${RELEASE_STAGE_DIR}/assets"
    COMMAND ${CMAKE_COMMAND} -E chdir "${RELEASE_STAGE_DIR}"
        ${CMAKE_COMMAND} -E tar "cf" "${CMAKE_BINARY_DIR}/UII-Demo-linux-x86_64.zip" --format=zip --
        TXProject
        "$<TARGET_SONAME_FILE_NAME:SDL3::SDL3>"
        "$<TARGET_SONAME_FILE_NAME:SDL3_ttf::SDL3_ttf>"
        assets
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    DEPENDS TXProject
    COMMENT "Creating demo release zip with bundled SDL3 libraries"
)

install(TARGETS TXProject
    RUNTIME DESTINATION bin
)