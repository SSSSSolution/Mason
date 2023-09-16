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


# test
enable_testing()

find_package(GTest CONFIG REQUIRED)

add_executable(${PROJECT_NAME}_test
	test/main.cpp
)

target_link_libraries(${PROJECT_NAME}_test PRIVATE
	GTest::gtest
	GTest::gtest_main
	GTest::gmock
	GTest::gmock_main
	${PROJECT_NAME}
)

add_test(
	NAME ${RPOJECT_NAME}_test
	COMMAND ${RPOJECT_NAME}_test
)

