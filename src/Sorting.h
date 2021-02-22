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
// File Name: Sorting.h
// Date File Created: 02/21/2021 at 6:07 PM
// Author: Matt
// 
// ------------------------------------------------------------------------------

#pragma once
#include <array>
#include <algorithm>
#include "Common.h"

template <typename T>
bool heap_smallest_to_largest(T lvalue, T rvalue)
{
	return lvalue > rvalue;
}

template <typename T>
bool heap_largest_to_smallest(T lvalue, T rvalue)
{
	return lvalue < rvalue;
}

template <typename T>
bool quick_smallest_to_largest(T lvalue, T rvalue)
{
	return lvalue < rvalue;
}

template <typename T>
bool quick_largest_to_smallest(T lvalue, T rvalue)
{
	return lvalue > rvalue;
}

template <typename T>
bool merge_smallest_to_largest(T lvalue, T rvalue)
{
	return lvalue <= rvalue;
}

template <typename T>
bool merge_largest_to_smallest(T lvalue, T rvalue)
{
	return lvalue >= rvalue;
}

template <typename T>
void heapify(T arr[ ], int n, int i, bool func(T, T), void drawFunc(T*), int& compares, int& swaps)
{
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	compares++;
	if (left < n && func(arr[ left ], arr[ largest ]))
	{
		largest = left;
	}

	compares++;
	if (right < n && func(arr[ right ], arr[ largest ]))
	{
		largest = right;
	}

	if (largest != i)
	{
		std::swap(arr[ i ], arr[ largest ]);
		swaps++;
		heapify(arr, n, largest, func, drawFunc, compares, swaps);
		drawFunc(arr);
	}
}


template <typename T>
void heap_sort(T arr[ ], int n, bool func(T, T), void drawFunc(T*), int& compares, int& swaps)
{
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		heapify(arr, n, i, func, drawFunc, compares, swaps);
	}


	for (int i = n - 1; i > 0; i--)
	{
		std::swap(arr[ 0 ], arr[ i ]);
		swaps++;
		heapify(arr, i, 0, func, drawFunc, compares, swaps);
	}
}

template <typename T>
int partition(T arr[ ], int low, int high, bool func(T, T), void drawFunc(T*), int& compares, int& swaps)
{
	T pivot = arr[ high ];
	int i = low - 1;

	for (int j = low; j <= high - 1; j++)
	{
		compares++;
		if (func(arr[ j ], pivot))
		{
			i++;
			std::swap(arr[ i ], arr[ j ]);
			swaps++;
			drawFunc(arr);
		}
	}

	std::swap(arr[ i + 1 ], arr[ high ]);
	swaps++;
	drawFunc(arr);
	return i + 1;
}

template <typename T>
void quick_sort(T arr[ ], int low, int high, bool func(T, T), void drawFunc(T*), int& compares, int& swaps)
{
	compares++;
	if (low < high)
	{
		int partIndex = partition(arr, low, high, func, drawFunc, compares, swaps);
		quick_sort(arr, low, partIndex - 1, func, drawFunc, compares, swaps);
		quick_sort(arr, partIndex + 1, high, func, drawFunc, compares, swaps);
	}
}

template <typename T>
void merge(T arr[ ], int left, int mid, int right, bool func(T, T), void drawFunc(T*), int& compares, int& swaps)
{
	const int n1 = mid - left + 1;
	const int n2 = right - mid;

	T* larr = new T[ n1 ];
	T* rarr = new T[ n2 ];

	for (int i = 0; i < n1; i++)
	{
		larr[ i ] = arr[ left + i ];
	}

	for (int i = 0; i < n2; i++)
	{
		rarr[ i ] = arr[ mid + 1 + i ];
	}

	int i = 0, j = 0;
	int k = left;

	while (i < n1 && j < n2)
	{
		compares += 2; // increments for both the while and the if
		if (func(larr[ i ], rarr[ j ]))
		{
			arr[ k ] = larr[ i ];
			i++;
			swaps++;
			drawFunc(arr);
		}
		else
		{
			arr[ k ] = rarr[ j ];
			j++;
			swaps++;
			drawFunc(arr);
		}

		k++;
	}

	while (i < n1)
	{
		compares++;
		arr[ k ] = larr[ i ];
		i++;
		k++;
		swaps++;
		drawFunc(arr);
	}

	while (j < n2)
	{
		compares++;
		arr[ k ] = rarr[ j ];
		j++;
		k++;
		swaps++;
		drawFunc(arr);
	}

	delete[] larr;
	delete[] rarr;
}

template <typename T>
void merge_sort(T arr[ ], int left, int right, bool func(T, T), void drawFunc(T*), int& compares, int& swaps)
{
	compares++;
	if (left >= right) { return; }
	int mid = left + (right - left) / 2;
	merge_sort(arr, left, mid, func, drawFunc, compares, swaps);
	merge_sort(arr, mid + 1, right, func, drawFunc, compares, swaps);
	merge(arr, left, mid, right, func, drawFunc, compares, swaps);
}

template <typename T>
void shell_sort(T arr[ ], int n, void drawFunc(T*), int& compares, int& swaps)
{
	for (int gap = n / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < n; i++)
		{
			int temp = arr[ i ];
			int j;
			for (j = i; j >= gap && arr[ j - gap ] > temp; j -= gap)
			{
				compares++;
				arr[ j ] = arr[ j - gap ];
				swaps++;
				drawFunc(arr);
			}
			arr[ j ] = temp;
			swaps++;
			drawFunc(arr);
		}
	}
}


template <typename T>
void selection_sort(T arr[ ], int n, void drawFunc(T*), int& compares, int& swaps)
{
	int minIndex;
	for (int i = 0; i < n - 1; i++)
	{
		minIndex = i;
		for (int j = i + 1; j < n; j++)
		{
			compares++;
			if (arr[ j ] < arr[ minIndex ])
				minIndex = j;
		}
		std::swap(arr[ minIndex ], arr[ i ]);
		swaps++;
		drawFunc(arr);
	}
}
