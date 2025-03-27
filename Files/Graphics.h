#pragma once
/*
* THIS OBJECT SERVES AS A GRAPHICS ENGINE
* I WOULD RECOMMEND INCLUDING IT, AS THIS LIBRARY IS DESIGNED WITH USING IT IN MIND
*/

//TODO:clean this code up, I don't need 200 line long code when
//		I can separate the code like this

//TODO: for that matter just improve legibility sometime.

#ifndef WINDOWS_GRAPHICS_HEADERS
#define WINDOWS_GRAPHICS_HEADERS
#include <Windows.h>
#include <d2d1.h>
#endif

#include "GlobalData.h"

#define GRAPHICS_COLOR_DEFAULT			1.0f, 1.0f, 1.0f, 1.0f
#define GRAPHICS_LINEWEIGHT_DEFAULT		3.0f
#define GRAPHICS_ROTATION_DEFAULT		//TODO: set this up

//TODO: bitmap functionality

class Graphics
{
private:
	ID2D1Factory* factory_;		//creates necessary object
	ID2D1HwndRenderTarget* renderTarget_;	//the target that is being drawn on
	ID2D1SolidColorBrush* brush_;			//the color being used
	ID2D1StrokeStyle* style_;			//line style that is being used
	//ID2D1Bitmap* bitmap_;
	//ID2D1BitmapBrush* bitmapBrush_;				//bitmap 
	HWND hWnd_; //exists to get what hWnd the class is initialized to
public:
	//default constructor & destructors
	Graphics();
	~Graphics();
	//initialize graphics
	bool Init(const HWND hWnd);
	//drawing functions
	void BeginDraw() { renderTarget_->BeginDraw(); };
	void EndDraw() { renderTarget_->EndDraw(); };
	//drawing wrappers
	void SetBrush(float r, float g, float b, float a);
	void SetTransform(D2D1_MATRIX_3X2_F transform);
	void ClearScreen(float r, float g, float b);
	void FillEllipse(D2D1_ELLIPSE* ellipse);
	void FillRect(D2D1_RECT_F* rect);
	void DrawCircle(float x, float y, float radius);
	void DrawEllipse(D2D1_ELLIPSE* ellipse);
	void DrawSquare(float x, float y, float sideLength);
	void DrawRect(D2D1_RECT_F* rect);
	void DrawRect(float x, float y, float baseLength, float sideLength);
	void DrawRect(D2D1_POINT_2F topLeft, D2D1_POINT_2F bottomRight);
	void DrawLine(float x1, float y1, float x2, float y2);
	void DrawLine(D2D1_POINT_2F point1, D2D1_POINT_2F point2);
	void DrawLine(GraphicsData::LINE line);
	void DrawDrawData(GraphicsData::DRAW_DATA drawData);
	//gets
	HWND getHWnd() { return hWnd_; };
};

