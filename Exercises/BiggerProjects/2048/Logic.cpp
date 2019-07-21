//
// Created by Piotr Zawadka on 20.04.2018.
//

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <time.h>
#include <random>
#include "Logic.h"

//**Funkcje ulatwiajace zmniejszenie redundancji kodu**//
void Logic::newBreak(State state) {
    QTextStream qtin(stdin);
    setState(state);
    qtin.reset();
    setBad(false);
    setNext(true);
}

void Logic::newGame() {
    setNextNumber(true);
    setGameOver(false);
    setScore(0);
    clearTable();
    randTable();
}

QCharRef Logic::output() {
    QTextStream qtin(stdin);
    QTextStream qtout(stdout);
    QString input;

    while(input = qtin.readLine(), input.length() != 1) {
        qtout << "Zla komenda! Prosze wpisac poprawna liczbe" << endl;
        qtin.reset();
    }
    return input[0];
}
//** KONIEC Funkcje ulatwiajace zmniejszenie redundancji kodu**//

//** Funkcje wyboru stanów; dla odpowiednich stanów **//
void Logic::chooseEnd() {
    QChar out = output();
    char c = out.toLatin1();

    switch(c) {
        case 'Z':
        case 'z':
        case '1':
            newGame();
            newBreak(State::Game);
            break;
        case 'M':
        case 'm':
        case '0':
            newBreak(State::Menu);
            break;
        default:
            setBad(true);
            setNext(true);
            break;
    }
}

void Logic::chooseGameMenu() {
    QChar out = output();
    char c = out.toLatin1();

    switch(c) {
        case 'W':
        case 'w':
        case '1':
            newBreak(State::Game);
            break;
        case 'Z':
        case 'z':
        case '2':
            newBreak(State::Save);
            break;
        case 'M':
        case 'm':
        case '0':
            cleanBuffor();
            save("ranking");
            newBreak(State::End);
            break;
        default:
            setBad(true);
            setNext(true);
            break;
    }
}

void Logic::chooseLoad() {
    QTextStream qtin(stdin);
    QTextStream qtout(stdout);
    QChar out = output();
    char c = out.toLatin1();

    switch(c) {
        case 'Z':
        case 'z':
        case '1':
            qtout << "Podaj nazwe pliku z zapisana gra" << endl;
            qtin >> filename;
            if(!load(filename)) {
                qtout << "Bledny plik" << endl;
                qtin.readLine();
                qtin.reset();
                newBreak(State::Menu);
                break;
            }
            newBreak(State::Game);
            break;
        case 'W':
        case 'w':
        case '0':
            newBreak(State::Menu);
            break;
        default:
            setBad(true);
            setNext(true);
            break;
    }
}

void Logic::chooseMenu() {
    QTextStream qtin(stdin);
    QTextStream qtout(stdout);
    QString name;
    QChar out = output();
    char c = out.toLatin1();

    switch(c) {
        case 'G':
        case 'g':
        case '1':
            system("cls");
            qtout << "Podaj swoje imie" << endl;
            qtin >> name;
            setName(name);
            qtin.reset();
            newGame();
            newBreak(State::Game);
            break;
        case 'W':
        case 'w':
        case '2':
            newBreak(State::Load);
            break;
        case 'R':
        case 'r':
        case '3':
            newBreak(State::Ranking);
            break;
        case 'O':
        case 'o':
        case '4':
            newBreak(State::Options);
            break;
        case 'K':
        case 'k':
        case '0':
            setEnd(true);
            newBreak(State::Menu);
            break;
        default:
            setBad(true);
            setNext(true);
            break;
    }
}

void Logic::chooseOptions() {
    QChar out = output();
    char c = out.toLatin1();

    switch(c) {
        case 'Z':
        case 'z':
        case '1':
            options();
        case 'W':
        case 'w':
        case '0':
            newBreak(State::Menu);
            break;
        default:
            setBad(true);
            setNext(true);
            break;
    }
}

void Logic::chooseSave() {
    QTextStream qtin(stdin);
    QTextStream qtout(stdout);
    QChar out = output();
    char c = out.toLatin1();

    switch(c) {
        case 'Z':
        case 'z':
        case '1':
            qtout << "Podaj nazwe pliku pod jaka zapisac gre" << endl;
            qtin >> filename;
            save(filename);
        case 'W':
        case 'w':
        case '0':
            newBreak(State::GameMenu);
            break;
        default:
            setBad(true);
            setNext(true);
            break;
    }
}
//** KONIEC Funkcje wyboru stanów; dla odpowiednich stanów **//

