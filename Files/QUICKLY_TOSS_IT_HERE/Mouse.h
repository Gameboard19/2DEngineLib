#pragma once

#ifndef WINDOWS_GRAPHICS_HEADERS
#define WINDOWS_GRAPHICS_HEADERS
#include <Windows.h>
#include <d2d1.h>
#endif


class Mouse
{
private:
	D2D1_POINT_2F pos;
public:
	D2D1_POINT_2F getPos() { return pos; };
};

