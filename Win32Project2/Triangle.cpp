#pragma once
#include "Triangle.h"
#include "stdafx.h"

GObject* Triangle::copy(){
	GObject * a = new Triangle(*this);
	return a;
}

Triangle::Triangle(TRIANGLE_ tTriangle, int iBrushColor, int iPenColor){
	tTriangle_ = tTriangle;
	iBrushColor_ = iBrushColor;
	iPenColor_ = iPenColor;
}

void Triangle::draw(HDC hDC) const{
	SetDCBrushColor(hDC, iBrushColor_);
	SelectObject(hDC, GetStockObject(DC_PEN));
	SetDCPenColor(hDC, iPenColor_);
	POINT triangle[4];

	triangle[0].x = tTriangle_.first.x;
	triangle[0].y = tTriangle_.first.y;

	triangle[1].x = tTriangle_.second.x;
	triangle[1].y = tTriangle_.second.y;

	triangle[2].x  = tTriangle_.third.x;
	triangle[2].y = tTriangle_.third.y;

	Polygon(hDC, triangle, 3);
}