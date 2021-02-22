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

#include "Sorting.h"

#include <gl/freeglut.h>


constexpr int N = 320;
int heights[ N ];

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

	HeapSorter<int, N> heap(heights);
	heap.sort();
	heap.printInfo();
	SLP(500);

	QuickSorter<int, N> quick(heights);
	quick.sort(0, N - 1);
	quick.printInfo();
	SLP(500);

	MergeSorter<int, N> merge(heights);
	merge.sort(0, N - 1);
	merge.printInfo();
	SLP(500);

	ShellSorter<int, N> shell(heights, 2);
	shell.sort();
	shell.printInfo();
	SLP(500);

	SelectionSorter<int, N> selection(heights, 10);
	selection.sort();
	selection.printInfo();
	SLP(500);
	system("pause");
}

void visualize(int* arr)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.f, 0.f, 0.f);

	for (int i = 0; i < N; i++)
	{
		glRecti(4 * i, 100, 4 * i + 3, 100 + arr[ i ]);
	}

	glFlush();
}
