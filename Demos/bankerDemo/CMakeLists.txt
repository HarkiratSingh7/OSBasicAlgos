include_directories(${OSBasicAlgos_SOURCE_DIR}/Deadlocks/lib)
link_directories(${OSBasicAlgos_SOURCE_DIR}/OSBasicAlgos/src)
add_executable(bankerDemo main.cpp)
target_link_libraries(bankerDemo INTERFACE DeadlockAlgos)