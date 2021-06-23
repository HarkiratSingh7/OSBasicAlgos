cmake_minimum_required(VERSION 3.0.0)
project(OSBasicAlgos VERSION 0.1.0)

include(CTest)
enable_testing()
add_subdirectory(ProcessSchAlgos)
add_subdirectory(Deadlocks)
add_subdirectory(Monitors)
add_subdirectory(Demos)