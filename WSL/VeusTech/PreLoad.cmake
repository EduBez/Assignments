#  The best way to use installed libraries with CMake is via the toolchain file scripts\buildsystems\vcpkg.cmake
#  To use this file, you simply need to add it onto your CMake command line as;
#    -DCMAKE_TOOLCHAIN_FILE=vcpkg root\scripts\buildsystems\vcpkg.cmake

if(WIN32)
    # Define VCPKG default triplet
    set(VCPKG_TARGET_TRIPLET "x64-windows" CACHE STRING "")

    # Use 'VcPkg' installed libs with CMake via its toolchain file
    set(CMAKE_TOOLCHAIN_FILE "C:/VcPkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

if(UNIX)
    # Use 'VcPkg' installed libs with CMake via its toolchain file
    set(CMAKE_TOOLCHAIN_FILE "~/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()
