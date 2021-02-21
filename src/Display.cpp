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
// File Name: Display.cpp
// Date File Created: 02/21/2021 at 3:10 PM
// Author: Matt
// 
// ------------------------------------------------------------------------------

#include "Display.h"

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <fmt/core.h>

void glfw_error_callback(int error, const char* desc)
{
	fmt::print(stderr, "Error {}: {}\n", error, desc);
}

Display::Display(std::string title, int width, int height):
	mTitle(std::move(title)),
	mWidth(width),
	mHeight(height)
{
	if(!glfwInit())
	{
		fmt::print(stderr, "Failed to initialize glfw\n");
		exit(-1);
	}

	glfwSetErrorCallback(glfw_error_callback);

	mWindow = glfwCreateWindow(width, height, mTitle.c_str(), nullptr, nullptr);

	if(!mWindow)
	{
		fmt::print(stderr, "Failed to create window\n");
		exit(-1);
	}

	int centerX = (glfwGetVideoMode(glfwGetPrimaryMonitor())->width / 2) - (width / 2);
	int centerY = (glfwGetVideoMode(glfwGetPrimaryMonitor())->height / 2) - (height / 2);
	glfwSetWindowPos(mWindow, centerX, centerY);

	glfwMakeContextCurrent(mWindow);

	glfwSwapInterval(1);

	GLenum err = glewInit();
	if(err)
	{
		fmt::print(stderr, "Failed to initialize glew - {}\n", glewGetErrorString(err));
		exit(-1);
	}
}

Display::~Display()
{
	glfwDestroyWindow(mWindow);
	glfwTerminate();
}

void Display::swap()
{
	glfwSwapBuffers(mWindow);
	glfwPollEvents();
}

void Display::clear(ubyte red, ubyte green, ubyte blue)
{
	glClearColor(red / 255.0f, green / 255.0f, blue / 255.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

bool Display::isClosed()
{
	return glfwWindowShouldClose(mWindow);
}
