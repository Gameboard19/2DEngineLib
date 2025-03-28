/* THIS FILE CONTAINS
* 
* - Graphics function definitions
* 
* FOR IN DEPTH DOCUMENTATION PLEASE SEE THE GITHUB REPO */

//TODO: github documentation
//TODO: bitmap implementation (if i do)
//TODO: implement images and gifs if able

#include "Graphics.h"

Graphics::Graphics() {
	factory_ = NULL;
	renderTarget_ = NULL;
	brush_ = NULL;
	style_ = NULL;
	//bitmap_ = NULL;
	//bitmapBrush_ = NULL;
}
Graphics::~Graphics() {
	if (factory_) factory_->Release();
	if (renderTarget_) renderTarget_->Release();
	if (brush_) brush_->Release();
	if (style_) style_->Release();
	//if (bitmapBrush_) bitmapBrush_->Release();
}
bool Graphics::Init(const HWND hWnd) {
	//create graphics factory.
	HRESULT result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory_);
	if (result != S_OK) return false;
	//get window size and pass it to rect
	RECT rect;
	GetClientRect(hWnd, &rect);
	//create render target
	result = factory_->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			hWnd,
			D2D1::SizeU(rect.right, rect.bottom)
			),
		&renderTarget_
	);
	if (result != S_OK) return false;
	//create brush and set it to default values
	result = factory_->CreateStrokeStyle(
		D2D1::StrokeStyleProperties(
			D2D1_CAP_STYLE_FLAT,
			D2D1_CAP_STYLE_FLAT,
			D2D1_CAP_STYLE_FLAT,
			D2D1_LINE_JOIN_BEVEL,
			10.0F,
			D2D1_DASH_STYLE_SOLID,
			0.0F
		),
		nullptr,
		0,
		&style_
	);
	if (result != S_OK) return false;
	result = renderTarget_->CreateSolidColorBrush(D2D1::ColorF(GRAPHICS_COLOR_DEFAULT), &brush_);
	if (result != S_OK) return false;
	//create bitmap brush
	//result = renderTarget_->CreateBitmapBrush()
	hWnd_ = hWnd;
	return true;
}
void Graphics::ClearScreen(float r, float g, float b) {
	renderTarget_->Clear(D2D1::ColorF(r, g, b));
}
void Graphics::DrawCircle(float x, float y, float radius) {
	renderTarget_->DrawEllipse(
		D2D1::Ellipse(
			D2D1::Point2F(
				x, y
			), 
			radius, 
			radius
		), 
		brush_, 
		GRAPHICS_LINEWEIGHT_DEFAULT
	);
}
void Graphics::DrawEllipse(D2D1_ELLIPSE* ellipse) {
	renderTarget_->DrawEllipse(ellipse, brush_, GRAPHICS_LINEWEIGHT_DEFAULT);
}
void Graphics::FillEllipse(D2D1_ELLIPSE* ellipse) {
	renderTarget_->FillEllipse(ellipse, brush_);
}
void Graphics::DrawRect(D2D1_RECT_F* rect) {
	renderTarget_->DrawRectangle(
		rect, 
		brush_, 
		GRAPHICS_LINEWEIGHT_DEFAULT
	);
}
void Graphics::DrawRect(float x, float y, float baseLength, float sideLength) {
	renderTarget_->DrawRectangle(
		D2D1::RectF(
			x - (baseLength / 2), 
			y - (sideLength / 2), 
			x + (baseLength / 2), 
			y + (sideLength / 2)
		), 
		brush_, 
		GRAPHICS_LINEWEIGHT_DEFAULT
	);
}
void Graphics::DrawRect(D2D1_POINT_2F topLeft, D2D1_POINT_2F bottomRight) {
	renderTarget_->DrawRectangle(
		D2D1::RectF(
			topLeft.x, 
			topLeft.y, 
			bottomRight.x, 
			bottomRight.y
		), 
		brush_, 
		GRAPHICS_LINEWEIGHT_DEFAULT
	);
}
void Graphics::FillRect(D2D1_RECT_F* rect) {
	renderTarget_->FillRectangle(rect, brush_);
}
void Graphics::DrawSquare(float x, float y, float sideLength) {
	renderTarget_->DrawRectangle(
		D2D1::RectF(
			x - (sideLength / 2), 
			y - (sideLength / 2), 
			x + (sideLength / 2), 
			y + (sideLength / 2)
		), 
		brush_, 
		GRAPHICS_LINEWEIGHT_DEFAULT
	);
}

void Graphics::SetBrush(float r, float g, float b, float a) {
	brush_->SetColor(D2D1::ColorF(r, g, b, a));
}
void Graphics::SetTransform(D2D1_MATRIX_3X2_F transformation) {
	renderTarget_->SetTransform(transformation);
}
void Graphics::DrawLine(float x1, float y1, float x2, float y2) {
	renderTarget_->DrawLine(
		D2D1::Point2F(
			x1, 
			y1
		), 
		D2D1::Point2F(
			x2, 
			y2
		), 
		brush_, 
		GRAPHICS_LINEWEIGHT_DEFAULT
	);
}
void Graphics::DrawLine(D2D1_POINT_2F point1, D2D1_POINT_2F point2) {
	renderTarget_->DrawLine(
		point1, 
		point2, 
		brush_, 
		GRAPHICS_LINEWEIGHT_DEFAULT
	);
}
void Graphics::DrawLine(GraphicsData::LINE line) {
	renderTarget_->DrawLine(
		line.point1, 
		line.point2, 
		brush_, 
		GRAPHICS_LINEWEIGHT_DEFAULT
	);
}
void Graphics::DrawDrawData(GraphicsData::DRAW_DATA drawData) {
	
}