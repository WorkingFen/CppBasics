//
// Created by Piotr Zawadka on 20.04.2018.
//

#pragma once

#include <QTextStream>
#include <QString>
#include <QPair>
#include <QVector>
#include <QFile>
#include <utility>
#include <fstream>

//Zapisywanie plików
class Save {
private:
    int score;
    int size;
    QVector< QPair<QString,int> > buffor;
    QVector< QVector<int> > table;

protected:

public:
    Save(): score(0), size(0){}

    void saving(QString filename);

    void cleanBuffor() { this->buffor.clear(); }

    void setScore(int score) { this->score = score; }
    void setSize(int size) { this->size = size; }
    void setBuffor(QVector< QPair<QString,int> > buffor) { this->buffor = std::move(buffor); }
    void setTable(QVector< QVector<int> > table) { this->table = std::move(table); }
};
