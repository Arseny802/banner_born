cmake_minimum_required(VERSION 3.17)
project(BannerBorn)

set(CMAKE_CXX_STANDARD 20)
set(CONAN_CMAKE_CXX_STANDARD 20)

set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/third-party)
include(ExternalProject)
ExternalProject_Add(hare
        GIT_REPOSITORY https://github.com/Arseny802/hare
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}/hare
        )

if (CONAN_EXPORTED) # in conan local cache
    message(STATUS "Conan is exported.")
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup(TARGETS)
else () # in user space
    message(STATUS "Conan is NOT exported.")
    if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
        file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake" "${CMAKE_BINARY_DIR}/conan.cmake")
    endif ()
    include(${CMAKE_BINARY_DIR}/conan.cmake)
    conan_cmake_run(CONANFILE conanfile.txt BASIC_SETUP CMAKE_TARGETS BUILD missing)
    conan_basic_setup()
endif ()

add_executable(BannerBorn main.cpp)
target_link_libraries(BannerBorn ${CONAN_LIBS})