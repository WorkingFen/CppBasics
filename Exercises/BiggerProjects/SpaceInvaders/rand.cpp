/**
* Name: rand.cpp
* Purpose: Namespace Rand
*
* @author Fenris
* @version 0.18a 01/05/2017
*/
#include <cstdlib>
#include "rand.h"

unsigned Rand::random(const unsigned low, const unsigned high){
    return (rand() % (high - low + 1)) + low;
}
