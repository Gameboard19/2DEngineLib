#pragma once

#ifndef WINDOWS_GRAPHICS_HEADERS
#define WINDOWS_GRAPHICS_HEADERS
#include <Windows.h>
#include <d2d1.h>
#endif

//I might just change this and just have you use a D2D1_POINT_2F as a mouse. TBD if I actually do that
class Mouse
{
private:
	D2D1_POINT_2F pos;
public:
	D2D1_POINT_2F getPos() { return pos; };
};

