cmake_minimum_required(VERSION 3.20)

project(iq)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

#link_directories(${OpenGL_LIBRARY_DIRS})
#add_definitions(${OpenGL_DEFINITIONS})

set(
    SOURCES
    block.cpp
    game.cpp
    input.cpp
    main.cpp
    system.cpp
)

add_executable(a ${SOURCES})

#target_include_directories(${ff-ogl} PUBLIC ${SDL2_INCLUDE_DIRS})

#target_link_libraries(${PROJECT_NAME} PUBLIC SDL2::SDL2)
target_link_libraries(a PUBLIC SDL2::SDL2)