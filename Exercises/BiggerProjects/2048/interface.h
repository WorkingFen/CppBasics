//
// Created by Piotr Zawadka on 20.04.2018.
//

#pragma once

#include <QTextStream>
#include <QString>
#include <iostream>

//Namespace z napisami dla odpowiednich stanów
namespace interface {
    extern const QString filepathRanking;       //Ścieżka gdzie znajduje się plik ranking.txt
                                                //"" gdy w folderze z programem
    void data();
    void menu();
    void gameMenu();
    void options();
    void load();
    void save();
};
