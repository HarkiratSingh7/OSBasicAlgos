include_directories(${OSBasicAlgos_SOURCE_DIR}/ProcessSchAlgos/lib)
link_directories(${OSBasicAlgos_SOURCE_DIR}/OSBasicAlgos/src)
add_executable(fcfsProgram main.cpp)
target_link_libraries(fcfsProgram INTERFACE ProcSchAlgos)