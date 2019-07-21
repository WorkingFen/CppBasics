//
// Created by Piotr Zawadka on 20.04.2018.
//

#pragma once

#include "Logic.h"

//Klasa wyświetlania tekstu na konsoli oraz częściowego działania na stanach
class Show {
private:
    Logic *logic;
protected:
    
public:
    explicit Show(Logic* logic) {
        this->logic = logic;
    }
    
    void end();
    void game();
    void gameMenu();
    void load();
    void menu();
    void options();
    void ranking();
    void save();

};

