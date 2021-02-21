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
// File Name: Common.h
// Date File Created: 02/21/2021 at 3:06 PM
// Author: Matt
// 
// ------------------------------------------------------------------------------

#pragma once

#if defined(WIN32) || defined(WIN64) || defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
#define OS_WINDOWS
#elif defined(macintosh) || defined(Macintosh) || defined(__APPLE__) || defined(__MACH__)
#define OS_APPLE
#elif defined(__unix__) || defined(__unix) || defined(__linux__) || defined(linux) || defined(__linux)
#define OS_UNIX
#else
#define OS_OTHER
#endif // OS Check

#define STR(x) #x
#define STR_EXPANDED(x) STR(x)

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

typedef unsigned char ubyte;

#include <vector>
#include <memory>

template <typename T>
using list = std::vector<T>;

template <typename T>
using UniquePtr = std::unique_ptr<T>;

template <typename T>
using Scope = std::unique_ptr<T>;

template <typename T>
using SharedPtr = std::shared_ptr<T>;

template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T, typename... Args>
constexpr UniquePtr<T> createScope(Args&& ... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T, typename... Args>
constexpr SharedPtr<T> createRef(Args&& ... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}