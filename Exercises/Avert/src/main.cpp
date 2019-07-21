/**
* Name: Main.cpp
* Purpose: Main
*
* @author Fenris
* @version 1.0 7/03/2017
*/

#include <iostream>
#include "a_z.hpp"
#include "avert.hpp"

using namespace std;

int main()
{
    Osoba osoba;
    cout << "Write name:" << endl;
    cin >> osoba.name;
    cout << "Write surname:" << endl;
    cin >> osoba.surname;
    cout << "Write nickname:" << endl;
    cin >> osoba.nickname;

    change(osoba.name);
    change(osoba.surname);
    change(osoba.nickname);

    avert(osoba.name);
    avert(osoba.surname);
    avert(osoba.nickname);

    cout << "Output:" << osoba.name << " " << osoba.surname << " \""<< osoba.nickname << "\" " << endl;

    return 0;
}
