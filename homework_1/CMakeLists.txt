cmake_minimum_required(VERSION 3.12)

project(homework VERSION 1.0)

add_executable(homework_${PROJECT_VERSION_MAJOR}
    example.h
    example.cpp
    move_me_out.cpp
    move_me_out.h
    hello_world.cpp
)

set_target_properties(homework_${PROJECT_VERSION_MAJOR} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)