/**
* Name: A_Z.cpp
* Purpose: Define
*
* @author Fenris
* @version 0.1 7/03/2017
*/
#include <iostream>
#include "a_z.hpp"

using namespace std;

void change(char* tab){
  for(int i=0; i<30; i++){
    if(tab[i]=='a'||tab[i]=='e'||tab[i]=='i'||tab[i]=='o'||tab[i]=='u'||tab[i]=='y'||
    tab[i]=='A'||tab[i]=='E'||tab[i]=='I'||tab[i]=='O'||tab[i]=='U'||tab[i]=='Y')
      tab[i]='z';
  }
}
