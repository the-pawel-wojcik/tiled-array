cmake_minimum_required(VERSION 3.31)
project(
    tutorial
    VERSION 0.1.0
    LANGUAGES CXX C
)

add_subdirectory("src")

find_package(OpenMP REQUIRED)
target_link_libraries(first INTERFACE OpenMP::OpenMP_CXX)

find_package(MPI REQUIRED)
target_link_libraries(first PUBLIC MPI::MPI_CXX)

find_package(tiledarray REQUIRED)
target_link_libraries(first PUBLIC tiledarray)
