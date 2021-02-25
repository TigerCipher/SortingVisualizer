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
// File Name: Timer.cpp
// Date File Created: 02/24/2021 at 10:05 PM
// Author: Matt
// 
// ------------------------------------------------------------------------------

#include "Timer.h"


float Timer::elapsed() const
{
	//auto msdur = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - mLast);
	return std::chrono::duration<float>(std::chrono::steady_clock::now() - mLast).count() * 1000;
}

