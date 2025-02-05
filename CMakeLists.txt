cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
cmake_policy(SET CMP0091 NEW)

# === options ==================================================================
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)
option(USE_STATIC_RUNTIME "Link against static runtime libraries" OFF)
option(SANITIZE_ADDRESS "Enable Address sanitizer" ON)
option(SANITIZE_UNDEFINED "Enable Undefined Behavior sanitizer" OFF)
option(SANITIZE_THREAD "Enable Thread sanitizer" OFF)
option(SANITIZE_MEMORY "Enable Memory sanitizer" OFF)

# Linting C/C++ code
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ==============================================================================
# Project attributes
# ==============================================================================
set(LIBRARY_NAME DesignPatternsCppLib)
string(TOLOWER "${LIBRARY_NAME}" LIBRARY_NAME_LOWER)
set(LIBRARY_NAMESPACE dsdotname)
project(
    ${LIBRARY_NAME}
    VERSION 0.0.1
    LANGUAGES C CXX
    DESCRIPTION "template Copyright (c) 2024 TomasMark [at] digitalspace.name"
    HOMEPAGE_URL "https://github.com/tomasmark79")

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "In-source builds not allowed.
        Please make a new directory (called a Build directory) and run CMake from there.")
endif()

# ==============================================================================
# Static runtime
# ==============================================================================
if(USE_STATIC_RUNTIME)
    if(MSVC)
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
    endif()
    
    if(UNIX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -pthread")
    endif()
endif()

# ==============================================================================
# Sanitizers
# ==============================================================================
message (status, CMAKE_CXX_COMPILER_ID=${CMAKE_CXX_COMPILER_ID})
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    if(SANITIZE_ADDRESS)
        add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
        add_link_options(-fsanitize=address)
        set(ENV{ASAN_OPTIONS} "detect_leaks=1:strict_string_checks=1")
    endif()
    
    if(SANITIZE_UNDEFINED)
        add_compile_options(-fsanitize=undefined)
        add_link_options(-fsanitize=undefined)
    endif()
    
    if(SANITIZE_THREAD)
        if(SANITIZE_ADDRESS)
            message(FATAL_ERROR "Thread sanitizer is not compatible with Address sanitizer")
        endif()
        add_compile_options(-fsanitize=thread)
        add_link_options(-fsanitize=thread)
    endif()
    
    if(SANITIZE_MEMORY)
        if(SANITIZE_ADDRESS OR SANITIZE_THREAD)
            message(FATAL_ERROR "Memory sanitizer is not compatible with Address or Thread sanitizer")
        endif()
        add_compile_options(-fsanitize=memory)
        add_link_options(-fsanitize=memory)
    endif()
else()
    message(WARNING "Sanitizers are only supported for GCC and Clang")
endif()

# ==============================================================================
# System / Conan dependencies
# ==============================================================================
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})
find_package(ZLIB REQUIRED)
find_package(fmt REQUIRED)
find_package(nlohmann_json REQUIRED)

# ==============================================================================
# CPM.cmake dependencies - take care conflicts
# ==============================================================================
include(cmake/tools.cmake)
include(cmake/CPM.cmake)
CPMAddPackage("gh:TheLartians/PackageProject.cmake@1.12.0")
CPMAddPackage("gh:cpm-cmake/CPMLicenses.cmake@0.0.7")
cpm_licenses_create_disclaimer_target(
    write-licenses-${LIBRARY_NAME} "${CMAKE_CURRENT_BINARY_DIR}/${LIBRARY_NAME}_third_party.txt"
    "${CPM_PACKAGES}")

# ==============================================================================
# Source and header files Glob not recommended, but the simplest way for this template
# ==============================================================================
file(
    GLOB_RECURSE
    headers
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hxx)
file(
    GLOB_RECURSE
    sources
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cxx)

# ==============================================================================
# Create target
# ==============================================================================
add_library(${LIBRARY_NAME})
target_sources(${LIBRARY_NAME} PRIVATE ${headers} ${sources})

# ==============================================================================
# Set headers
# ==============================================================================
# header-only libraries change all PUBLIC flags to INTERFACE and create an interface target:
# <add_library(${LIBRARY_NAME} INTERFACE)>
target_include_directories(
    ${LIBRARY_NAME}
    PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Source> # for exceptions 😎
           $<INSTALL_INTERFACE:include/${LIBRARY_NAME}-${PROJECT_VERSION}>)

# ==============================================================================
# Set compile options
# ==============================================================================
# note: generator expressions are evaluated during generation of the buildsystem, and not during processing of CMakeLists.txt files
target_compile_options(
    ${LIBRARY_NAME}
    PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive-;/W4>"
    PUBLIC
        "$<$<AND:$<NOT:$<COMPILE_LANG_AND_ID:CXX,MSVC>>,$<NOT:$<PLATFORM_ID:Darwin>>>:-Wall;-Wextra;-Wpedantic;-MMD;-MP>"
    PUBLIC
        "$<$<AND:$<NOT:$<COMPILE_LANG_AND_ID:CXX,MSVC>>,$<PLATFORM_ID:Darwin>>:-Wall;-Wextra;-Wpedantic>"
)

# ==============================================================================
# Set compile features
# ==============================================================================
target_compile_features(${LIBRARY_NAME} PUBLIC cxx_std_14)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ==============================================================================
# Set linking
# ==============================================================================
target_link_libraries(
    ${LIBRARY_NAME}
    PRIVATE ZLIB::ZLIB
    PRIVATE fmt::fmt
    PRIVATE nlohmann_json::nlohmann_json)

# ==============================================================================
# set packageProject arttributes
# ==============================================================================
packageProject(
    NAME ${LIBRARY_NAME}
    VERSION ${PROJECT_VERSION}
    BINARY_DIR ${PROJECT_BINARY_DIR}
    INCLUDE_DIR "/include"
    INCLUDE_DESTINATION include/${LIBRARY_NAME_LOWER}-${PROJECT_VERSION}
    INCLUDE_HEADER_PATTERN "*.h;*.hpp;*.hh;*.hxx"
    DEPENDENCIES "zlib#1.2.11;fmt#11.1.1;CPMLicenses.cmake@0.0.7;nlohmann_json#3.11.2"
    VERSION_HEADER "${LIBRARY_NAME_LOWER}/version.h"
    EXPORT_HEADER "${LIBRARY_NAME_LOWER}/export.h"
    NAMESPACE ${LIBRARY_NAMESPACE}
    COMPATIBILITY AnyNewerVersion
    DISABLE_VERSION_SUFFIX YES
    ARCH_INDEPENDENT YES
    CPACK YES)

# ==============================================================================
# Set installation directory
# ==============================================================================
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${LIBRARY_NAME} DESTINATION include/)
