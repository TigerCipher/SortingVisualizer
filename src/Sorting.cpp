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
// File Name: Sorting.cpp
// Date File Created: 02/24/2021 at 8:56 PM
// Author: Matt
// 
// ------------------------------------------------------------------------------

#include "Sorting.h"
#include "Timer.h"


int Sorter::getMax()
{
	int mx = mStartingArray[ 0 ];
	mIts++;
	for (int i = 1; i < mStartingArray.size(); i++)
	{
		mIts++;
		++mCompares;
		if (mStartingArray[ i ] > mx)
		{
			mx = mStartingArray[ i ];
		}
	}

	return mx;
}

int Sorter::getMin()
{
	mIts++;
	int mx = mStartingArray[ 0 ];
	for (int i = 1; i < mStartingArray.size(); i++)
	{
		mIts++;
		++mCompares;
		if (mStartingArray[ i ] < mx)
		{
			mx = mStartingArray[ i ];
		}
	}

	return mx;
}

void HeapSorter::sort()
{
	mIts++;
	Timer t;
	for (int i = mStartingArray.size() / 2 - 1; i >= 0; i--)
	{
		mIts++;
		heapify(mStartingArray.size(), i);
	}


	for (int i = mStartingArray.size() - 1; i > 0; --i)
	{
		mIts++;
		std::swap(mStartingArray[ 0 ], mStartingArray[ i ]);
		++mSwaps;
		mQueue.push(mStartingArray);
		heapify(i, 0);
	}

	mTime = t.elapsed();
}

void HeapSorter::heapify(const int n, int i)
{
	mIts++;
	auto largest = i;
	auto left = 2 * i + 1;
	auto right = 2 * i + 2;

	++mCompares;
	if (left < n && mStartingArray[ left ] > mStartingArray[ largest ])
	{
		largest = left;
	}

	++mCompares;
	if (right < n && mStartingArray[ right ] > mStartingArray[ largest ])
	{
		largest = right;
	}

	if (largest != i)
	{
		std::swap(mStartingArray[ i ], mStartingArray[ largest ]);
		++mSwaps;
		mQueue.push(mStartingArray);
		heapify(n, largest);
	}
}


void QuickSorter::sort(int low, int high)
{
	mIts++;
	Timer t;
	mCompares++;
	if (low < high)
	{
		const int partIndex = partition(low, high);
		sort(low, partIndex - 1);
		sort(partIndex + 1, high);
	}
	mTime = t.elapsed();
}


int QuickSorter::partition(int low, int high)
{
	mIts++;
	int pivot = mStartingArray[ high ];
	int i = low - 1;

	for (int j = low; j <= high - 1; j++)
	{
		mIts++;
		mCompares++;
		if (mStartingArray[ j ] < pivot)
		{
			i++;
			std::swap(mStartingArray[ i ], mStartingArray[ j ]);
			mSwaps++;
			mQueue.push(mStartingArray);
		}
	}

	std::swap(mStartingArray[ i + 1 ], mStartingArray[ high ]);
	mSwaps++;
	mQueue.push(mStartingArray);
	return i + 1;
}


void MergeSorter::sort(int left, int right)
{
	mIts++;
	Timer t;
	mCompares++;
	if (left >= right) { return; }
	int mid = left + (right - left) / 2;
	sort(left, mid);
	sort(mid + 1, right);
	merge(left, mid, right);
	mTime = t.elapsed();
}


void MergeSorter::merge(int left, int mid, int right)
{
	mIts++;
	const int n1 = mid - left + 1;
	const int n2 = right - mid;

	int* larr = new int[ n1 ];
	int* rarr = new int[ n2 ];

	for (int i = 0; i < n1; i++)
	{
		mIts++;
		larr[ i ] = mStartingArray[ left + i ];
	}

	for (int i = 0; i < n2; i++)
	{
		mIts++;
		rarr[ i ] = mStartingArray[ mid + 1 + i ];
	}

	int i = 0, j = 0;
	int k = left;

	mCompares++; // Accounts for when the while loop doesn't meet the condition as well
	while (i < n1 && j < n2)
	{
		mIts++;
		mCompares += 2; // increments for both the while and the if
		if (larr[ i ] <= rarr[ j ])
		{
			mStartingArray[ k ] = larr[ i ];
			i++;
			mSwaps++;
			mQueue.push(mStartingArray);
		}
		else
		{
			mStartingArray[ k ] = rarr[ j ];
			j++;
			mSwaps++;
			mQueue.push(mStartingArray);
		}

		k++;
	}

	mCompares++;
	while (i < n1)
	{
		mIts++;
		mCompares++;
		mStartingArray[ k ] = larr[ i ];
		i++;
		k++;
		mSwaps++;
		mQueue.push(mStartingArray);
	}

	mCompares++;
	while (j < n2)
	{
		mIts++;
		mCompares++;
		mStartingArray[ k ] = rarr[ j ];
		j++;
		k++;
		mSwaps++;
		mQueue.push(mStartingArray);
	}

	delete[] larr;
	delete[] rarr;
}

