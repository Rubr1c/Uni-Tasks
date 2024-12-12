cmake_minimum_required(VERSION 3.7.2)
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
    "src/Task-1/Anagram.cpp"
    "src/Task-2/CoinScale.cpp"
    "src/Task-3/Sort.cpp"
    "src/Task-3/SortingTester.cpp"
    "src/Task-3/Test.cpp"
    "src/Task-3/JSONBuilder.cpp" 
    "src/Task-4/TowerOfHanoi.cpp"
    "src/Task-5/2nDisks.cpp"
    "src/Task-6/TextWrapping.cpp"
    "src/Task-7/Maze.cpp" 
    "src/Task-8/LinkedList.cpp"
    "src/Task-8/student.cpp" 
    "src/Task-8/ParallelReader.cpp"
    "src/InvokeTasks.cpp" 
     )

# Check operating system and set appropriate definitions
if(WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-DWIN32_LEAN_AND_MEAN)
    add_definitions(-D_WIN32)
endif()

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})
if(MSVC AND CLANG_TIDY_EXE)
    set_property(TARGET ${PROJECT_NAME} PROPERTY VS_GLOBAL_RunCodeAnalysis true)
    set_property(TARGET ${PROJECT_NAME} PROPERTY VS_GLOBAL_ClangTidyChecks "*")
endif()

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
    ${zlib_BINARY_DIR}
)
