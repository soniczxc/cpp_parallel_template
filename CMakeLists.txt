cmake_minimum_required(VERSION 3.15.0)
cmake_policy(SET CMP0016 NEW)

project(parallel_executor VERSION 1.0.0 DESCRIPTION "Синхронизация нескольких потоков исполнения через очередь сообщений на C++")
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(${CMAKE_SOURCE_DIR}/src)
file(GLOB Device_SRC
        "src/parallel_executor/Device/*.h"
        "src/parallel_executor/Device/*.cpp"
        )
file(GLOB Event_SRC
        "src/parallel_executor/Event/*.h"
        "src/parallel_executor/Event/*.cpp"
        )
file(GLOB EventQueue_SRC
        "src/parallel_executor/EventQueue/*.h"
        "src/parallel_executor/EventQueue/*.cpp"
        )
file(GLOB Parser_SRC
        "src/parallel_executor/Parser/*.h"
        "src/parallel_executor/Parser/*.cpp")
add_library(device ${Device_SRC})
add_library(event ${Event_SRC})
add_library(eventQueue ${EventQueue_SRC})
add_library(parser ${Parser_SRC})

add_executable(${PROJECT_NAME} src/parallel_executor/main.cpp)

target_include_directories(eventQueue PUBLIC src/parallel_executor/Event)
target_include_directories(event PUBLIC src/parallel_executor/Device)
target_include_directories(${PROJECT_NAME} PUBLIC
        src/parallel_executor/Device
        src/parallel_executor/Event
        src/parallel_executor/EventQueue
        src/parallel_executor/Parser
)

target_link_libraries(${PROJECT_NAME} parser device event eventQueue)



enable_testing()

add_subdirectory(test)

