/**
* Name: globals.cpp
* Purpose: Namespace Globals
*
* @author Fenris
* @version 0.16 01/05/2017
*/
#include "globals.h"

Globals::States Globals::GAME_STATE = Globals::States::MENU;        //Game state is useful to all objects so I made it global + Let's start with menu
Globals::States Globals::PREVIOUS_STATE = Globals::States::MENU;    //Let's say MENU was first in creation
