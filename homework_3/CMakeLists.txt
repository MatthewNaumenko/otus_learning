cmake_minimum_required(VERSION 3.12)

project(homework VERSION 3.0)

add_executable(homework_${PROJECT_VERSION_MAJOR}
    main.cpp
)

set_target_properties(homework_${PROJECT_VERSION_MAJOR} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)