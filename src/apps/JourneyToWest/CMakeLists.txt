cmake_minimum_required(VERSION 3.21)

project(JourneyToWest)

add_executable(${PROJECT_NAME}
   src/main.cpp
   src/items/GroundItem.h
   src/items/GroundItem.cpp
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC core
)