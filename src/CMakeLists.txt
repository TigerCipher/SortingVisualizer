find_package(GLUT REQUIRED)

add_executable (SortingVisualizer  "main.cpp"      "Sorting.h"  "Sorting.cpp")
target_link_libraries(SortingVisualizer PRIVATE GLUT::GLUT)

