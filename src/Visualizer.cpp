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
// File Name: Visualizer.cpp
// Date File Created: 02/21/2021 at 3:25 PM
// Author: Matt
// 
// ------------------------------------------------------------------------------


#include "Visualizer.h"

#include <gl/glew.h>
#include <fmt/core.h>

const char* vertex_shader_src =
	"#version 330 core\n"
	"layout (location = 0) in vec2 aPos;\n"
	"void main() {\n"
	"	gl_Position = vec4(aPos, 0.0, 1.0);\n"
	"}";

const char* frag_shader_src =
	"#version 330 core\n"
	"out vec4 fragColor;\n"
	"void main() {\n"
	"	fragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
	"}";

Visualizer::Visualizer()
{
	mShader = createScope<Shader>(vertex_shader_src, frag_shader_src);
	mLines.push_back(Line(0, 0, 1.0f, 1.0f));
	mLines.push_back(Line(-0.5f, 0, 1.0f, 1.0f));
	//for(int i = 0; i < 400; i++)
	//{
	//	mLines.push_back()
	//}
}

void Visualizer::draw()
{
	mShader->bind();
	for(const auto& l : mLines)
	{
		l.bind();
		l.draw();
	}
}


Line::Line(float x1, float y1, float x2, float y2)
{
	glGenVertexArrays(1, &mVao);
	glGenBuffers(1, &mVbo);

	glBindVertexArray(mVao);
	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	float data[] = {x1, y1, x2, y2};
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(float), data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Line::bind() const
{
	glBindVertexArray(mVao);
	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
}
void Line::draw() const
{
	glBindVertexArray(mVao);
	glLineWidth(4.0f);
	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);
}


Shader::Shader(const char* vert, const char* frag)
{
	const auto vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vert, nullptr);
	glCompileShader(vertShader);

	int success;
	char info[512];
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertShader, 512, nullptr, info);
		const auto err = fmt::format("Vertex Shader Error: {}", info);
		fmt::print(stderr, err);
		exit(-1);
	}

	const auto fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &frag, nullptr);
	glCompileShader(fragShader);

	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragShader, 512, nullptr, info);
		const auto err = fmt::format("Fragment Shader Error: {}", info);
		fmt::print(stderr, err);
		exit(-1);
	}

	mProgram = glCreateProgram();
	glAttachShader(mProgram, vertShader);
	glAttachShader(mProgram, fragShader);
	glLinkProgram(mProgram);

	glGetShaderiv(mProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(mProgram, 512, nullptr, info);
		const auto err = fmt::format("Shader Linkage Error: {}", info);
		fmt::print(stderr, err);
		exit(-1);
	}

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
}

Shader::~Shader()
{
	glDeleteProgram(mProgram);
}

void Shader::bind()
{
	glUseProgram(mProgram);
}
