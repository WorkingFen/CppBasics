/**
* Name: MyList.h
* Purpose: Define class MyList
*
* @author Fenris
* @version 0.87 30/03/2017
*/
#pragma once
#include "Element.h"

class MyList {
public:

	Element* first;
	Element* lastAdd;

	MyList(); //Create a default object

    ///Add an element
	Element& add(int); //As first on the list
	Element& add(double, int); //After element with index

    ///Delete an element
	void del(double); //By its index
	void del(int); //By its value
	void del(int, int); //By value from i to j
	void del(Element*, int); //By its index and value

    ///Check how many elements are there in list
	int check();

	MyList* single(); //Only one element with each value

	bool operator==(MyList&); //Equal?
	bool operator!=(MyList&); //Unequal?
	bool operator>(MyList&);  //Bigger
	bool operator<(MyList&);  //Smaller

	Element* operator[](int); //Index

	MyList operator=(MyList&); //Copy object MyList

	MyList* operator+(MyList&); //Add lists
	MyList* operator+(int); //Add integral to list

	MyList* operator-(MyList&); //Subtract lists
	MyList* operator-(int); //Subtract integral from list

	MyList(MyList&); //Copy an object

	~MyList(); //Delete an object
};
