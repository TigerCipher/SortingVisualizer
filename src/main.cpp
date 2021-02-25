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
#include <vector>
#include <gl/freeglut.h>

#include "Sorting.h"


enum SortType
{
	NONE,
	DONE,
	HEAP,
	QUICK,
	MERGE,
	BUBBLE,
	SELECTION,
	INSERT,
	RADIX,
	COUNT,
	SHELL
};

constexpr int N = 320;

std::vector<int> gHeights;
std::vector<int> gDrawArray;
SortType gSortType = NONE;

Sorter* gSorter;

void gfx();
void on_key(unsigned char key, int x, int y);
void visualize(int* arr);
void update(int status);
void clean_up();

int main(int argc, char** argv)
{
	std::cout << "Press the following keys to start a sort:\n"
			"r - Reset the array\n"
			"1 - Heap Sort\n"
			"2 - Quick Sort\n"
			"3 - Merge Sort\n"
			"4 - Bubble Sort\n"
			"5 - Selection Sort\n"
			"6 - Insertion Sort\n"
			"7 - Radix Sort\n"
			"8 - Counting Sort\n"
			"9 - Shell Sort\n";

	for (int i = 0; i < N; i++)
	{
		gHeights.push_back(rand() % 600);
	}

	gDrawArray = gHeights;

	glutInit(&argc, argv);
	glutInitWindowSize(1280, 720);
	int cx = (glutGet(GLUT_SCREEN_WIDTH) - 1280) / 2;
	int cy = (glutGet(GLUT_SCREEN_HEIGHT) - 720) / 2;
	glutInitWindowPosition(cx, cy);
	glutCreateWindow("Sorting Visualizer");
	glutDisplayFunc(gfx);
	glutKeyboardFunc(on_key);
	glutTimerFunc(1000, update, 1);

	glClearColor(0, 0, 0, 1);
	gluOrtho2D(0, 1280, 0, 720);
	atexit(clean_up);
	glutMainLoop();
	return 0;
}

void gfx()
{
	visualize(gDrawArray.data());
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


void on_key(unsigned char key, int x, int y)
{
	if (key == 'r')
	{
		if (!gSorter)
		{
			gDrawArray = gHeights;
		}
		else
		{
			std::cerr << "Only reset the array after the current sort is finished please!\n";
		}
	}
	int k = static_cast<int>(key) - 48;
	if (k >= 1 && k <= 9)
	{
		gSortType = static_cast<SortType>(k + 1);
	}

	switch (gSortType)
	{
	case HEAP:
		{
			auto* heap = new HeapSorter(gHeights);
			heap->sort();
			heap->printInfo();
			gSorter = heap;
			gSortType = DONE;
			break;
		}
	case QUICK:
		{
			auto* quick = new QuickSorter(gHeights);
			quick->sort(0, N - 1);
			quick->printInfo();
			gSorter = quick;
			gSortType = DONE;
			break;
		}
	case MERGE:
		{
			auto* merge = new MergeSorter(gHeights);
			merge->sort(0, N - 1);
			merge->printInfo();
			gSorter = merge;
			gSortType = DONE;
			break;
		}
	case COUNT:
		{
			auto* count = new CountSorter(gHeights);
			count->sort();
			count->printInfo();
			gSorter = count;
			gSortType = DONE;
			break;
		}
	case RADIX:
		{
			auto* radix = new RadixSorter(gHeights);
			radix->sort();
			radix->printInfo();
			gSorter = radix;
			gSortType = DONE;
			break;
		}
	case INSERT:
		{
			auto* insert = new InsertionSorter(gHeights, 0);
			insert->sort();
			insert->printInfo();
			gSorter = insert;
			gSortType = DONE;
			break;
		}
	case BUBBLE:
		{
			auto* bubble = new BubbleSorter(gHeights, 1);
			bubble->sort();
			bubble->printInfo();
			gSorter = bubble;
			gSortType = DONE;
			break;
		}
	case SELECTION:
		{
			auto* selection = new SelectionSorter(gHeights, 10);
			selection->sort();
			selection->printInfo();
			gSorter = selection;
			gSortType = DONE;
			break;
		}
	case SHELL:
		{
			auto* shell = new ShellSorter(gHeights, 2);
			shell->sort();
			shell->printInfo();
			gSorter = shell;
			gSortType = DONE;
			break;
		}
	case NONE:
		{
			gDrawArray = gHeights;
			break;
		}
	}
}

void update(int status)
{
	if (gSorter && !gSorter->getQueue().empty())
	{
		gDrawArray = gSorter->getQueue().front();
		gSorter->getQueue().pop();
		glutTimerFunc(gSorter->getSleep(), update, 1);
		glutPostRedisplay();
		return;
	}
	if (gSorter && gSorter->getQueue().empty())
	{
		delete gSorter;
		gSorter = nullptr;
	}

	glutTimerFunc(5, update, 1);
	glutPostRedisplay();
}


void clean_up()
{
	std::cout << "Cleaning allocated resources\n";
	delete gSorter;
}
