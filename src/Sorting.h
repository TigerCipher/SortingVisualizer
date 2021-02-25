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
#include <iostream>
#include <string>
#include <queue>
#include <vector>

class Sorter
{
public:
	Sorter(std::string name, const std::vector<int>& start, const int slp = 5) :
		mName(std::move(name)),
		mSleep(slp)
	{
		for (auto i : start)
		{
			mStartingArray.push_back(i);
		}
	}

	void printInfo() const
	{
		// TODO count up number of total iterations
		std::cout << mName << " - Compares: " << mCompares << " - Swaps: " << mSwaps << " - Total time: " << mTime << " ms" <<
				"\n";
	}

	std::queue<std::vector<int>>& getQueue()
	{
		return mQueue;
	}

	[[nodiscard]] int getSleep() const { return mSleep; }

protected:

	int getMax();

	int getMin();

	std::string mName;
	std::vector<int> mStartingArray;
	int mSleep;
	int mCompares = 0;
	int mSwaps = 0;
	float mTime = 0;
	std::queue<std::vector<int>> mQueue;
};

class HeapSorter : public Sorter
{
public:
	HeapSorter(const std::vector<int>& arr, int slp = 5) : Sorter("Heap Sort", arr, slp) {}

	void sort();

private:
	void heapify(const int n, int i);
};


class QuickSorter : public Sorter
{
public:
	QuickSorter(const std::vector<int>& arr, int slp = 5) : Sorter("Quick Sort", arr, slp) {}

	void sort(int low, int high);

private:
	int partition(int low, int high);
};


class MergeSorter : public Sorter
{
public:
	MergeSorter(const std::vector<int>& arr, int slp = 5) : Sorter("Merge Sort", arr, slp) {}

	void sort(int left, int right);

private:
	void merge(int left, int mid, int right);
};


class ShellSorter : public Sorter
{
public:
	ShellSorter(const std::vector<int>& arr, int slp = 5) : Sorter("Shell Sort", arr, slp) {}

	void sort();
};


class SelectionSorter : public Sorter
{
public:
	SelectionSorter(const std::vector<int>& arr, int slp = 5) : Sorter("Selection Sort", arr, slp) {}

	void sort();
};


class BubbleSorter : public Sorter
{
public:
	BubbleSorter(const std::vector<int>& arr, int slp = 5) : Sorter("Bubble Sort", arr, slp) {}

	void sort();
};

class InsertionSorter : public Sorter
{
public:
	InsertionSorter(const std::vector<int>& arr, int slp = 5) : Sorter("Insertion Sort", arr, slp) {}

	void sort();
};


class CountSorter : public Sorter
{
public:
	CountSorter(const std::vector<int>& arr, int slp = 5) : Sorter("Count Sort", arr, slp) {}

	void sort();
};


class RadixSorter : public Sorter
{
public:
	RadixSorter(const std::vector<int>& arr, int slp = 5) : Sorter("Radix Sort", arr, slp) {}

	void sort();

private:

	void countSort(int exp);
};


// TODO: Comb sort, pigeonhole sort, maybe bucket sort
