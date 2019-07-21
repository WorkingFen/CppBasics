/**
* Name: MyList.cpp
* Purpose: Define class MyList
*
* @author Fenris
* @version 0.92a 02/04/2017
*/
#include <iostream>
#include "MyList.h"

MyList::MyList() :first(), lastAdd()
{
}

Element& MyList::add(int value = 0)
{
	if (first == NULL) {
		Element* flag = new Element(value);
		first = lastAdd = flag;
		return *flag;
	}
	else {
		Element* flag = new Element(value, *first, *lastAdd);
		first = lastAdd = flag;
		return *flag;
	}
}

Element& MyList::add(double index = 0, int value = 0)
{
	if (first == NULL) {
		Element* flag = new Element(value);
		first = lastAdd = flag;
		return *flag;
	}
	else {
		Element* flag = new Element(value, index, *first, *lastAdd);
		lastAdd = flag;
		return *flag;
	}
}

void MyList::del(double index)
{
	Element* toDel = this->first->exSearch(index, this->first);
	Element* tmp = toDel->popB();

	if (tmp != NULL) {
		toDel->popF()->pushB(tmp);
		tmp->pushF(toDel->popF());
	}

	if (toDel == this->first) {
		this->first = toDel->popF();
		toDel->popF()->pushB(NULL);
	}

	this->first->indexMinus(toDel);

	delete toDel;
	toDel = NULL;
}

void MyList::del(int value)
{
    Element* flag = this->first;
	while (flag->popF() != NULL) {
		Element* toDel = flag->exSearch(value, flag);
        Element* tmp = toDel->popB();

        if (toDel == NULL)
            break;

        if (tmp != NULL) {
            toDel->popF()->pushB(tmp);
            tmp->pushF(toDel->popF());
        }

        if (toDel == this->first) {
            this->first = toDel->popF();
            toDel->popF()->pushB(NULL);
        }

        flag->indexMinus(toDel);

        flag = flag->popF();
        delete toDel;
        toDel = NULL;
	}
}

void MyList::del(int from, int to)
{
    Element* flag = this->first;
	while (flag->popF() != NULL) {
        if (flag->popValue() <= to && flag->popValue() >= from) {
            Element* toDel = flag;
            Element* tmp = toDel->popB();

            if (tmp != NULL) {
                toDel->popF()->pushB(tmp);
                tmp->pushF(toDel->popF());
            }

            if (toDel == this->first) {
                this->first = toDel->popF();
                toDel->popF()->pushB(NULL);
            }

            flag->indexMinus(toDel);

            flag = flag->popF();
            delete toDel;
            toDel = NULL;
        }
        else
            flag = flag->popF();
	}
}

void MyList::del(Element* el, int value)
{
    Element* flag = el;
	while (flag->popF() != NULL) {
		Element* toDel = flag->exSearch(value, flag);
        Element* tmp = toDel->popB();

        if (toDel == NULL)
            break;

        if (tmp != NULL) {
            toDel->popF()->pushB(tmp);
            tmp->pushF(toDel->popF());
        }

        if (toDel == this->first) {
            this->first = toDel->popF();
            toDel->popF()->pushB(NULL);
        }

        flag->indexMinus(toDel);

        flag = flag->popF();
        delete toDel;
        toDel = NULL;
	}
}

int MyList::check()
{
	int ile = 0;
	Element* tmp = this->first;
	while (tmp != NULL) {
		++ile;
		tmp = tmp->popF();
	}
	return ile;
}

MyList* MyList::single()
{
    Element* tmp = this->first;
	while (tmp->popF() != NULL) {
		if (tmp->exSearch(tmp->popValue(), tmp->popF()) != NULL)
			this->del(tmp->popF(), tmp->popValue());
		tmp = tmp->popF();
	}

	return this;
}

bool MyList::operator==(MyList& mL)
{
	int ok = 0;
	if (this->check() == mL.check()) {
		int ile = this->check();
		while (ile-->0) {
			if (this->first == mL.first)
				ok = 1;
			else {
				ok = 0;
				break;
			}
		}
	}
	if (ok == 0)
		return false;
	else
		return true;
}

bool MyList::operator!=(MyList &mL)
{
	int ok = 0;
	if (this->check() == mL.check()) {
		int ile = this->check();
		while (ile-->0) {
			if (this->first == mL.first)
				ok = 1;
			else {
				ok = 0;
				break;
			}
		}
	}
	if (ok == 0)
		return true;
	else
		return false;
}

bool MyList::operator>(MyList& mL)
{
	if (this->check() > mL.check())
		return true;
	else
		return false;
}

bool MyList::operator<(MyList& mL)
{
	if (this->check() < mL.check())
		return true;
	else
		return false;
}

Element* MyList::operator[](int index)
{
	return this->first->exSearch((double)index, this->first);
}

MyList MyList::operator=(MyList &mL)
{
	first = new Element(*mL.first);
	lastAdd = new Element(*mL.lastAdd);

	return *this;
}

MyList* MyList::operator+(MyList &mL)
{
    Element* tmp = mL.first;
    Element* flag = this->first;
	while (flag->popF() != NULL) {
		flag = flag->popF();
	}
	while (tmp != NULL) {
        this->add(flag->popIndex(), tmp->popValue());
        tmp->pushID(this->lastAdd->popID());
        lastAdd = flag;
        tmp = tmp->popF();
        flag = flag->popF();
	}
	return this;
}

MyList* MyList::operator+(int i)
{
    Element* flag = this->first;
	while (flag->popF() != NULL) {
		flag = flag->popF();
	}
	this->add(flag->popIndex(), i);
	flag = flag->popF();
	flag->pushID(this->lastAdd->popID());
	lastAdd = flag;
	return this;
}

MyList* MyList::operator-(MyList &mL)
{
    Element* tmp = mL.first;
	while (tmp != NULL) {
        del(tmp->popValue());
        tmp = tmp->popF();
	}
	return this;
}

MyList* MyList::operator-(int i)
{
	del(i);
	return this;
}

MyList::MyList(MyList &mL)
{
    Element* tmp = mL.first;
    Element* flag = this->first;
    this->first = new Element(*tmp);
    while(tmp != NULL){
        flag = new Element(*tmp);
        if(tmp != mL.first){
            flag->pushB(flag->exSearch(flag->popIndex()-1, this->first));
            flag->popB()->pushF(flag);
        }
        tmp = tmp->popF();
        flag->pushF(NULL);
    }
}

MyList::~MyList()
{
	delete first;
}
