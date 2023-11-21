cmake_minimum_required(VERSION 3.25)
project(linearalgerba)

set(CMAKE_CXX_STANDARD 20)

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


add_executable(linearalgerba
        main.cpp
        RowVector.h
        ColVector.h
        Matrix.h )

target_link_libraries(linearalgerba  PRIVATE  Eigen3::Eigen)


enable_testing()

add_executable(
        tests
        test.cc
)
target_link_libraries(
        tests
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)
