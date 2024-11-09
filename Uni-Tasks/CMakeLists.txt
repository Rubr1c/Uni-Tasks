cmake_minimum_required(VERSION 3.14)
project(UniTasks VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(XLSXIO_PATH "${CMAKE_SOURCE_DIR}/dependencies/xlsxio")

set(XLSXIO_INCLUDE_DIR "${XLSXIO_PATH}/include")
set(XLSXIO_LIBRARY_DIR "${XLSXIO_PATH}/lib")

if (EXISTS "${XLSXIO_INCLUDE_DIR}" AND EXISTS "${XLSXIO_LIBRARY_DIR}")
    message(STATUS "XLSX I/O found at ${XLSXIO_PATH}")
else()
    message(FATAL_ERROR "XLSX I/O not found at ${XLSXIO_PATH}. Please check the path.")
endif()

# Define source files
set(SOURCES
    "src/main.cpp"
    "src/Anagrams.cpp"
    "src/CoinScale.cpp"
    "src/TowerOfHanoi.cpp"
    "src/Sorting/Sort.cpp"
    "src/2nDisks.cpp"
 "src/Sorting/Excel.cpp" "src/Sorting/SortingTester.cpp" "src/Sorting/Test.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(UniTasks PRIVATE
    ${XLSXIO_LIBRARY_DIR}/libxlsxio_write.dll.a
    ${XLSXIO_LIBRARY_DIR}/libxlsxio_read.dll.a
)

target_include_directories(UniTasks PRIVATE ${XLSXIO_INCLUDE_DIR})
