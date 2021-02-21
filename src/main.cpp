// ------------------------------------------------------------------------------
// 
// SortingVisualizer
// Copyright (C) 2021 Blue Moon Development. All rights reserved.
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
// 
// Contact: team@bluemoondev.org
// 
// File Name: main.cpp
// Date File Created: 02/21/2021 at 3:02 PM
// Author: Matt
// 
// ------------------------------------------------------------------------------


#include <fmt/core.h>
#include "Display.h"
#include "Visualizer.h"

#include <GLFW/glfw3.h>

int main(int argc, char** argv)
{
	Display display("Sorting Visualizer", 1280, 720);

	auto counter = 0;

	int arr[400];
	for (auto& i : arr)
	{
		i = rand() % 600;
	}

	Visualizer visualizer;

	glfwSetTime(0);
	while(!display.isClosed())
	{
		auto fps = static_cast<double>(counter) / glfwGetTime();
		if(glfwGetTime() >= 1.0)
		{
			fmt::print("FPS: {:.2f}\t-\t{:.2f} ms/frame\n", fps, 1000.0 / fps);
			counter = 0;
			glfwSetTime(0);
		}
		display.clear(255, 255, 255);

		visualizer.draw();
		
		display.swap();
		counter++;
	}
	return 0;
}