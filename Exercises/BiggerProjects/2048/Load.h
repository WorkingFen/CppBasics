//
// Created by Piotr Zawadka on 20.04.2018.
//

#pragma once

#include <QTextStream>
#include <QString>
#include <QPair>
#include <QVector>
#include <QFile>
#include <fstream>

//Ładowanie plików
class Load {
private:
    int score;
    int size;
    QVector< QPair<QString,int> > buffor;
    QVector< QVector<int> > table;

protected:

public:
    Load():score(0), size(0){}

    int loading(QString filename);

    void cleanBuffor() { this->buffor.clear(); }

    int getScore() { return this->score; }
    int getSize() { return this->size; }
    QVector< QPair<QString,int> > getBuffor() { return this->buffor; }
    QVector< QVector<int> > getTable() { return this->table; }
};

