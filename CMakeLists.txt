cmake_minimum_required(VERSION 3.20)
project(JuodaBalta)

set(CMAKE_CXX_STANDARD 17)

include(conan/conanbuildinfo.cmake)
conan_basic_setup()

file(GLOB_RECURSE JUODA_BALTA_SOURCE Source/JuodaBalta/Public/*.h Source/JuodaBalta/Public/*.cpp)
file(GLOB_RECURSE JUODA_BALTA_SOURCE Source/JuodaBalta/Private/*.h Source/JuodaBalta/Private/*.cpp)
add_library(JuodaBalta ${JUODA_BALTA_SOURCE})
target_include_directories(JuodaBalta PRIVATE Source/JuodaBalta)

file(GLOB_RECURSE SPEC_SOURCE Source/GTest/*.h Source/GTest/*.cpp)
add_executable(GTest ${SPEC_SOURCE})
target_include_directories(GTest PRIVATE Source/JuodaBalta)
target_include_directories(GTest PRIVATE Source/Fixtures)
target_link_libraries(GTest ${CONAN_LIBS})
target_link_libraries(GTest JuodaBalta)

file(GLOB_RECURSE PERFORMANCE_TEST_SOURCE Source/PerformanceTest/*.h Source/PerformanceTest/*.cpp)
add_executable(PerformanceTest ${PERFORMANCE_TEST_SOURCE})
target_include_directories(PerformanceTest PRIVATE Source/JuodaBalta)
target_include_directories(PerformanceTest PRIVATE Source/Fixtures)
target_link_libraries(PerformanceTest JuodaBalta)
