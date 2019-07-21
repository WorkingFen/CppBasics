//
// Created by Piotr Zawadka on 20.04.2018.
//

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include "Show.h"

using namespace std;

void Show::end() {
    QTextStream qtout(stdout);
    logic->setNext(false);

    do {
        system("cls");              //Czyszczenie konsoli, by ładnie wyglądała

        if(logic->getBad())
            qtout << "Zla komenda! Prosze wpisac poprawna komende" << endl;

        qtout << "Koniec gry" << endl;
        qtout << "Zdobyles " << logic->getScore() << " punktow!" << endl;
        qtout << "1.(Z)agraj ponownie" << endl;
        qtout << "0.(M)enu" << endl;
        qtout << endl;
        qtout << "Wpisz co chcesz zrobic" << endl;
        qtout << endl;

        logic->chooseEnd();

    }while(!logic->getNext());
}

void Show::game() {
    QTextStream qtout(stdout);
    int foo = 0;
    logic->setNext(false);

    if(logic->getNextNumber())
        logic->randTable();

    logic->setNextNumber(false);

    do {
        system("cls");

        for(auto tmp : logic->getTable()) {             /* Wyświetlanie planszy gry */
            qtout << endl;
            for (auto i : tmp) {
                qtout << "\t" << i;
                if (!(++foo % logic->getSize()))
                    qtout << endl << endl;
            }
        }

        if(logic->getBad())
            qtout << "Zla komenda! Prosze wpisac poprawna komende" << endl;

        qtout << "Sterowanie za pomoca WSAD lub klawiatury numerycznej, X/5 wlacza pauze" << endl;
        qtout << "Za pomoca przycisku Q/7 mozna cofnac ruch, ale tylko 3 razy" << endl;

        if(logic->getNoBack())
            qtout << "Nie mozesz cofnac ruchu" << endl;

        logic->play();

    }while(!logic->getNext());
}

void Show::gameMenu() {
    QTextStream qtout(stdout);
    logic->setNext(false);

    do {
        system("cls");

        if(logic->getBad())
            qtout << "Zla komenda! Prosze wpisac poprawna komende" << endl;

        interface::gameMenu();

        logic->chooseGameMenu();

    }while(!logic->getNext());
}

void Show::load() {
    QTextStream qtout(stdout);
    logic->setNext(false);

    do {
        system("cls");

        if(logic->getBad())
            qtout << "Zla komenda! Prosze wpisac poprawna komende" << endl;

        interface::load();

        logic->chooseLoad();

    }while(!logic->getNext());
}

void Show::menu() {
    QTextStream qtout(stdout);
    logic->setNext(false);

    do {
        system("cls");

        if(logic->getBad())
            qtout << "Zla komenda! Prosze wpisac poprawna komende" << endl;

        interface::menu();

        logic->chooseMenu();

    }while(!logic->getNext());
}

void Show::options() {
    QTextStream qtout(stdout);
    logic->setNext(false);

    do {
        system("cls");

        if(logic->getBad())
            qtout << "Zla komenda! Prosze wpisac poprawna komende" << endl;

        interface::options();

        logic->chooseOptions();

    }while(!logic->getNext());
}

void Show::ranking() {
    QTextStream qtout(stdout);          //Tak się deklaruje wypisywanie w konsoli w Qt (std::cout)
    QTextStream qtin(stdin);            //Tak się deklaruje zapis do konsoli (std::cin)
    QChar in;
    char c;
    QVector< QPair<QString,int> > tmpBuffor;

    logic->setNext(false);

    logic->load(interface::filepathRanking+"ranking");
    tmpBuffor = logic->getBuffor();

    do{
        system("cls");

        if(logic->getBad())
            qtout << "Zla komenda! Prosze wpisac poprawna komende" << endl;

        qtout << "Ranking" << endl;
        for(auto tmp : tmpBuffor)
        {
            qtout << tmp.first << "\t" << tmp.second << endl;
        }
        qtout << endl;
        qtout << "0. (W)roc" << endl;
        qtin >> in;
        c = in.toLatin1();
        if(c == 'W' || c == 'w' || c == '0') {
            logic->setBad(false);
            logic->setNext(true);
            logic->setState(State::Menu);
        }
        else
            logic->setBad(true);

    }while(!logic->getNext());
}

void Show::save() {
    QTextStream qtout(stdout);
    logic->setNext(false);

    do {
        system("cls");

        if(logic->getBad())
            qtout << "Zla komenda! Prosze wpisac poprawna komende" << endl;

        interface::save();

        logic->chooseSave();

    }while(!logic->getNext());
}
