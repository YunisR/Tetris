#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow
{
	Display *d;
	Window w;
	int s;
	GC gc;
	unsigned long colours[11];

public:
	Xwindow(int width = 500, int height = 500); // Constructor; displays the window.
	~Xwindow();									// Destructor; destroys the window.
	Xwindow(const Xwindow &) = delete;
	Xwindow &operator=(const Xwindow &) = delete;

	enum
	{
		White = 0,
		Black,
		LightGrey,
		Orange,
		DarkBlue,
		LightBlue,
		Green,
		Purple,
		Red,
		Yellow,
		Browm
	}; // Available colours.

	// Draws a rectangle
	void fillRectangle(int x, int y, int width, int height, int colour = Black);

	// Draws a string
	void drawString(int x, int y, std::string msg);
};

#endif
