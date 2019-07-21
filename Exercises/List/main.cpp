/**
* Name: main.cpp
* Purpose: Main file
*
* @author Fenris
* @version 0.94a 02/04/2017
*/
#include <iostream>
#include <cassert>
#include "Element.h"
#include "MyList.h"

using namespace std;

///Function to show text
void text(Element* tmp){
        cout << tmp->popIndex() << ".  ";
		cout << tmp->popID() << " ";
		cout << tmp->popValue() << endl;
}

int main() {

	///cout << "Robciaj Pipi" << endl;

///Test of push and pop

	cout << "------------------===============+++++++++++++Test of push and pop+++++++++++++===============------------------" << endl << endl;
	MyList *hy = new MyList();
	hy->add(2);                                                                 //Default ID is 0, index is 1, value is 2
	hy->add(1);                                                                 //Add as first, add(2) should has index 2 now
	hy->add(1.0, 3);                                                            //Add after index 1
	hy->add(2.0, 7);                                                            //Add after index 2

	cout << "Values of First element of hy: Index, ID, value, previous, next " << endl;
	cout << hy->first->popIndex() << ".  ";                                     //Let's see value of ID
	cout << hy->first->popID() << " ";                                          //Let's see value of Index
	cout << hy->first->popValue() << " | ";                                     //Let's see value of Value
	cout << hy->first->popB()<< ", ";                                           //Let's see an address of previous
    cout << hy->first->popF() <<endl;                                           //Let's see an address of next
#ifdef _DEBUG
	cout <<"Address: "<< hy->first << endl<<endl;
#endif //_DEBUG

#ifdef _DEBUG
	Element *tmp = hy->first;                                                   //Testing object
	cout << "Values of: Index, ID, value, previous, next " << endl;
	while (tmp != NULL) {
		text(tmp);
        cout <<"Address: "<< tmp << endl<<endl;                                 //Just to see if it's alright
		tmp = tmp->popF();                                                      //First should be element with value 1, last with 2
	}
#endif // _DEBUG

    cout << endl << "===========Let's see address of element (3) which I recall by index operator===========" << endl;

    tmp = (*hy)[3];
    cout <<"Address of (*hy)[3]: "<< tmp << endl<<endl;

	hy->first->pushIndex(5);                                                    //Let's make Index's value =5
	hy->first->pushValue(5);                                                    //Let's make Value's value =5
	hy->first->pushID(5);                                                       //Let's make ID's value bigger  1 =6

#ifdef _DEBUG
	cout << "                 ===========ID should be bigger by 1 than (5)! Other values should be (5)===========                 " << endl;
#endif // _DEBUG

	cout << "Values of first element after pushes: Index, ID, value " << endl;
	cout << hy->first->popIndex() << ".  ";                                     //Let's see value of ID now
	cout << hy->first->popID() << " ";                                          //Let's see value of Index now
	cout << hy->first->popValue() << endl << endl;                              //Let's see value of Value now

#ifdef _DEBUG
    cout << "===========Here should be seen address of First element of hy===========" << endl;
	cout << hy->first << endl;
#endif //_DEBUG

	tmp = hy->first->exSearch(3.0, hy->first);

#ifdef _DEBUG
    cout << "===========Here should be seen address of element with index (3) of hy===========" << endl;
	cout << tmp << endl<<endl;
#endif //_DEBUG

	cout << "Values of element that I recalled by index (3): Index, ID, value " << endl;
	text(tmp);

#ifdef _DEBUG
    cout << "===========Here I should change index of First element of hy to (1)===========" << endl;
	hy->first->pushIndex(1);
	cout << hy->first->popIndex() << ".  ";
	cout << hy->first->popID() << " ";
	cout << hy->first->popValue() << endl << endl;
    cout << "                                ===========Index has been changed to (1)===========                 " << endl<<endl;
#endif //_DEBUG

///Test of add and delete
	cout << "------------------===============+++++++++++++Test of add and delete+++++++++++++===============------------------" << endl << endl;
	MyList *yh = new MyList();
	yh->add(2);                                                                 //Add it as first element
	yh->add(4);
	yh->add(2);
	yh->add(9);
	yh->add(3);
	yh->add(2.0, 6);                                                            //Add it after index 2
	yh->add(2);
	yh->add(7);
	yh->add(9);
	yh->add(6);
	yh->add(5.0, 6);
	yh->add(1);
	yh->add(3);
	yh->add(9);
	yh->add(2);
	yh->add(9);
	yh->add(2);
	yh->add(3.0, 4);                                                            //Add it after index 3

	tmp = yh->first;
	cout << "Values of: Index, ID, value " << endl;
	while (tmp != NULL) {
		text(tmp);
#ifdef _DEBUG
		cout <<"& of ^: "<< tmp << endl;
#endif // _DEBUG
		tmp = tmp->popF();
	}

	cout << endl << "Previous value of ID in First of yh: " << yh->first->popID() << endl;
	yh->first->pushID(hy->first->popID());                                       //Just checking pushID with element and popID
	cout << "------------ID should be bigger by 1 than First's element of hy!-------------" << endl;
	cout << "Value of ID in First of yh after push: " << yh->first->popID() << endl << endl;

	yh->del(4.0);                                                                //Delete element which has index (4)

	tmp = yh->first;
	cout << "===========List after deleting of element with index (4)===========" << endl;
	cout << "Values of: Index, ID, value " << endl;
	while (tmp != NULL) {
		text(tmp);
#ifdef _DEBUG
		cout <<"& of ^: "<< tmp << endl;
#endif // _DEBUG
		tmp = tmp->popF();
	}

	yh->del(7);                                                                 //Delete element which has value (7)

	tmp = yh->first;
    cout << endl << "===========List after deleting element with value (7)===========" << endl;
	cout << "Values of: Index, ID, value " << endl;
	while (tmp != NULL) {
		text(tmp);
#ifdef _DEBUG
		cout <<"& of ^: "<< tmp << endl;
#endif // _DEBUG
		tmp = tmp->popF();
	}

	yh->del(2);                                                                 //Delete elements which have value (2)

	tmp = yh->first;
    cout << endl << "===========List after deleting elements with value (2)===========" << endl;
	cout << "Values of: Index, ID, value " << endl;
	while (tmp != NULL) {
		text(tmp);
#ifdef _DEBUG
		cout <<"& of ^: "<< tmp << endl;
#endif // _DEBUG
		tmp = tmp->popF();
	}

	yh->del(1, 3);                                                              //Delete elements which have values from (1) to (3)

	tmp = yh->first;
    cout << endl << "===========List after deleting elements from values (1) to (3)===========" << endl;
	cout << "Values of: Index, ID, value " << endl;
	while (tmp != NULL) {
		text(tmp);
#ifdef _DEBUG
		cout <<"& of ^: "<< tmp << endl;
#endif // _DEBUG
		tmp = tmp->popF();
	}

///Test of check
	cout <<endl << "--------------------=================+++++++++++++++Test of check+++++++++++++++=================--------------------" << endl << endl;
	int i;
	i = hy->check();                                                            //As I recall, there should be 4 elements

#ifdef _DEBUG
	cout << "                                    ===========There should be 4 elements in hy===========                                    " << endl;
#endif // _DEBUG

	cout << "There are " << i << " elements in the list hy" << endl<<endl;

#ifdef _DEBUG
    i = yh->check();
    cout << "There are " << i << " elements in the list yh" << endl<<endl;
#endif // _DEBUG

///Test >, <, ==, !
    cout <<endl << "-------------------================++++++++++++++[Test >, <, ==, !=]+++++++++++++++================-------------------" << endl << endl;
    bool type;

    type = *hy>*yh;
    cout <<"Operator >: hy>yh "<< type << endl<<endl;

    type = *yh>*hy;
    cout <<"Operator >: yh>hy "<< type << endl<<endl;

    type = *hy<*yh;
    cout <<"Operator <: hy<yh "<< type << endl<<endl;

    type = *yh<*hy;
    cout <<"Operator <: yh<hy "<< type << endl<<endl;

    type = yh==hy;
    cout <<"Operator ==: hy==yh "<< type << endl<<endl;

    type = yh!=hy;
    cout <<"Operator !=: yh!=hy "<< type << endl<<endl;

///Test of + and -
    cout <<endl << "-----------------===============+++++++++++++[Test of + and - operators]++++++++++++++===============-----------------" << endl << endl;

    cout << endl << "===========List (hy) after adding an integer (2)===========" << endl;
    hy = *hy+2;
    tmp = hy->first;
    cout << "Values of: Index, ID, value " << endl;
    while (tmp != NULL) {
        text(tmp);
        cout <<"& of ^: "<< tmp << endl;
        tmp = tmp->popF();
    }

    cout << endl << "===========List (hy) after adding another list (yh)===========" << endl;
    hy = *hy+*yh;
    tmp = hy->first;
    cout << "Values of: Index, ID, value " << endl;
    while (tmp != NULL) {
        text(tmp);
        cout <<"& of ^: "<< tmp << endl;
        tmp = tmp->popF();
    }

    cout << endl << "===========List (hy) after subtracting an integer (2)===========" << endl;
    hy = *hy-2;
    tmp = hy->first;
    cout <<"Address: "<< tmp << endl<<endl;
    cout << "Values of: Index, ID, value " << endl;
    while (tmp != NULL) {
        text(tmp);
        tmp = tmp->popF();
    }

    cout << endl << "===========List (hy) after subtracting another list (yh)===========" << endl;
    hy = *hy-*yh;
    tmp = hy->first;
    cout <<"Address: "<< tmp << endl<<endl;
    cout << "Values of: Index, ID, value " << endl;
    while (tmp != NULL) {
        text(tmp);
        tmp = tmp->popF();
    }

///Test of copying constructor
    cout <<endl << "-----------------===============+++++++++++++Test of copying constructor++++++++++++++===============-----------------" << endl << endl;

    MyList* flag = new MyList(*hy);

    tmp = flag->first;
    cout <<"Address: "<< tmp << endl<<endl;
    cout << "Values of: Index, ID, value in (flag)" << endl;
    while (tmp != NULL) {
        text(tmp);
        cout <<"& of ^: "<< tmp << endl;
        tmp = tmp->popF();
    }
    cout << endl << "===========List (flag) and (hy) should be the same, but with different addresses===========" << endl;

    tmp = hy->first;
    cout <<"Address: "<< tmp << endl<<endl;
    cout << "Values of: Index, ID, value in (hy)" << endl;
    while (tmp != NULL) {
        text(tmp);
        cout <<"& of ^: "<< tmp << endl;
        tmp = tmp->popF();
    }


///Test of single (Function to delete doubled values)
    cout <<endl << "-----------------===============+++++++++++++Test of deleting doubled values++++++++++++++===============-----------------" << endl << endl;

	yh->single();

	tmp = yh->first;
    cout <<"Address: "<< tmp << endl<<endl;
    cout << "Values of: Index, ID, value in (yh)" << endl;
    while (tmp != NULL) {
        text(tmp);
        tmp = tmp->popF();
    }

	i = yh->check();

	cout << "There are now " << i << " elements in the list" <<endl;

///Test of deleting
	cout << "-------------------================++++++++++++++Test of deleting++++++++++++++================-------------------" << endl << endl;
	delete hy;
	delete yh;
	delete tmp;
	delete flag;

#ifdef _DEBUG
	///Error if accessed... That means it's deleted
	//cout <<"Values after delete: ID, index, value "<<endl<<hy->first->popID()<<" ";
	//cout << hy->first->popIndex()<<" ";
	//cout << hy->first->popValue()<<endl<<endl;
	//cout << "As we can see it's rubbish, great!" <<endl;
	cout << "                                    ===========Everything has been deleted===========                                    " << endl;
#endif //_DEBUG

	return 0;

}
