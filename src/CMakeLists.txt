find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_executable (SortingVisualizer  "main.cpp" "Display.h" "Common.h" "Display.cpp" "Visualizer.h" "Visualizer.cpp")
target_link_libraries(SortingVisualizer PRIVATE glfw GLEW::GLEW fmt::fmt glm)
