#pragma once
#include <iostream>
#include <windows.h>
#include "GObject.h"

using namespace std;

class Ellipsis : public GObject{
private:
	RECT rRect_;
	POINT pMainPoint_;
	COLORREF iBrushColor_;
	int iPenColor_;
public:
	Ellipsis(RECT rRect, int BrushColor, int iPenColor);
	~Ellipsis(){}; 
	virtual void print(HDC) const;
	GObject* copy();
};