void Logic::play() {
    if(getGameOver()) {
        cleanBuffor();
        save("ranking");
        newBreak(State::End);
        return;
    }

    QChar out = output();
    char c = out.toLatin1();

    switch(c) {
        case 'W':
        case 'w':
        case '8':
            setBack();
            moveUp();
            setNextNumber(true);
            setNoBack(false);
            newBreak(State::Game);
            break;
        case 'S':
        case 's':
        case '2':
            setBack();
            moveDown();
            setNextNumber(true);
            setNoBack(false);
            newBreak(State::Game);
            break;
        case 'A':
        case 'a':
        case '4':
            setBack();
            moveLeft();
            setNextNumber(true);
            setNoBack(false);
            newBreak(State::Game);
            break;
        case 'D':
        case 'd':
        case '6':
            setBack();
            moveRight();
            setNextNumber(true);
            setNoBack(false);
            newBreak(State::Game);
            break;
        case 'X':
        case 'x':
        case '5':
            setNoBack(false);
            newBreak(State::GameMenu);
            break;
        case 'Q':
        case 'q':
        case '7':
            setNoBack(false);
            getBack();
            newBreak(State::Game);
            break;
        default:
            setNoBack(false);
            setBad(true);
            setNext(true);
            break;
    }
}

int Logic::load(QString filename) {
    QTextStream qtout(stdout);
    loading->cleanBuffor();
    if(!(loading->loading(filename)))
        return 0;
    if(filename == "ranking") {
        this->buffor.clear();
        this->buffor = loading->getBuffor();
    }
    else {
        table.clear();
        this->score = loading->getScore();
        this->size = loading->getSize();
        this->table = loading->getTable();
    }
    return 1;
}

void Logic::save(QString filename) {
    QTextStream qtout(stdout);
    if(filename == "ranking") {
        QPair<QString, int> tmp;
        loading->cleanBuffor();
        load(filename);
        this->buffor = loading->getBuffor();
        tmp.first = getName();
        tmp.second = getScore();
        for(int i = 0; i < this->buffor.size(); i++)
            if(this->buffor.at(i).second < getScore()) {
                this->buffor.insert(i, tmp);
                this->buffor.pop_back();
                break;
            }
        saving->cleanBuffor();
        saving->setBuffor(this->buffor);
        saving->saving(filename);
    }
    else{
        qtout << filename << endl;
        saving->setSize(this->size);
        saving->setScore(this->score);
        saving->setTable(this->table);
        saving->saving(filename);
    }
}

void Logic::options() {
    QTextStream qtin(stdin);
    QTextStream qtout(stdout);
    QString tmpString;
    int tmpSize;
    system("cls");
    qtout << "Jakiego rozmiaru chcesz by byla plansza?" << endl;

    do{
        for(qtout << "Rozmiar: "; tmpString = qtin.readLine(), !(tmpSize = tmpString.toInt());){
            qtout << "Zla komenda! Prosze wpisac poprawna liczbe" << endl;
            qtin.reset();
        }

        if(tmpSize >= 7)
            qtout << "Plansza jest za duza, prosze wybrac rozmiar między 3 a 6" << endl;
        else if(tmpSize <= 2)
            qtout << "Plansza jest za mala, prosze wybrac rozmiar między 3 a 6" << endl;
    }while(tmpSize >= 7 || tmpSize <= 2);

    setSize(tmpSize);
}

//** Funkcje manipulacji planszą **//
void Logic::moveLeft() {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size-1; j++) {
            if (table.at(i).at(j)) {
                for(int k = j+1; k < size; k++) {
                    if(table.at(i).at(j) != table.at(i).at(k) && table.at(i).at(k))
                        break;
                    else if(table.at(i).at(j) == table.at(i).at(k)) {
                        changeTable(i, j, table.at(i).at(j) << 1);
                        changeTable(i, k, 0);
                        setScore(getScore()+table.at(i).at(j));
                        break;
                    }
                }
            }
            else {
                for(int k = j+1; k < size; k++)
                    if(table.at(i).at(k)) {
                        for(int l = k+1; l < size; l++) {
                            if(table.at(i).at(k) != table.at(i).at(l) && table.at(i).at(l))
                                break;
                            else if(table.at(i).at(k) == table.at(i).at(l)) {
                                changeTable(i, k, table.at(i).at(k) << 1);
                                changeTable(i, l, 0);
                                setScore(getScore()+table.at(i).at(k));
                                break;
                            }
                        }
                        changeTable(i, j, table.at(i).at(k));
                        changeTable(i, k, 0);
                        break;
                    }
            }
        }
    }
}

void Logic::moveRight() {
    for(int i = 0; i < size; i++) {
        for(int j = size; j > 1; j--) {
            if (table.at(i).at(j-1)) {
                for(int k = j; k > 1; k--) {
                    if(table.at(i).at(j-1) != table.at(i).at(k-2) && table.at(i).at(k-2))
                        break;
                    else if(table.at(i).at(j-1) == table.at(i).at(k-2)) {
                        changeTable(i, j-1, table.at(i).at(j-1) << 1);
                        changeTable(i, k-2, 0);
                        setScore(getScore()+table.at(i).at(j-1));
                        break;
                    }
                }
            }
            else {
                for(int k = j; k > 1; k--)
                    if(table.at(i).at(k-2)) {
                        for(int l = k-2; l > 1; l--) {
                            if(table.at(i).at(k-2) != table.at(i).at(l-1) && table.at(i).at(l-1))
                                break;
                            else if(table.at(i).at(k-2) == table.at(i).at(l-1)) {
                                changeTable(i, k-2, table.at(i).at(k-2) << 1);
                                changeTable(i, l-1, 0);
                                setScore(getScore()+table.at(i).at(k-2));
                                break;
                            }
                        }
                        changeTable(i, j-1, table.at(i).at(k-2));
                        changeTable(i, k-2, 0);
                        break;
                    }
            }
        }
    }
}

