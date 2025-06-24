cmake_minimum_required(VERSION 3.10)

project(app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(include)

file(GLOB SOURCES
    src/*.cpp    
)

add_executable(app ${SOURCES})

find_package(Threads REQUIRED)

target_link_libraries(app PRIVATE Threads::Threads)
