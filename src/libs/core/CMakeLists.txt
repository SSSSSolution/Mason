cmake_minimum_required(VERSION 3.21)

project(core)

find_package(spdlog CONFIG REQUIRED)

add_library(${PROJECT_NAME} SHARED
    src/MApp.cpp
	src/MLog.cpp
	src/MCoreEngine.cpp
	include/core/IRenderEngine.h
	include/core/ILogicEngine.h
	src/ILogicEngine.cpp
	src/LogicEngine.h
	src/LogicEngine.cpp
	src/IRenderEngine.cpp
	src/RenderEngine.h
	src/RenderEngine.cpp
	src/MGame.cpp
)

target_compile_definitions(${PROJECT_NAME} PRIVATE MASON_CORE_DLL)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		include
)

target_link_libraries(${PROJECT_NAME} PUBLIC
	spdlog::spdlog
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
	spdlog::spdlog
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
    spdlog::spdlog
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
	spdlog::spdlog
)

add_executable(${PROJECT_NAME}_MLogTest
	test/MLogTest.cpp
)

target_link_libraries(${PROJECT_NAME}_MLogTest PRIVATE
	GTest::gtest
	GTest::gtest_main
	GTest::gmock
	GTest::gmock_main
	${PROJECT_NAME}
	spdlog::spdlog
)

add_test(
	NAME ${PROJECT_NAME}_MAppTest
	COMMAND ${PROJECT_NAME}_NoPresetCfgTest
			${PROJECT_NAME}_PresetCfgInArgsTest
			${PROJECT_NAME}_PresetCfgInWDTest
			${PROJECT_NAME}_MLogTest
)

set_tests_properties(${PROJECT_NAME}_MAppTest PROPERTIES
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/MAppTestWD
)
