# Project supports 'Visual Studio 2019 CMake'
#
# Configurations available:
#   Windows
#   WSL 1.0
#   Linux

cmake_minimum_required(VERSION 3.10)
           
project(RdwDecoder)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Werror -Wextra -pedantic")
endif()

# Enable testing for current directory and below
enable_testing()

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

add_subdirectory(tests)

add_executable(${PROJECT_NAME}
   "./src/HemAnaGen.cpp"
   "./src/RdwDecoder.cpp"
   "./src/StdCinUtil.cpp"
   "./src/VeusMain.cpp")

if(UNIX)
   target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
endif()
