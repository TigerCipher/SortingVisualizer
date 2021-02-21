#pragma once

#include "Common.h"

#include <string>

class Display
{
public:
	Display(std::string title, int width, int height);
	virtual ~Display();

	void swap();
	void clear(ubyte red = 0, ubyte green = 0, ubyte blue = 0);

	bool isClosed();


	[[nodiscard]] std::string title() const { return mTitle; }
	[[nodiscard]] int width() const { return mWidth; }
	[[nodiscard]] int height() const { return mHeight; }
private:
	std::string mTitle;
	int mWidth;
	int mHeight;

	class GLFWwindow* mWindow;
};