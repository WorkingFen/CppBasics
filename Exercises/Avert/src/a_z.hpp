/**
* Name: A_Z.hpp
* Purpose: Define
*
* @author Fenris
* @version 0.1 7/03/2017
*/
#ifndef A_Z_HPP
#define A_Z_HPP

class Osoba{
  public:
    char* name= new char[30];
    char* surname= new char[30];
    char* nickname= new char[30];
};

void change(char*);

#endif // A_Z_HPP
