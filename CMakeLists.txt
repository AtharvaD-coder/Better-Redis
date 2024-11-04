
cmake_minimum_required(VERSION 3.14)
project(Better_Redis)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add the executable
add_executable(better_redis main.cpp)

# Add GoogleTest
add_subdirectory(libs/googletest)

# Include directories for better-redis
target_include_directories(better_redis PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/googletest/googletest/include
    ${CMAKE_SOURCE_DIR}/libs/concurrentqueue
    )

# Link libraries for better-redis
target_link_libraries(better_redis gtest gtest_main)

# Add test executable
add_executable(run_tests tests/database.cpp)
target_link_libraries(run_tests gtest gtest_main)

# Include directories for tests
target_include_directories(run_tests PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/googletest/googletest/include
)

