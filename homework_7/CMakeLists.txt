cmake_minimum_required(VERSION 3.12)
project(homework VERSION 7.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/MTd)  
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")  
endif()

add_executable(homework_${PROJECT_VERSION_MAJOR}
    IList.hpp
    IVector.hpp
    IContainer.h
    main.cpp
)

add_executable(containers_tests
    test/IList_tests.cpp
    test/IVector_tests.cpp
    test/main_tests.cpp
)

set_target_properties(containers_tests PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.0
)

FetchContent_MakeAvailable(googletest)

target_include_directories(containers_tests PRIVATE
    ${gtest_SOURCE_DIR}/include
)

target_link_libraries(containers_tests
    gtest
    gtest_main
)

