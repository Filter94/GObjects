#pragma once
#include <iostream>
#include <windows.h>
using namespace std;

class GObject{
public:
	virtual void print(HDC) const = 0;
	virtual ~GObject(){};
	virtual GObject* copy() = 0;
};