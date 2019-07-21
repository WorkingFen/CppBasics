/**
* Name: Element.cpp
* Purpose: Define class Element
*
* @author Fenris
* @version 0.89a 02/04/2017
*/
#include <iostream>
#include "Element.h"

Element::Element()
{
	this->ID = 0;
	this->index = 0;
	this->value = 0;
	prev = NULL;
	next = NULL;
}

Element::Element(int value)
{
	this->ID = 0;
	this->index = 1;
	this->value = value;
	prev = NULL;
	next = NULL;
}

Element::Element(int value, Element &first, Element &lastAdd)
{
	this->ID = lastAdd.ID + 1;
	this->index = 1;

	this->value = value;
	prev = NULL;
	next = &first;

	Element* tmp = this->next;

	tmp->prev = this;

	indexPlus(this); //Other's indexes have their values greater by one
}

Element::Element(int value, double index, Element& first, Element& lastAdd)
{
	Element* prv = exSearch(index, &first);
	this->ID = lastAdd.ID + 1;
	this->index = index + 1;

	this->value = value;
	this->prev = prv;
	this->next = prv->next;
	if (prv->next != NULL)
		prv->next->prev = this;
	prv->next = this;

	indexPlus(this); //Other's indexes have their values greater by one
}

Element * Element::popF()
{
	if (this != NULL)
		return this->next;
	return (Element*)NULL;
}

Element * Element::popB()
{
	if (this != NULL)
		return this->prev;
	return (Element*)NULL;
}

double Element::popIndex()
{
	if (this != NULL)
		return this->index;
	return (double)NULL;
}

int Element::popValue()
{
	if (this != NULL)
		return this->value;
	return (int)NULL;
}

int Element::popID()
{
	if (this != NULL)
		return this->ID;
	return (int)NULL;
}

void Element::pushF(Element* next)
{
	if (this != NULL)
		this->next = next;
}

void Element::pushB(Element* prev)
{
	if (this != NULL)
		this->prev = prev;
}

void Element::pushIndex(double index)
{
	if (this != NULL)
		this->index = index;
}

void Element::pushValue(int value)
{
	if (this != NULL)
		this->value = value;
}

void Element::pushID(int ID)
{
	if (this != NULL)
		this->ID = ID + 1;
}

Element* Element::exSearch(double index, Element* first) //Search for value by index
{
	while (first != NULL) {
		if (first->index == index)
			return first;
		first = first->next;
	}
	return (Element*)NULL;
}

Element* Element::exSearch(int value, Element* first) //Search for first element with value
{
	while (first != NULL) {
		if (first->value == value)
			return first;
		first = first->next;
	}
	return (Element*)NULL;
}

void Element::indexPlus(Element* start)
{
	while (start->next != NULL) {
		start->next->pushIndex(start->popIndex() + 1);
		start = start->next;
	}
}

void Element::indexMinus(Element* start)
{
	start->pushIndex(start->popIndex() - 1);
	while (start->next != NULL) {
		start->next->pushIndex(start->popIndex() + 1);
		start = start->next;
	}
}

Element& Element::operator=(Element* el)
{
	this->ID = el->ID;
	this->value = el->value;
	this->index = el->index;
	this->prev = el->prev;
	this->next = el->next;

	return *this;
}

bool Element::operator!=(const int &el)
{
	if (this->ID != el)
		return true;
	else
		return false;
}

bool Element::operator==(const Element &el)
{
	if (this->value == el.value && this->index == el.index)
		return true;
	else
		return false;
}

Element::Element(Element &el)
{
	this->ID = el.ID;
	this->value = el.value;
	this->index = el.index;
}

Element::~Element()
{
	Element* do_skasowania = NULL;
	Element* pierwszy = this;
	int koniec = 0;

	while (!koniec) {
		do_skasowania = pierwszy->next;

		if (do_skasowania == NULL)
			do_skasowania = pierwszy;

		if (pierwszy != NULL)
			pierwszy->next = do_skasowania->next;

		if (do_skasowania == pierwszy) {
			koniec = 1;
		}

		do_skasowania = NULL;

	}
	pierwszy = NULL;
}
