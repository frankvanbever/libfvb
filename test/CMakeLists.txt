find_package(PkgConfig REQUIRED)

set(CMAKE_BUILD_TYPE Debug)

file(GLOB SOURCES "../src/*.c")
set(SOURCES ${SOURCES} "./dsp_test.c")

message(${SOURCES})

add_executable(tester ${SOURCES})
target_include_directories(tester PRIVATE "../include/")
target_link_libraries(tester m)


pkg_check_modules(CHECK REQUIRED check)
target_link_libraries(tester ${CHECK_LIBRARIES})
target_include_directories(tester PUBLIC ${CHECK_INCLUDE_DIRS})
target_compile_options(tester PUBLIC ${CHECK_CFLAGS_OTHER})


add_test(Tester tester)