void ShellSorter::sort()
{
	mIts++;
	Timer t;
	for (int gap = mStartingArray.size() / 2; gap > 0; gap /= 2)
	{
		mIts++;
		for (int i = gap; i < mStartingArray.size(); i++)
		{
			mIts++;
			int temp = mStartingArray[ i ];
			int j;
			mCompares++;
			for (j = i; j >= gap && mStartingArray[ j - gap ] > temp; j -= gap)
			{
				mIts++;
				mCompares++;
				mStartingArray[ j ] = mStartingArray[ j - gap ];
				mSwaps++;
				mQueue.push(mStartingArray);
			}
			mStartingArray[ j ] = temp;
			mSwaps++;
			mQueue.push(mStartingArray);
		}
	}
	mTime = t.elapsed();
}

void SelectionSorter::sort()
{
	mIts++;
	Timer t;
	for (int i = 0; i < mStartingArray.size() - 1; i++)
	{
		mIts++;
		int minIndex = i;
		for (int j = i + 1; j < mStartingArray.size(); j++)
		{
			mIts++;
			mCompares++;
			if (mStartingArray[ j ] < mStartingArray[ minIndex ])
				minIndex = j;
		}
		std::swap(mStartingArray[ minIndex ], mStartingArray[ i ]);
		mSwaps++;
		mQueue.push(mStartingArray);
	}
	mTime = t.elapsed();
}

void BubbleSorter::sort()
{
	mIts++;
	Timer t;
	for (auto i = 0; i < mStartingArray.size() - 1; i++)
	{
		mIts++;
		bool swapped = false;
		for (auto j = 0; j < mStartingArray.size() - i - 1; j++)
		{
			mIts++;
			++mCompares;
			if (mStartingArray[ j ] > mStartingArray[ j + 1 ])
			{
				std::swap(mStartingArray[ j ], mStartingArray[ j + 1 ]);
				++mSwaps;
				swapped = true;
				mQueue.push(mStartingArray);
			}
		}

		if (!swapped)
		{
			break;
		}
	}
	mTime = t.elapsed();
}

void InsertionSorter::sort()
{
	mIts++;
	Timer t;
	for (int i = 0; i < mStartingArray.size(); i++)
	{
		mIts++;
		int key = mStartingArray[ i ];
		int j = i - 1;

		++mCompares;
		while (j >= 0 && mStartingArray[ j ] > key)
		{
			mIts++;
			++mCompares;
			mStartingArray[ j + 1 ] = mStartingArray[ j ];
			--j;
			++mSwaps;
			mQueue.push(mStartingArray);
		}

		mStartingArray[ j + 1 ] = key;
		++mSwaps;
		mQueue.push(mStartingArray);
	}
	mTime = t.elapsed();
}

void CountSorter::sort()
{
	mIts++;
	Timer t;
	int* output = new int[ mStartingArray.size() ];
	int min = getMin();
	int max = getMax();
	const int range = max - min + 1;

	int i;
	int* count = new int[ range ] { 0 };

	for (i = 0; i < mStartingArray.size(); i++)
	{
		mIts++;
		++count[ mStartingArray[ i ] - min ];
	}

	for (i = 1; i < range; i++)
	{
		mIts++;
		count[ i ] += count[ i - 1 ];
	}

	for (i = mStartingArray.size() - 1; i >= 0; i--)
	{
		mIts++;
		output[ count[ mStartingArray[ i ] - min ] - 1 ] = mStartingArray[ i ];
		--count[ mStartingArray[ i ] - min ];
	}

	for (i = 0; i < mStartingArray.size(); i++)
	{
		mIts++;
		mStartingArray[ i ] = output[ i ];
		++mSwaps;
		mQueue.push(mStartingArray);
	}


	delete[] output;
	delete[] count;
	mTime = t.elapsed();
}

void RadixSorter::sort()
{
	mIts++;
	Timer t;
	int m = getMax();

	for (int exp = 1; m / exp > 0; exp *= 10)
	{
		mIts++;
		countSort(exp);
	}
	mTime = t.elapsed();
}

void RadixSorter::countSort(int exp)
{
	int* output = new int[ mStartingArray.size() ];
	int i;
	int count[ 10 ] = {};

	for (i = 0; i < mStartingArray.size(); i++)
	{
		mIts++;
		++count[ (mStartingArray[ i ] / exp) % 10 ];
	}

	for (i = 1; i < 10; i++)
	{
		mIts++;
		count[ i ] += count[ i - 1 ];
	}

	for (i = mStartingArray.size() - 1; i >= 0; i--)
	{
		mIts++;
		output[ count[ (mStartingArray[ i ] / exp) % 10 ] - 1 ] = mStartingArray[ i ];
		--count[ (mStartingArray[ i ] / exp) % 10 ];
	}

	for (i = 0; i < mStartingArray.size(); i++)
	{
		mIts++;
		mStartingArray[ i ] = output[ i ];
		++mSwaps;
		mQueue.push(mStartingArray);
	}


	delete[] output;
}
