add_definitions(-DFILESPATH=\"${CMAKE_CURRENT_SOURCE_DIR}/files/\")

add_subdirectory(tst_core)
add_subdirectory(tst_parser)
add_subdirectory(tst_gui)
