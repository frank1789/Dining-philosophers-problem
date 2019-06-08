cmake_minimum_required (VERSION 3.10)
project(Dining-philosophers LANGUAGES CXX)
set(NAME_PROJECT "Dining-philosophers")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

SET(COVERAGE OFF CACHE BOOL "Coverage")

# sources file
set(SOURCES main.cpp fork.cpp Philo.cpp Philo.hpp)
add_executable(${NAME_PROJECT} ${SOURCES})
target_compile_options(${NAME_PROJECT} PUBLIC -g -O0 -Wall -Werror -Wextra -Wpedantic -Wconversion -Wswitch-default -Wswitch-enum -Wunreachable-code -Wwrite-strings -Wcast-align -Wshadow -Wundef)
set_target_properties(${NAME_PROJECT}
    PROPERTIES
    COMPILE_FLAGS "-ftest-coverage -fprofile-arcs"
    LINK_FLAGS    "-lgcov --coverage"
)
