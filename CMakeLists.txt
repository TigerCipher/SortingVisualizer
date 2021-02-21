# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.16)

project ("SortingVisualizer")

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
        CACHE STRING "Vcpkg toolchain file")

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # Lets us use folders in IDEs
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    # Enable testing for the main application
    #include(CTest)

    find_package(Doxygen)
    if(Doxygen_FOUND)
        message(STATUS "Found Doxygen")
        add_subdirectory(docs)
    else()
        message(STATUS "Doxygen not found, cannot build docs")
    endif()
endif()

# Include sub-projects.
add_subdirectory ("src")
