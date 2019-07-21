/**
* Name: Element.h
* Purpose: Class Element
*
* @author Fenris
* @version 0.9 29/03/2017
*/
#pragma once

class Element {
	int ID;
	int value;
	double index;
	Element* prev;
	Element* next;

public:

	Element(); //Construct a default element
	Element(int); //Construct first element
	Element(int, Element&, Element&); //Construct element which will be first
	Element(int, double, Element&, Element&); //Construct element with index

    ///Pop element out of the private
	Element* popF();
	Element* popB();
	double popIndex();
	int popValue();
	int popID();

	///Push element to the private
	void pushF(Element*);
	void pushB(Element*);
	void pushIndex(double);
	void pushValue(int);
	void pushID(int);

	///Change index
	void indexPlus(Element*);
	void indexMinus(Element*);

	///Search and export an element
	Element* exSearch(double, Element*); //By its index
	Element* exSearch(int, Element*); //By its value

	Element& operator=(Element*); //Copy an Element with operator

	bool operator!=(const int&); //Unequal?
	bool operator==(const Element&); //Equal?

	Element(Element&); //Copy an element

	~Element(); //Delete
};
