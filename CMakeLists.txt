cmake_minimum_required(VERSION 3.14)

project(
  libfvb
  VERSION 0.0.1
  DESCRIPTION "A C library"
  LANGUAGES C
)

option(CMAKE_BUILD_TYPE release)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SOURCES "src/*.c")

add_library(libfvb SHARED
  ${SOURCES}
)

target_include_directories(libfvb PRIVATE "include/")
target_link_libraries(libfvb m)

add_subdirectory(test)


set_target_properties(libfvb PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(libfvb PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
