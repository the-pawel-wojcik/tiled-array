cmake_minimum_required(VERSION 3.31)
project(
    tiled-aray-pg
    VERSION 0.1.0
    LANGUAGES CXX C
)

find_package(OpenMP REQUIRED)
find_package(MPI REQUIRED)
find_package(tiledarray REQUIRED)

file(GLOB PROGRAMS_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

foreach(program ${PROGRAMS_LIST})
    get_filename_component(program_name ${program} NAME_WE)

    add_executable(${program_name} ${program})
    target_compile_features(${program_name} PUBLIC cxx_std_20)

    target_link_libraries(${program_name} INTERFACE OpenMP::OpenMP_CXX)
    target_link_libraries(${program_name} PUBLIC MPI::MPI_CXX)
    target_link_libraries(${program_name} PUBLIC tiledarray)
endforeach()
