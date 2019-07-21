//
// Created by Piotr Zawadka on 20.04.2018.
//

#include "interface.h"

const QString interface::filepathRanking = "";

void interface::data() {
    QTextStream qtout(stdout);
    qtout << "|||||\tGra 2048++" << endl;
    qtout << "|||||\tStworzona przez Kinge Rynkowska" << endl;
    qtout << endl;
    qtout << "Wcisnij ENTER by kontynuowac" << endl;
}

void interface::menu() {
    QTextStream qtout(stdout);
    qtout << "Gra 2048++" << endl;
    qtout << "1.(G)raj" << endl;
    qtout << "2.(W)czytaj" << endl;
    qtout << "3.(R)anking" << endl;
    qtout << "4.(O)pcje" << endl;
    qtout << "0.(K)oniec" << endl;
    qtout << endl;
    qtout << "Wpisz co chcesz zrobic" << endl;
    qtout << endl;
}

void interface::gameMenu() {
    QTextStream qtout(stdout);
    qtout << "Pauza" << endl;
    qtout << "1.(W)roc" << endl;
    qtout << "2.(Z)apisz" << endl;
    qtout << "0.(M)enu glowne" << endl;
    qtout << endl;
    qtout << "Wpisz co chcesz zrobic" << endl;
    qtout << endl;
}

void interface::options() {
    QTextStream qtout(stdout);
    qtout << "Opcje" << endl;
    qtout << "1.(Z)mien rozmiar planszy" << endl;
    qtout << "0.(W)roc" << endl;
    qtout << endl;
    qtout << "Wpisz co chcesz zrobic" << endl;
    qtout << endl;
}

void interface::load() {
    QTextStream qtout(stdout);
    qtout << "Wczytywanie" << endl;
    qtout << "1.(Z)aladuj poprzedni stan gry" << endl;
    qtout << "0.(W)roc" << endl;
    qtout << endl;
    qtout << "Wpisz co chcesz zrobic" << endl;
    qtout << endl;
}

void interface::save() {
    QTextStream qtout(stdout);
    qtout << "Zapisywanie" << endl;
    qtout << "1.(Z)apisz stan gry" << endl;
    qtout << "0.(W)roc" << endl;
    qtout << endl;
    qtout << "Wpisz co chcesz zrobic" << endl;
    qtout << endl;
}
