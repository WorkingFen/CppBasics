//
// Created by Piotr Zawadka on 20.04.2018.
//

#pragma once

#include <QPair>
#include <QVector>
#include <QString>
#include <QTextStream>
#include "interface.h"
#include "Load.h"
#include "Save.h"
#include <utility>
#include "MyList.h"

//Enumerator stanów
enum class State{Menu, Save, Load, Options, GameMenu, Ranking, Game, End};

//Główna klasa z zawartą tutaj logiką gry
class Logic {
private:
    Load* loading = new Load();                 //Odczyt
    Save* saving = new Save();                  //Zapis
    QVector< QPair<QString,int> > buffor;
    //List::MyList< QVector< QVector<int> > > moves;   //Trzy poprzednie ruchy
    QVector< QVector< QVector<int> > > moves;   //Trzy poprzednie ruchy
    QVector< QVector<int> > table;

    State gameState;
    QString filename;
    QString name;           //Nazwa gracza

    int score;
    int size;

    bool bad;               //Zla komenda
    bool end;               //Koniec gry
    bool gameOver;          //Przegrana
    bool next;              //Nastepny stan
    bool nextNumber;        //Kolejny numer
    bool noBack;            //Brak poprzedniego ruchu

protected:

public:
    Logic(): score(0), size(4), bad(false), end(false), gameOver(false), next(false),
        nextNumber(false), noBack(true) {

        this->gameState = State::Menu;          //Zaczynamy od menu
        clearTable();
    };

    /** Funkcje wyboru stanów; dla odpowiednich stanów **/
    void chooseEnd();
    void chooseGameMenu();
    void chooseLoad();
    void chooseMenu();
    void chooseOptions();
    void chooseSave();
    /* KONIEC Funkcje wyboru stanów; dla odpowiednich stanów */

    void play();
    int load(QString filename);
    void save(QString filename);
    void options();

    /** Funkcje manipulacji planszą **/
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    /* KONIEC Funkcje manipulacji planszą */

    /** Funkcje usuwania redundancji **/
    void newBreak(State state);
    void newGame();
    QCharRef output();
    /* KONIEC Funkcje usuwania redundancji */

    /** Funkcje zmiany planszy **/
    void changeTable(int row, int col, int value);
    void clearTable();
    void randTable();
    void cleanBuffor() { this->buffor.clear(); }
    /* KONIEC Funkcje zmiany planszy */

    /** Setery i getery **/
    void setBack();
    void getBack();

    void setBad(bool bad) { this->bad = bad; }
    bool getBad() { return this->bad; }

    QVector< QPair<QString,int> > getBuffor() { return this->buffor; }

    void setEnd(bool end) { this->end = end; }
    bool getEnd() { return this->end; }

    void setGameOver(bool gameOver) { this->gameOver = gameOver; }
    bool getGameOver() { return this->gameOver; }

    void setName(QString name) { this->name = std::move(name); }
    QString getName() { return this->name; }

    void setNext(bool next) { this->next = next; }
    bool getNext() { return this->next; }

    void setNextNumber(bool nextNumber) { this->nextNumber = nextNumber; }
    bool getNextNumber() { return this->nextNumber; }

    void setNoBack(bool noBack) { this->noBack = noBack; }
    bool getNoBack() { return this->noBack; }

    void setScore(int score) { this->score = score; }
    int getScore() { return this->score; }

    void setSize(int size) { this->size = size; }
    int getSize() { return this->size; }

    void setState(State state) { this->gameState = state; }
    State getState() { return this->gameState; }

    void setTable(QVector< QVector<int> > table) { this->table = std::move(table); }
    QVector< QVector<int> > getTable() { return table; }
    /* KONIEC Setery i getery */

};
