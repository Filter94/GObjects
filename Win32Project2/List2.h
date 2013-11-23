#pragma once

#include "GObject.h"
#include <iostream>

using namespace std;

class List2: public GObject{
public:
	void draw(HDC) const;
	List2();//crt
	~List2();//dsry
	List2(const List2&);//cpy
	void addToBegin(const GObject*);
	void add(GObject *);
	void makeItEmpty();
	void toBegin()const;
	void toNext()const;
	void toPrevious()const;
	void toEnd()const;
	bool isEmpty()const;
	bool isInEnd()const;
	bool isAfterEnd()const;
	bool isInBegin()const;
	void erase();
	GObject*& getCurrent();
	GObject* getCurrent() const;
	GObject* copy();
private:	
	struct Lelem{
		Lelem* previous_;
		Lelem* next_;
		GObject* data_;
		~Lelem(){delete data_;}
	};
	Lelem* tail_;
	Lelem* head_;
	mutable Lelem* temp_;
	void copy(const List2&);
};