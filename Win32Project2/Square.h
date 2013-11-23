#pragma once
#include <iostream>
#include <windows.h>
#include "GObject.h"

using namespace std;

class Square : public GObject{
private:
	RECT rRect_;
	COLORREF iBrushColor_;
	COLORREF iPenColor_;
public:
	Square(RECT rRect, int iBrushColor, int iPenColor);
	~Square(){};
	virtual void draw(HDC) const;
	GObject* copy();
};