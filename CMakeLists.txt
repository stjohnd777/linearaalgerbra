cmake_minimum_required(VERSION 3.25)
project(linear_algebra)

set(CMAKE_CXX_STANDARD 20)


# Recursively collect all header files in the 'header/' directory
set(HEADER_DIRECTORY "${CMAKE_SOURCE_DIR}/include")
file(GLOB_RECURSE HEADER_FILES
        "${HEADER_DIRECTORY}/*.h"
        "${HEADER_DIRECTORY}/*.hpp"
)
# Recursively collect all cpp files in the 'header/' directory
set(SOURCE_DIRECTORY "${CMAKE_SOURCE_DIR}/src" )
file(GLOB_RECURSE SOURCE_FILES
        "${SOURCE_DIRECTORY}/*.c"
        "${SOURCE_DIRECTORY}/*.cpp"
)

include(FetchContent)
find_package(Eigen3 REQUIRED)
if(Eigen3_FOUND)
    link_directories(${Eigen_INCLUDE_DIRS})
    message(STATUS "Found Eigen Success!" Eigen3::Eigen)
else()
    FetchContent_Declare(
            Eigen
            GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
            GIT_TAG master
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE)
    set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
    set(EIGEN_BUILD_DOC OFF)
    set(EIGEN_BUILD_PKGCONFIG OFF)
    FetchContent_MakeAvailable(Eigen)
endif()


find_package(GTest REQUIRED)
if(GTest_FOUND)
    message(STATUS "Found GTest Success!" ${GTest_LIBS})
else ()
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()


add_library(linear_algebra
        ${HEADER_FILES}
        ${SOURCE_FILES}
        include/Vector.h
)

# Add the include directory for headers to the linear_algebra library
target_include_directories(linear_algebra
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

add_executable(linear_algebra_main main/main.cpp )
target_link_libraries(linear_algebra_main PUBLIC linear_algebra)


enable_testing()
set(TEST_DIRECTORY "${CMAKE_SOURCE_DIR}/test" )
file(GLOB_RECURSE TEST_FILES
#        "${TEST_DIRECTORY}/*.h"
        "${TEST_DIRECTORY}/*.cc"
)
add_executable(
        tests
        ${TEST_FILES}
)

target_link_libraries(
        tests
        GTest::gtest_main
        linear_algebra
        Eigen3::Eigen
)

include(GoogleTest)
gtest_discover_tests(tests)
