//
// Created by Piotr Zawadka on 20.04.2018.
//

#include "Load.h"

//Główna funkcja ładowania pliku
int Load::loading(QString filename) {
    QFile load(filename + ".txt");

    QVector< QVector<int> > tmpTable;
    QVector<int> tmpRow;
    int number;
    QPair<QString, int> tmpPair;
    QString tmp;
    int tmpScore;

    if(!load.open(QIODevice::ReadOnly | QIODevice::Text)) {         ///Jeśli plik nie będzie poprawnie otwarty
        return 0;       //Error
    }
    else {
        QTextStream in(&load);

        if(filename == "ranking") {
            for(int i = 0; i < 10; i++) {
                in >> tmp;
                in >> tmpScore;
                tmpPair.first = tmp;
                tmpPair.second = tmpScore;
                buffor.push_back(tmpPair);
            }
        }
        else {
            in >> size;
            in >> score;
            table.clear();
            for(int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    in >> number;
                    tmpRow.push_back(number);
                }
                tmpTable.push_back(tmpRow);
                tmpRow.clear();
            }
            table = tmpTable;
        }

    }
    load.close();
    return 1;       //Sukces
}
