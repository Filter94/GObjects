#pragma once
#include <iostream>
#include <windows.h>
#include "GObject.h"

using namespace std;

class _Rectangle : public GObject{
private:
	RECT rRect_;
	COLORREF iBrushColor_;
	COLORREF iPenColor_;
public:
	_Rectangle(RECT rRect, int iBrushColor, int iPenColor);
	~_Rectangle(){};
	virtual void draw(HDC) const;
	GObject* copy();
};