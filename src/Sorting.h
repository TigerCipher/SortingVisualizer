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
#include <string>
#include <iostream>
#include <gl/freeglut.h>
#include <ctime>

#if defined(_WIN64) || defined(_WIN32)
	#include <Windows.h>
	#define SLP(x) //slp(x)// Sleep(x)
#else
	#include <unistd.h>
	#define SLP(x) sleep(x)
#endif

void slp(clock_t wait)
{
	clock_t goal;
	goal = wait + clock();
	while(goal > clock());
}

template <typename T, int N>
class Sorter
{
public:
	Sorter(std::string name, T arr[ N ], const int slp = 5) :
		mName(std::move(name)),
		mSleep(slp)
	{
		for (auto i = 0; i < N; i++)
		{
			mArr[ i ] = arr[ i ];
		}
	}

	void printInfo() const
	{
		std::cout << mName << " - Compares: " << mCompares << " - Swaps: " << mSwaps << "\n";
	}

protected:


	static void drawText(const float x, const float y, const std::string& txt)
	{
		glColor3f(1, 1, 1);
		glRasterPos2f(x, y);

		for (auto i : txt)
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, i);
		}
	}

	void drawStep()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		drawText(5, 700, mName);
		drawText(5, 680, "Compares: " + std::to_string(mCompares));
		drawText(5, 660, "Swaps: " + std::to_string(mSwaps));
		drawText(5, 640, "Sleep: " + std::to_string(mSleep) + " ms");

		glColor3f(1.f, 0.f, 0.f);

		for (auto i = 0; i < N; i++)
		{
			glRecti(4 * i, 100, 4 * i + 3, 100 + mArr[ i ]);
		}

		glFlush();
		SLP(mSleep);
	}

	std::string mName;
	int mSleep;
	int mCompares = 0;
	int mSwaps = 0;

	T mArr[ N ];
};

template <typename T, int N>
class HeapSorter : public Sorter<T, N>
{
	using Sorter<T, N>::drawStep;
	using Sorter<T, N>::mSwaps;
	using Sorter<T, N>::mCompares;
	using Sorter<T, N>::mArr;
	using Sorter<T, N>::mName;
public:
	HeapSorter(T arr[ N ], int slp = 5) : Sorter<T, N>("Heap Sort", arr, slp) {}

	void sort()
	{
		for (int i = N / 2 - 1; i >= 0; i--)
		{
			heapify(N, i);
		}


		for (int i = N - 1; i > 0; i--)
		{
			std::swap(mArr[ 0 ], mArr[ i ]);
			mSwaps++;
			drawStep();
			heapify(i, 0);
		}
	}

private:
	void heapify(const int n, int i)
	{
		int largest = i;
		int left = 2 * i + 1;
		int right = 2 * i + 2;

		++mCompares;
		if (left < n && mArr[ left ] > mArr[ largest ])
		{
			largest = left;
		}

		++mCompares;
		if (right < n && mArr[ right ] > mArr[ largest ])
		{
			largest = right;
		}

		if (largest != i)
		{
			std::swap(mArr[ i ], mArr[ largest ]);
			++mSwaps;
			drawStep();
			heapify(n, largest);
		}
	}
};


template <typename T, int N>
class QuickSorter : public Sorter<T, N>
{
	using Sorter<T, N>::drawStep;
	using Sorter<T, N>::mSwaps;
	using Sorter<T, N>::mCompares;
	using Sorter<T, N>::mArr;
	using Sorter<T, N>::mName;

public:
	QuickSorter(T arr[ N ], int slp = 5) : Sorter<T, N>("Quick Sort", arr, slp) {}

	void sort(int low, int high)
	{
		mCompares++;
		if (low < high)
		{
			const int partIndex = partition(low, high);
			sort(low, partIndex - 1);
			sort(partIndex + 1, high);
		}
	}

private:
	int partition(int low, int high)
	{
		T pivot = mArr[ high ];
		int i = low - 1;

		for (int j = low; j <= high - 1; j++)
		{
			mCompares++;
			if (mArr[ j ] < pivot)
			{
				i++;
				std::swap(mArr[ i ], mArr[ j ]);
				mSwaps++;
				drawStep();
			}
		}

		std::swap(mArr[ i + 1 ], mArr[ high ]);
		mSwaps++;
		drawStep();
		return i + 1;
	}
};

