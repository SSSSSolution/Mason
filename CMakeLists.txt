cmake_minimum_required(VERSION 3.21)

project(Mason)

set(CMAKE_CXX_STANDARD 17)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

include_directories(src/libs)

add_subdirectory(src/libs/core)

add_subdirectory(src/apps/JourneyToWest)