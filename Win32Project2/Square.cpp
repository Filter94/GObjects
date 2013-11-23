#pragma once
#include "Square.h"
#include "stdafx.h"

GObject* Square::copy(){
	GObject * a = new Square(*this);
	return a;
}

Square::Square(RECT rRect, int iBrushColor, int iPenColor){
	rRect_ = rRect;
	iBrushColor_ = iBrushColor;
	iPenColor_ = iPenColor;
}

void Square::draw(HDC hDC) const{
	SetDCBrushColor(hDC, iBrushColor_);
	SelectObject(hDC, GetStockObject(DC_PEN));
	SetDCPenColor(hDC, iPenColor_);
	Rectangle(hDC, rRect_.left, rRect_.top, rRect_.right, rRect_.bottom);
}