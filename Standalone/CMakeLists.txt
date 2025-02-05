cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
cmake_policy(SET CMP0091 NEW)

# === options ==================================================================
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)
option(USE_STATIC_RUNTIME "Link against static runtime libraries" OFF)
option(SANITIZE_ADDRESS "Enable Address sanitizer" OFF)
option(SANITIZE_UNDEFINED "Enable Undefined Behavior sanitizer" ON)
option(SANITIZE_THREAD "Enable Thread sanitizer" OFF)
option(SANITIZE_MEMORY "Enable Memory sanitizer" OFF)

# Linting C/C++ code
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ==============================================================================
# Project attributes
# ==============================================================================
set(STANDALONE_NAME DesignPatternsCppStandalone)
string(TOLOWER "${STANDALONE_NAME}" STANDALONE_NAME_LOWER)
set(STANDALONE_NAMESPACE dsdotname)
project(
    ${STANDALONE_NAME}
    LANGUAGES C CXX ASM
    DESCRIPTION "template Copyright (c) 2024 TomasMark [at] digitalspace.name"
    HOMEPAGE_URL "https://github.com/tomasmark79")

# ---- Include guards ----
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

# ==============================================================================
# CPM.cmake dependencies - take care conflicts
# ==============================================================================
include(../cmake/tools.cmake)
include(../cmake/CPM.cmake)
CPMAddPackage(NAME DesignPatternsCppLib SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
cpm_licenses_create_disclaimer_target(
    write-licenses-${STANDALONE_NAME}
    "${CMAKE_CURRENT_BINARY_DIR}/${STANDALONE_NAME}_third_party.txt" "${CPM_PACKAGES}")

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
add_executable(${STANDALONE_NAME} ${sources})

# ==============================================================================
# Set compile properties
# ==============================================================================
set_target_properties(${STANDALONE_NAME} PROPERTIES OUTPUT_NAME "${STANDALONE_NAME}")

# ==============================================================================
# Set linking
# ==============================================================================
target_link_libraries(${STANDALONE_NAME} PRIVATE dsdotname::DesignPatternsCppLib)

# ==============================================================================
# Set installation directory
# ==============================================================================
install(TARGETS ${STANDALONE_NAME} RUNTIME DESTINATION bin)
