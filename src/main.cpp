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


#include <iostream>
#include <string>

#include "Sorting.h"

#include <gl/glut.h>


#ifdef OS_WINDOWS
	#include <Windows.h>
	#define SLP(x) Sleep(x)
#else
	#include <unistd.h>
	#define SLP(x) sleep(x)
#endif


constexpr int N = 320;
int heights[ N ];
int gCompares = 0;
int gSwaps = 0;
int gSleepFor = 5;
std::string gSort;

void gfx();
void visualize(int* arr);

int main(int argc, char** argv)
{
	for (int i = 0; i < N; i++)
	{
		heights[ i ] = rand() % 600;
	}

	glutInit(&argc, argv);
	glutInitWindowSize(1280, 720);
	int cx = (glutGet(GLUT_SCREEN_WIDTH) - 1280) / 2;
	int cy = (glutGet(GLUT_SCREEN_HEIGHT) - 720) / 2;
	glutInitWindowPosition(cx, cy);
	glutCreateWindow("Sorting Visualizer");
	glutDisplayFunc(gfx);
	glClearColor(0, 0, 0, 1);
	gluOrtho2D(0, 1280, 0, 720);
	glutMainLoop();
	return 0;
}

void gfx()
{
	glClear(GL_COLOR_BUFFER_BIT);

	visualize(heights);
	SLP(500);

	int arr[ N ];
	for (auto i = 0; i < N; i++)
	{
		arr[ i ] = heights[ i ];
	}

	gCompares = 0;
	gSwaps = 0;
	gSleepFor = 5;
	gSort = "Quick Sort";
	
	quick_sort(arr, 0, N - 1, quick_smallest_to_largest, visualize, gCompares, gSwaps);
	std::cout << gSort << " - " << gCompares << " compares and " << gSwaps << " swaps\n";
	SLP(500);

	gCompares = 0;
	gSwaps = 0;
	gSort = "Merge Sort";
	gSleepFor = 5;
	for (auto i = 0; i < N; i++)
	{
		arr[i] = heights[i];
	}
	merge_sort(arr, 0, N - 1, merge_smallest_to_largest, visualize, gCompares, gSwaps);
	std::cout << gSort << " - " << gCompares << " compares and " << gSwaps << " swaps\n";
	SLP(500);

	gCompares = 0;
	gSwaps = 0;
	gSort = "Heap Sort";
	gSleepFor = 5;
	for (auto i = 0; i < N; i++)
	{
		arr[i] = heights[i];
	}
	heap_sort(arr, N, heap_smallest_to_largest, visualize, gCompares, gSwaps);
	std::cout << gSort << " - " << gCompares << " compares and " << gSwaps << " swaps\n";
	SLP(500);

	gCompares = 0;
	gSwaps = 0;
	gSort = "Shell Sort";
	gSleepFor = 2;
	for (auto i = 0; i < N; i++)
	{
		arr[i] = heights[i];
	}
	shell_sort(arr, N, visualize, gCompares, gSwaps);
	std::cout << gSort << " - " << gCompares << " compares and " << gSwaps << " swaps\n";
	SLP(500);

	gCompares = 0;
	gSwaps = 0;
	gSort = "Selection Sort";
	gSleepFor = 5;
	for (auto i = 0; i < N; i++)
	{
		arr[i] = heights[i];
	}
	selection_sort(arr, N, visualize, gCompares, gSwaps);
	std::cout << gSort << " - " << gCompares << " compares and " << gSwaps << " swaps\n";
	SLP(500);

}

void drawText(float x, float y, const std::string& txt)
{
	glColor3f(1, 1, 1);
	glRasterPos2f(x, y);
	int l = txt.size();
	for (int i = 0; i < l; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, txt[ i ]);
	}
}

void visualize(int* arr)
{
	glClear(GL_COLOR_BUFFER_BIT);

	drawText(100, 700, gSort);
	drawText(100, 680, "Compares: " + std::to_string(gCompares));
	drawText(100, 660, "Swaps: " + std::to_string(gSwaps));
	drawText(100, 640, "Sleep: " + std::to_string(gSleepFor) + " ms");

	glColor3f(1.f, 0.f, 0.f);

	for (int i = 0; i < N; i++)
	{
		glRecti(4 * i, 100, 4 * i + 3, 100 + arr[ i ]);
	}

	glFlush();
	SLP(gSleepFor);
}