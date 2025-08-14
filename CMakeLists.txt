# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Define the project name and version
project(BloomFilterProject VERSION 1.0)

# Set the C++ standard to use (you can change 17 to whatever version you prefer)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the source files (where cpp files are located)
set(SOURCES
    src/main.cpp
    src/bloom_filter.cpp
    src/hash_function.cpp
    src/murmur3.cpp
)

# Define the executable target (what you want to build)
add_executable(BloomFilter ${SOURCES})

# Now, add the include directory for this specific target
target_include_directories(BloomFilter PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Optionally link libraries (for now, no external libraries are mentioned)
# target_link_libraries(BloomFilter <your_libraries_here>)
