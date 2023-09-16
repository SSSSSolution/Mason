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

add_executable(${PROJECT_NAME}_NoPresetCfgTest
	test/MAppNoPresetCfgTest.cpp
)

target_link_libraries(${PROJECT_NAME}_NoPresetCfgTest PRIVATE
	GTest::gtest
	GTest::gtest_main
	GTest::gmock
	GTest::gmock_main
	${PROJECT_NAME}
)

add_executable(${PROJECT_NAME}_PresetCfgInArgsTest
	test/MAppPresetCfgInArgsTest.cpp
)

target_link_libraries(${PROJECT_NAME}_PresetCfgInArgsTest PRIVATE
	GTest::gtest
	GTest::gtest_main
	GTest::gmock
	GTest::gmock_main
	${PROJECT_NAME}
)

add_executable(${PROJECT_NAME}_PresetCfgInWDTest
	test/MAppPresetCfgInWDTest.cpp
)


target_link_libraries(${PROJECT_NAME}_PresetCfgInWDTest PRIVATE
	GTest::gtest
	GTest::gtest_main
	GTest::gmock
	GTest::gmock_main
	${PROJECT_NAME}
)

add_test(
	NAME ${PROJECT_NAME}_MAppTest
	COMMAND ${PROJECT_NAME}_NoPresetCfgTest
			${PROJECT_NAME}_PresetCfgInArgsTest
			${PROJECT_NAME}_PresetCfgInWDTest
)

set_tests_properties(${PROJECT_NAME}_MAppTest PROPERTIES
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/MAppTestWD
)


