cmake_minimum_required(VERSION 3.21)

project(core)

add_library(${PROJECT_NAME}
    src/MApp.cpp
	src/MCoreEngine.cpp
)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		include
)

add_executable(${PROJECT_NAME}_test
   test/main.cpp
)

target_link_libraries(${PROJECT_NAME}_test
    PRIVATE ${PROJECT_NAME}
)

