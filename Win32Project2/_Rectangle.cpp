#pragma once
#include "_Rectangle.h"
#include "stdafx.h"

GObject* _Rectangle::copy(){
	GObject * a = new _Rectangle(*this);
	return a;
}

_Rectangle::_Rectangle(RECT rRect, int iBrushColor, int iPenColor){
	rRect_ = rRect;
	iBrushColor_ = iBrushColor;
	iPenColor_ = iPenColor;
}

void _Rectangle::draw(HDC hDC) const{
	SetDCBrushColor(hDC, iBrushColor_);
	SelectObject(hDC, GetStockObject(DC_PEN));
	SetDCPenColor(hDC, iPenColor_);
	Rectangle(hDC, rRect_.left, rRect_.top, rRect_.right, rRect_.bottom);
}