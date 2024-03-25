set(CMAKE_BUILD_TYPE Debug)

file(GLOB SOURCES "../src/*.c")
set(SOURCES ${SOURCES} "./dsp_test.c")

message(${SOURCES})

add_executable(tester ${SOURCES})
target_include_directories(tester PRIVATE "../include/")
target_link_libraries(tester m)
target_link_libraries(tester check)
target_link_libraries(tester subunit)

add_test(Tester tester)
