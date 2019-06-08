cmake_minimum_required (VERSION 3.10)
project(Dining-philosophers LANGUAGES CXX)
set(NAME_PROJECT "Dining-philosophers")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package (Threads)



#SET(COVERAGE OFF CACHE BOOL "Coverage")
# Code Coverage Configuration
add_library(coverage_config INTERFACE)
set(CODE_COVERAGE "Enable coverage reporting" OFF)
if(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  # Add required flags (GCC & LLVM/Clang)
  target_compile_options(coverage_config INTERFACE
    -O0        # no optimization
    -g         # generate debug info
    --coverage # sets all required flags
  )
  if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
    target_link_options(coverage_config INTERFACE --coverage)
  else()
    target_link_libraries(coverage_config INTERFACE --coverage)
  endif()
endif()


# if(CMAKE_BUILD_TYPE STREQUAL "coverage" OR CODE_COVERAGE)
#     if("${CMAKE_C_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang" OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang")
#         message("Building with llvm Code Coverage Tools")

#         # Warning/Error messages
#         if(NOT LLVM_COV_PATH)
#             message(FATAL_ERROR "llvm-cov not found! Aborting.")
#         endif()

#         # set Flags
#         set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
#         set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping")

#     elseif(CMAKE_COMPILER_IS_GNUCXX)
#         message("Building with lcov Code Coverage Tools")

#         # Warning/Error messages
#         if(NOT (CMAKE_BUILD_TYPE STREQUAL "Debug"))
#             message(WARNING "Code coverage results with an optimized (non-Debug) build may be misleading")
#         endif()
#         if(NOT LCOV_PATH)
#             message(FATAL_ERROR "lcov not found! Aborting...")
#         endif()
#         if(NOT GENHTML_PATH)
#             message(FATAL_ERROR "genhtml not found! Aborting...")
#         endif()

#         set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
#         set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
#     else()
#         message(FATAL_ERROR "Code coverage requires Clang or GCC. Aborting.")
#     endif()
# endif()
























# sources file
set(SOURCES main.cpp fork.cpp Philo.cpp Philo.hpp)
# add_library(FORK fork.cpp fork.hpp)
# set_target_properties(FORK
#     PROPERTIES
#     COMPILE_FLAGS "-fpic -g -O0 -Wall -Werror -Wextra -Wpedantic -Wconversion -Wswitch-default -Wswitch-enum -Wunreachable-code -Wwrite-strings -Wcast-align -Wshadow -Wundef -ftest-coverage -fprofile-arcs"
#     LINK_FLAGS    "-lgcov --coverage"
# )
# add_library(PHILO Philo.cpp Philo.hpp ${FORK})
# set_target_properties(PHILO
#     PROPERTIES
#     COMPILE_FLAGS "-fpic -g -O0 -Wall -Werror -Wextra -Wpedantic -Wconversion -Wswitch-default -Wswitch-enum -Wunreachable-code -Wwrite-strings -Wcast-align -Wshadow -Wundef -ftest-coverage -fprofile-arcs"
#     LINK_FLAGS    "-lgcov --coverage"
# )


add_executable(${NAME_PROJECT} ${SOURCES})
target_link_libraries (${NAME_PROJECT} ${CMAKE_THREAD_LIBS_INIT} ${coverage_config})
target_compile_options(${NAME_PROJECT} PUBLIC -fpic -g -O0 -Wall -Werror -Wextra -Wpedantic -Wconversion -Wswitch-default -Wswitch-enum -Wunreachable-code -Wwrite-strings -Wcast-align -Wshadow -Wundef)
# set_target_properties(${NAME_PROJECT}
#     PROPERTIES
#     COMPILE_FLAGS "-ftest-coverage -fprofile-arcs"
#     LINK_FLAGS    "-lgcov --coverage"
# )
