# Project supports 'Visual Studio 2019 CMake'
#
# Configurations available:
#   Windows
#   WSL 1.0
#   Linux

cmake_minimum_required(VERSION 3.10)

project(RdwDecoderTests)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Werror -Wextra -pedantic")
endif()

# Enable testing for current directory
enable_testing()

# Locate Google Test framework
find_package(GTest CONFIG REQUIRED)

# Load and run CMake code from 'GoogleTest' module
include(GoogleTest)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../src")

add_executable(
   ${PROJECT_NAME}
   "../src/HemAnaGen.cpp"
   "../src/RdwDecoder.cpp"
   "../src/StdCinUtil.cpp"
   "./src/RdwDecoderTests.cpp"
   "./src/VeusMainTests.cpp"
)

if (WIN32)
    target_link_libraries(${PROJECT_NAME}
        PRIVATE
            GTest::gtest
            GTest::gtest_main
            GTest::gmock
            GTest::gmock_main)
endif()

if (UNIX)
    target_link_libraries(${PROJECT_NAME}
        PRIVATE
            GTest::gtest
            GTest::gtest_main
            GTest::gmock
            pthread)
endif()

# Discover all tests in the project. Can only appear after 'target_link_libraries()'
gtest_discover_tests(${PROJECT_NAME})
