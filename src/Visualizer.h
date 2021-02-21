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
// File Name: Visualizer.h
// Date File Created: 02/21/2021 at 3:24 PM
// Author: Matt
// 
// ------------------------------------------------------------------------------

#pragma once

#include "Common.h"


class Visualizer
{
public:
	Visualizer();
	
	void draw();

private:
	UniquePtr<class Shader> mShader;
	list<class Line> mLines;
};

class Line
{
public:
	Line(float x1, float y1, float x2, float y2);

	void bind() const;
	void draw() const;

private:
	uint mVao {};
	uint mVbo {};
};

class Shader
{
public:
	Shader(const char* vert, const char* frag);
	virtual ~Shader();

	void bind();

private:
	uint mProgram;
};
