#pragma once
#include "stdafx.h"
#include "List2.h"

List2::List2(){
	head_ =nullptr;
	temp_ =nullptr;
	tail_ =nullptr;
}

List2::~List2(){
	makeItEmpty();
}

List2::List2(const List2& list){
	head_ =nullptr;
	temp_ =nullptr;
	tail_ =nullptr;
	copy(list);
}

void List2::print(HDC hDC) const{
	if (!isEmpty()){
		SelectObject(hDC, GetStockObject(DC_BRUSH));
		toBegin();
		while (TRUE){
			(*getCurrent()).print(hDC);
			if (!isInEnd()){
				toNext();
			}
			else{
				break;
			}
		};
	}
}

void List2::add(GObject* obj){
	Lelem* a=new Lelem;
	GObject * new_object = obj -> copy();
	a->data_ = new_object;
	if(head_){
			a->previous_=temp_;
			a->next_=temp_->next_;
			temp_->next_=a;
			if(!a->next_){
				tail_=a;
			}
	}
	else{
		head_=a;
		temp_=a;
		tail_=a;
		temp_->next_=nullptr;
		temp_->previous_=nullptr;
	}
}

void List2::makeItEmpty(){
	temp_=head_;
	Lelem* a;
	while (temp_){
		a=temp_->next_;
		delete temp_;
		temp_=a;
	}
	head_=nullptr;
	tail_=nullptr;
}

void List2::toBegin() const{
	temp_=head_;
}

void List2::toNext()const {
	if(temp_)
		temp_=temp_->next_;
	else
		throw std::out_of_range("Out of range.");
}

void List2::toPrevious()const{
	if(temp_)
		temp_=temp_->previous_;
	else
		throw std::out_of_range("Out of range.");
}

void List2::toEnd()const{
	temp_=tail_;
}

bool List2::isEmpty()const{
	return !head_;
}

bool List2::isAfterEnd()const{
	return !temp_;
}

bool List2::isInEnd()const{
	return temp_==tail_;
}

bool List2::isInBegin()const{
	return temp_==head_;
}

void List2::erase(){//Удаляет элемент temp_, перемещает temp_ за удаленный или temp_==nullptr если temp_ в конце.
	if(temp_){
		Lelem *a,*b;
		b=temp_->previous_;
		a=temp_->next_;
		if(isInBegin()){
			head_=a;
		}
		if(isInEnd()){
			tail_=b;
		}
		delete temp_;
		if(b){
			b->next_=a;
		}
		if(a){
			a->previous_=b;
		}
		else{
			temp_=b;
		}
	}
	else{throw std::logic_error("Current element is bad.");
	}
}

GObject*List2::getCurrent()const{
	if (!temp_){throw std::logic_error("Current element is bad.");
	}
	return temp_->data_;
}

GObject*& List2::getCurrent(){
	if (!temp_){throw std::logic_error("Current element is bad.");
	}
	return temp_->data_;
}

void List2::copy(const List2& list){
	if(!list.isEmpty()){
		list.toBegin();
		add(list.getCurrent());
		toEnd();
		while(!list.isInEnd()){
			list.toNext();
			add(list.getCurrent());
			toEnd();
		}
		temp_=head_;
	}
}

GObject* List2::copy(){
	GObject * a = new List2(*this);
	return a;
}