cmake_minimum_required(VERSION 3.12)

project(homework VERSION 5.0)

add_executable(homework_${PROJECT_VERSION_MAJOR}
    statictic.cpp
    statictic.h
)

set_target_properties(homework_${PROJECT_VERSION_MAJOR} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)