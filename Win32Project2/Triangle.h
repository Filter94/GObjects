#pragma once
#include <iostream>
#include <windows.h>
#include "GObject.h"

using namespace std;

struct TRIANGLE_{
	POINT first;
	POINT second;
	POINT third;

	TRIANGLE_(){};

	TRIANGLE_(POINT iFirst, POINT iSecond, POINT iThird){
		first = iFirst;
		second = iSecond;
		third = iThird;
	}
};

class Triangle : public GObject{
private:
	TRIANGLE_ tTriangle_;
	POINT pMainPoint_;
	COLORREF iBrushColor_;
	int iPenColor_;
public:
	Triangle(TRIANGLE_ tTriangle, int BrushColor, int iPenColor);
	~Triangle(){};
	virtual void draw(HDC) const;
	GObject* copy();
};