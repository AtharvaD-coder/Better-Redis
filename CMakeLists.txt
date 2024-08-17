# Specify the minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Better_Redis)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable to be built from the source files
add_executable(better-redis main.cpp)

# Include directories (optional)
# target_include_directories(MyExecutable PRIVATE include_dir)

# Link libraries (optional)
# target_link_libraries(MyExecutable PRIVATE my_library)
