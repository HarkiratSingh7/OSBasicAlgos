include_directories(${OSBasicAlgos_SOURCE_DIR}/Monitors/lib)
link_directories(${OSBasicAlgos_SOURCE_DIR}/OSBasicAlgos/src)
add_executable(diningPhilosophers main.cpp)
target_link_libraries(diningPhilosophers INTERFACE MonitorsAlgos)