template <typename T, int N>
class MergeSorter : public Sorter<T, N>
{
	using Sorter<T, N>::drawStep;
	using Sorter<T, N>::mSwaps;
	using Sorter<T, N>::mCompares;
	using Sorter<T, N>::mArr;
	using Sorter<T, N>::mName;

public:
	MergeSorter(T arr[ N ], int slp = 5) : Sorter<T, N>("Merge Sort", arr, slp) {}

	void sort(int left, int right)
	{
		mCompares++;
		if (left >= right) { return; }
		int mid = left + (right - left) / 2;
		sort(left, mid);
		sort(mid + 1, right);
		merge(left, mid, right);
	}

private:
	void merge(int left, int mid, int right)
	{
		const int n1 = mid - left + 1;
		const int n2 = right - mid;

		T* larr = new T[ n1 ];
		T* rarr = new T[ n2 ];

		for (int i = 0; i < n1; i++)
		{
			larr[ i ] = mArr[ left + i ];
		}

		for (int i = 0; i < n2; i++)
		{
			rarr[ i ] = mArr[ mid + 1 + i ];
		}

		int i = 0, j = 0;
		int k = left;

		mCompares++; // Accounts for when the while loop doesn't meet the condition as well
		while (i < n1 && j < n2)
		{
			mCompares += 2; // increments for both the while and the if
			if (larr[ i ] <= rarr[ j ])
			{
				mArr[ k ] = larr[ i ];
				i++;
				mSwaps++;
				drawStep();
			}
			else
			{
				mArr[ k ] = rarr[ j ];
				j++;
				mSwaps++;
				drawStep();
			}

			k++;
		}

		mCompares++;
		while (i < n1)
		{
			mCompares++;
			mArr[ k ] = larr[ i ];
			i++;
			k++;
			mSwaps++;
			drawStep();
		}

		mCompares++;
		while (j < n2)
		{
			mCompares++;
			mArr[ k ] = rarr[ j ];
			j++;
			k++;
			mSwaps++;
			drawStep();
		}

		delete[] larr;
		delete[] rarr;
	}
};


template<typename T, int N>
class ShellSorter : public Sorter<T, N>
{
	using Sorter<T, N>::drawStep;
	using Sorter<T, N>::mSwaps;
	using Sorter<T, N>::mCompares;
	using Sorter<T, N>::mArr;
	using Sorter<T, N>::mName;

public:
	ShellSorter(T arr[N], int slp = 5) : Sorter<T, N>("Shell Sort", arr, slp) {}

	void sort()
	{
		for (int gap = N / 2; gap > 0; gap /= 2)
		{
			for (int i = gap; i < N; i++)
			{
				int temp = mArr[i];
				int j;
				mCompares++;
				for (j = i; j >= gap && mArr[j - gap] > temp; j -= gap)
				{
					mCompares++;
					mArr[j] = mArr[j - gap];
					mSwaps++;
					drawStep();
				}
				mArr[j] = temp;
				mSwaps++;
				drawStep();
			}
		}
	}
};


template<typename T, int N>
class SelectionSorter : public Sorter<T, N>
{
	using Sorter<T, N>::drawStep;
	using Sorter<T, N>::mSwaps;
	using Sorter<T, N>::mCompares;
	using Sorter<T, N>::mArr;
	using Sorter<T, N>::mName;

public:
	SelectionSorter(T arr[N], int slp = 5) : Sorter<T, N>("Selection Sort", arr, slp) {}

	void sort()
	{
		for (int i = 0; i < N - 1; i++)
		{
			int minIndex = i;
			for (int j = i + 1; j < N; j++)
			{
				mCompares++;
				if (mArr[j] < mArr[minIndex])
					minIndex = j;
			}
			std::swap(mArr[minIndex], mArr[i]);
			mSwaps++;
			drawStep();
		}
	}
};
