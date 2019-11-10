cmake_minimum_required(VERSION 3.5)
project(configfile)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-D_GLIBCXX_USE_C99=1)

set(src_dir ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(main_dir ${CMAKE_CURRENT_SOURCE_DIR}/test_main)

include_directories("${src_dir}")

aux_source_directory("${src_dir}" SRCS)
aux_source_directory("${main_dir}" SRCS)

add_executable(configfile ${SRCS})
