/**
* Name: Info.cpp
* Purpose: Class Info
*
* @author Fenris
* @version 1.02a 14/05/2017
*/
#include "Info.h"
#include "game.h"

Info::Info(Textures &textures, ScoreDisplay &score_disp, ClockDisplay &clock_disp): score_disp(score_disp), clock_disp(clock_disp), str_char_on(0), line_on(1), sprite_drawn(false), display_scores(false)
{
    this->invader1.setTexture(textures.INVADER_11);
    this->invader2.setTexture(textures.INVADER_21);
    this->invader3.setTexture(textures.INVADER_31);
    this->invader4.setTexture(textures.INVADER_41);

    this->invader1.setPosition((Globals::SCREEN_WIDTH / 2) - 156, 390);
    this->invader2.setPosition((Globals::SCREEN_WIDTH / 2) - 156, 440);
    this->invader3.setPosition((Globals::SCREEN_WIDTH / 2) - 158, 491);
    this->invader4.setPosition((Globals::SCREEN_WIDTH / 2) - 162, 544);

    this->invader1.setScale(1.7, 1.7);
    this->invader2.setScale(1.7, 1.7);
    this->invader3.setScale(1.7, 1.7);
    this->invader4.setScale(1.7, 1.7);
}

void Info::reset()
{
    this->line_on = 1;
    this->str_char_on = 0;
    this->sprite_drawn = false;
    this->display_scores = false;
}

void Info::drawLine(sf::RenderWindow &window, const std::string msg, const unsigned x, const unsigned y, const unsigned wait, const unsigned line_num, sf::Sprite *sprite, sf::Color color, unsigned size)
{
    ///Don't do anything until info isn't done with previous line
    if (line_num > this->line_on)
        return;

    ///If it's okey it will drew next line
    else if (line_num < this->line_on){
        if (sprite != nullptr)
            window.draw(*sprite);

        Game::draw_text(window, msg, x, y, color, size);
        return;
    }

    if (sprite != nullptr && this->display_scores){
        window.draw(*sprite);
        if (!this->sprite_drawn){
            sf::sleep(sf::milliseconds(wait));
            this->sprite_drawn = true;
        }
    }

    ///Draw the line letter by letter
    std::ostringstream ss;
    for (unsigned i = 0; i <= this->str_char_on; ++i)
        ss << msg[i];

    if (this->str_char_on < msg.length())
        ++this->str_char_on;
    else{
        ++this->line_on;
        this->str_char_on = 0;
        this->sprite_drawn = false;
    }

    Game::draw_text(window, ss.str(), x, y, color, size);
    sf::sleep(sf::milliseconds(wait));
}

void Info::draw(sf::RenderWindow &window)
{
    this->score_disp.draw(window);
    this->clock_disp.draw(window);

    this->drawLine(window, "PLAY", (Globals::SCREEN_WIDTH / 2) - 80, 70, this->PAUSE, 1, nullptr, sf::Color::White, 80);
    this->drawLine(window, "SPACE INVADERS", (Globals::SCREEN_WIDTH / 2) - 350, 120, this->PAUSE, 2, nullptr, sf::Color::White, 128);

    if (this->line_on >= 3)
    {
        Game::draw_text(window, "* SCORE  ADVANCE  TABLE *", (Globals::SCREEN_WIDTH / 2)- 310, 270, sf::Color::White, 64);

        if (this->line_on == 3)
            ++this->line_on;

        else if (this->line_on == 4 && this->str_char_on == 1)
        {
            sf::sleep(sf::milliseconds(300));
            this->display_scores = true;
        }
    }

    this->drawLine(window, " = 4 0    P O I N T S", (Globals::SCREEN_WIDTH / 2) - 113, 380, this->PAUSE, 4, &this->invader1, sf::Color::White, 36);
    this->drawLine(window, " = 3 0    P O I N T S", (Globals::SCREEN_WIDTH / 2) - 113, 435, this->PAUSE, 5, &this->invader2, sf::Color::White, 36);
    this->drawLine(window, " = 2 0    P O I N T S", (Globals::SCREEN_WIDTH / 2) - 113, 490, this->PAUSE, 6, &this->invader3, sf::Color::White, 36);
    this->drawLine(window, " = 1 0    P O I N T S", (Globals::SCREEN_WIDTH / 2) - 113, 545, this->PAUSE, 7, &this->invader4, sf::Color::White, 36);

    Game::draw_text(window, "PRESS                 TO RETURN", (Globals::SCREEN_WIDTH / 2) - 205, 670, sf::Color::White, 38);
    Game::draw_text(window, "ESCAPE", (Globals::SCREEN_WIDTH / 2) - 75, 670, sf::Color::Green, 38);
}

