cmake_minimum_required(VERSION 3.21)
project(Librum VERSION 0.1 LANGUAGES CXX)


# Configuration
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
option(BUILD_TESTS ON)
option(ENABLE_COVERAGE OFF)
option(USE_SANITIZERS OFF) # Slows down program startup significantly



# Create a set of warnings
string(CONCAT LIBRUM_WARNINGS "-Wall;-Wextra;-Wshadow;-Wnon-virtual-dtor;-Wold-style-cast;-Wcast-align;"
                              "-Wunused;-Woverloaded-virtual;-Wpedantic;-Wmissing-include-dirs;"
                              "-Wnull-dereference;-Wdouble-promotion;-Wformat=2;-Wcast-qual;-Winit-self;"
                              "-Wswitch-enum;-Wunreachable-code;-Wredundant-decls;")

# GCC specific warnings
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU") # If compiler is GCC
    list(APPEND LIBRUM_WARNINGS "-Wduplicated-cond")
    list(APPEND LIBRUM_WARNINGS "-Wduplicated-branches")
    list(APPEND LIBRUM_WARNINGS "-Wunsafe-loop-optimizations")
    list(APPEND LIBRUM_WARNINGS "-Wlogical-op")
    list(APPEND LIBRUM_WARNINGS "-Wunsafe-loop-optimizations")
endif()


# Create variables for coverage compiler an linker flags
if(ENABLE_COVERAGE)
    string(CONCAT COVERAGE_COMPILE_OPTIONS "-fprofile-arcs;-ftest-coverage;-fno-inline;--coverage")
    string(CONCAT COVERAGE_LINKING_OPTIONS "-lgcov;--coverage;")
endif()


# Create a set of sanitizers
if(USE_SANITIZERS)
    string(CONCAT LIBRUM_SANITIZERS "-fsanitize=address,undefined,shift,integer-divide-by-zero,"
                                    "float-divide-by-zero,unreachable,vla-bound,null,return,leak,"
                                    "bounds,float-cast-overflow,enum")
endif()


# Dependencies
#add_subdirectory(libs/rapidfuzz-cpp)


# Build
add_subdirectory(src/)



# Tests
if(BUILD_TESTS)
    add_subdirectory(libs/googletest)
    add_subdirectory(tests/)
endif()
