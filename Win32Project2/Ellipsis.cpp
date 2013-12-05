#pragma once
#include "Ellipsis.h"
#include "stdafx.h"

GObject* Ellipsis::copy(){
	GObject * a = new Ellipsis(*this);
	return a;
}

Ellipsis::Ellipsis(RECT rRect, int iBrushColor, int iPenColor){
	rRect_ = rRect;
	iBrushColor_ = iBrushColor;
	iPenColor_ = iPenColor;
}

void Ellipsis::draw(HDC hDC) const{
	SelectObject(hDC, GetStockObject(DC_BRUSH));
	SetDCBrushColor(hDC, iBrushColor_);
	SelectObject(hDC, GetStockObject(DC_PEN));
	SetDCPenColor(hDC, iPenColor_);
	Ellipse(hDC, rRect_.left, rRect_.top, rRect_.right, rRect_.bottom);
}