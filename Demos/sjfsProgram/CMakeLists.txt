include_directories(${OSBasicAlgos_SOURCE_DIR}/ProcessSchAlgos/lib)
link_directories(${OSBasicAlgos_SOURCE_DIR}/OSBasicAlgos/src)
add_executable(sjfsProgram main.cpp)
target_link_libraries(sjfsProgram INTERFACE OSBasicAlgos)