void Logic::moveUp() {
    for(int i = 0; i < size-1; i++) {
        for(int j = 0; j < size; j++) {
            if (table.at(i).at(j)) {
                for(int k = i+1; k < size; k++) {
                    if(table.at(i).at(j) != table.at(k).at(j) && table.at(k).at(j))
                        break;
                    else if(table.at(i).at(j) == table.at(k).at(j)) {
                        changeTable(i, j, table.at(i).at(j) << 1);
                        changeTable(k, j, 0);
                        setScore(getScore()+table.at(i).at(j));
                        break;
                    }
                }
            }
            else {
                for(int k = i+1; k < size; k++)
                    if(table.at(k).at(j)) {
                        for(int l = k+1; l < size; l++) {
                            if(table.at(k).at(j) != table.at(l).at(j) && table.at(l).at(j))
                                break;
                            else if(table.at(k).at(j) == table.at(l).at(j)) {
                                changeTable(k, j, table.at(k).at(j) << 1);
                                changeTable(l, j, 0);
                                setScore(getScore()+table.at(k).at(j));
                                break;
                            }
                        }
                        changeTable(i, j, table.at(k).at(j));
                        changeTable(k, j, 0);
                        break;
                    }
            }
        }
    }
}

void Logic::moveDown() {
    for(int i = size; i > 1; i--) {
        for(int j = 0; j < size; j++) {
            if (table.at(i-1).at(j)) {
                for(int k = i; k > 1; k--) {
                    if(table.at(i-1).at(j) != table.at(k-2).at(j) && table.at(k-2).at(j))
                        break;
                    else if(table.at(i-1).at(j) == table.at(k-2).at(j)) {
                        changeTable(i-1, j, table.at(i-1).at(j) << 1);
                        changeTable(k-2, j, 0);
                        setScore(getScore()+table.at(i-1).at(j));
                        break;
                    }
                }
            }
            else {
                for(int k = i; k > 1; k--)
                    if(table.at(k-2).at(j)) {
                        for(int l = k-2; l > 1; l--) {
                            if(table.at(k-2).at(j) != table.at(l-1).at(j) && table.at(l-1).at(j))
                                break;
                            else if(table.at(k-2).at(j) == table.at(l-1).at(j)) {
                                changeTable(k-2, j, table.at(k-2).at(j) << 1);
                                changeTable(l-1, j, 0);
                                setScore(getScore()+table.at(k-2).at(j));
                                break;
                            }
                        }
                        changeTable(i-1, j, table.at(k-2).at(j));
                        changeTable(k-2, j, 0);
                        break;
                    }
            }
        }
    }
}
//** KONIEC Funkcje manipulacji planszą **//

//** Funkcje zmiany planszy **//
void Logic::changeTable(int col, int row, int value) {
    table[col][row] = value;
}

void Logic::clearTable() {
    table.clear();
    QVector<int> tmp;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++)
            tmp.push_back(0);
        table.push_back(tmp);
        tmp.clear();
    }
}

void Logic::randTable() {
    int count=0;
    int random;
    int value;
    int randomRow;
    int randomCol;
    srand(static_cast<unsigned int>(time(nullptr)));

    random = rand()%100+1;

    if(random < 86)
        value = 2;
    else
        value = 4;

    do{
        randomRow = (rand() % getSize());
        randomCol = (rand() % getSize());
        count++;
        if(count > 400) {
            setGameOver(true);
            break;
        }
    }while(table.at(randomCol).at(randomRow));

    changeTable(randomCol, randomRow, value);
}
//** KONIEC Funkcje zmiany planszy **//

//** Setery i getery **//
void Logic::setBack() {
    QVector< QVector<int> > tmpTable;
    QVector<int> tmpRow;
    for (auto Row : table) {
        for (auto i : Row)
            tmpRow.push_back(i);
        tmpTable.push_back(tmpRow);
        tmpRow.clear();
    }
    if(moves.size()>=3)
        moves.pop_front();
    moves.push_back(tmpTable);
}

void Logic::getBack() {
    QTextStream qtout(stdout);
    if(!moves.size()) {
        setNoBack(true);
        return;
    }

    clearTable();

    QVector<int> tmpRow;

    QVector< QVector<int> > tmpTable = moves.back();

    for(int i = 0; i < tmpTable.size(); i++) {
        tmpRow = tmpTable[i];
        for(int j = 0; j < tmpRow.size(); j++)
            changeTable(i, j, tmpRow[j]);
    }
    moves.pop_back();
}
//** KONIEC Setery i getery **//
