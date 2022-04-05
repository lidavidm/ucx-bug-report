cmake_minimum_required(VERSION 3.10)
project(BugReport)

find_package(UCX REQUIRED)
find_package(CUDAToolkit REQUIRED)

add_executable(main main.cc)
add_library(client_server SHARED ucp_client_server.c)

target_compile_definitions(client_server PRIVATE HAVE_CUDA)
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# TODO: ucp should have ucs in its interface_link_libraries
target_link_libraries(main dl)
target_link_libraries(client_server ucx::ucp ucx::ucs CUDA::cuda_driver CUDA::cudart)
