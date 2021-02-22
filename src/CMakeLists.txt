find_package(GLUT REQUIRED)

add_executable (SortingVisualizer  "main.cpp"      "Sorting.h" )
target_link_libraries(SortingVisualizer PRIVATE GLUT::GLUT)

