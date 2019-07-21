//
// Created by Piotr Zawadka on 20.04.2018.
//

#include <iostream>
#include "Save.h"

//Główna funkcja zapisywania pliku
void Save::saving(QString filename) {
    QFile save(filename + ".txt");

    QString tmp;
    int tmpScore;

    if(!save.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QString msg = "An error occurred while saving to file " + filename;
        throw msg;          //Błąd tworzenia pliku
    }

    QTextStream out(&save);

    if(filename == "ranking") {
        for(auto tmpPair : buffor) {        //Przejście po całym buforze
            tmp = tmpPair.first;
            tmpScore = tmpPair.second;
            out << tmp << "\t" << tmpScore << "\n";
        }
    }
    else {
        out << this->size << "\n";
        out << this->score << "\n";

        for (auto tmpRow : table) {
            for (auto i : tmpRow)
                out << i << " ";
        }
        out << "\n";
    }

    save.close();
}
