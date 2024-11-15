cmake_minimum_required(VERSION 3.14)
project(UniTasks VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

# Fetch and build zlib
FetchContent_Declare(
    zlib
    URL https://zlib.net/zlib-1.3.1.tar.gz
    URL_HASH SHA256=9a93b2b7dfdac77ceba5a558a580e74667dd6fede4585b91eefb60f03b72df23
)
FetchContent_MakeAvailable(zlib)

# Set ZLIB variables for libxlsxwriter to find
set(ZLIB_LIBRARY zlibstatic)
set(ZLIB_INCLUDE_DIR ${zlib_SOURCE_DIR} ${zlib_BINARY_DIR})
set(ZLIB_FOUND TRUE)

# Configure libxlsxwriter options
set(USE_SYSTEM_ZLIB OFF CACHE BOOL "Use system zlib")
set(BUILD_TESTS OFF CACHE BOOL "Build libxlsxwriter tests")
set(BUILD_EXAMPLES OFF CACHE BOOL "Build libxlsxwriter examples")
set(USE_STANDARD_TMPFILE ON CACHE BOOL "Use standard tmpfile")

# Fetch and build libxlsxwriter
FetchContent_Declare(
    libxlsxwriter
    GIT_REPOSITORY https://github.com/jmcnamara/libxlsxwriter.git
    GIT_TAG v1.1.9
)
FetchContent_MakeAvailable(libxlsxwriter)

# Define your source files
set(SOURCES
    "src/main.cpp"
    "src/Anagrams.cpp"
    "src/CoinScale.cpp"
    "src/TowerOfHanoi.cpp"
    "src/Sorting/Sort.cpp"
    "src/2nDisks.cpp"
    
    "src/Sorting/SortingTester.cpp"
    "src/Sorting/Test.cpp"
)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link against xlsxwriter and zlib
target_link_libraries(${PROJECT_NAME} PRIVATE 
    xlsxwriter 
    zlibstatic
)

# Add include directories for zlib and libxlsxwriter
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${libxlsxwriter_SOURCE_DIR}/include
    ${zlib_SOURCE_DIR}
    ${zlib_BINARY_DIR}
)