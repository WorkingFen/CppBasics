/**
* Name: Avert.cpp
* Purpose: Avert->trevA
*
* @author Fenris
* @version 0.1 7/03/2017
*/
#include <iostream>
#include <string.h>
#include "avert.hpp"

void avert(char* tab){
  char help;
  int j=strlen(tab);
  for(int i=0; i<j/2; i++){
    help=tab[i];
    tab[i]=tab[j-i-1];
    tab[j-i-1]=help;
  }
}

