//
// Created by Piotr Zawadka on 20.04.2018.
//

#include <cstdio>
#include "Show.h"

int main(int argc, char *argv[]) {
    QTextStream qtin(stdin);
    auto* logic = new Logic();              //Nowa logika
    auto* window = new Show(logic);         //Nowe wyświetlanie

    interface::data();
    qtin.readLine();
    qtin.reset();

    do{                                     //Pętla gry i stanów
        if (logic->getState() == State::Menu)
            window->menu();
        else if (logic->getState() == State::Game)
            window->game();
        else if (logic->getState() == State::GameMenu)
            window->gameMenu();
        else if (logic->getState() == State::End)
            window->end();
        else if (logic->getState() == State::Save)
            window->save();
        else if (logic->getState() == State::Load)
            window->load();
        else if (logic->getState() == State::Options)
            window->options();
        else if (logic->getState() == State::Ranking)
            window->ranking();
    }while(!logic->getEnd());               //Wykonuje się, póki End nie będzie true

    return 0;
}
