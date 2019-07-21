/**
* Name: Save.cpp
* Purpose: Class Save
*
* @author Fenris
* @version 1.08a 14/05/2017
*/
#include <sstream>
#include "Save.h"
#include "game.h"

Save::Save(Textures &textures, ScoreDisplay &score_disp, ClockDisplay &clock_disp, LivesDisplay &lives, unsigned &wave_on, unsigned &score,
           unsigned &minutes, unsigned &seconds, unsigned &miliseconds):
           score_disp(score_disp), clock_disp(clock_disp), frame_on(1), frame_tick(FRAME_TICK_MAX), str_char_on(0), line_on(1), sprite_drawn(false), display_scores(false),
           wave_on(wave_on), minutes(minutes), seconds(seconds), miliseconds(miliseconds), game_score(score), lives(lives)
{
    this->arrow.setTexture(textures.ARROW_1);
    this->arrow.setPosition((Globals::SCREEN_WIDTH / 2) - 456, 390);
    this->arrow.setScale(1.2, 1.2);
}

void Save::flipFrame(Textures &textures)
{
    if(this->frame_on == 1){
        this->arrow.setTexture(textures.ARROW_1, true);
        this->frame_on = 2;
    }
    else if(this->frame_on == 2){
        this->arrow.setTexture(textures.ARROW_2, true);
        this->frame_on = 3;
    }
    else if(this->frame_on == 3){
        this->arrow.setTexture(textures.ARROW_3, true);
        this->frame_on = 4;
    }
    else if(this->frame_on == 4){
        this->arrow.setTexture(textures.ARROW_4, true);
        this->frame_on = 5;
    }
    else if(this->frame_on == 5){
        this->arrow.setTexture(textures.ARROW_5, true);
        this->frame_on = 6;
    }
    else if(this->frame_on == 6){
        this->arrow.setTexture(textures.ARROW_6, true);
        this->frame_on = 7;
    }
    else if(this->frame_on == 7){
        this->arrow.setTexture(textures.ARROW_7, true);
        this->frame_on = 8;
    }
    else if(this->frame_on == 8){
        this->arrow.setTexture(textures.ARROW_8, true);
        this->frame_on = 9;
    }
    else if(this->frame_on == 9){
        this->arrow.setTexture(textures.ARROW_9, true);
        this->frame_on = 10;
    }
    else if(this->frame_on == 10){
        this->arrow.setTexture(textures.ARROW_10, true);
        this->frame_on = 11;
    }
    else if(this->frame_on == 11){
        this->arrow.setTexture(textures.ARROW_11, true);
        this->frame_on = 12;
    }
    else if(this->frame_on == 12){
        this->arrow.setTexture(textures.ARROW_12, true);
        this->frame_on = 13;
    }
    else if(this->frame_on == 13){
        this->arrow.setTexture(textures.ARROW_13, true);
        this->frame_on = 14;
    }
    else if(this->frame_on == 14){
        this->arrow.setTexture(textures.ARROW_14, true);
        this->frame_on = 15;
    }
    else{
        this->arrow.setTexture(textures.ARROW_15, true);
        this->frame_on = 1;
    }
}

void Save::reset()
{
    this->line_on = 1;
    this->str_char_on = 0;
    this->sprite_drawn = false;
    this->display_scores = false;
}

void Save::doSave()
{
    this->save.open(Globals::SAVES_PATH + fileName.c_str() + ".txt");
    if(save.bad()){
        std::string msg = "An error occurred while saving to file " + fileName;
        throw msg;
    }
    this->save << this->game_score << std::endl;
    this->save << this->lives.getLives() << std::endl;
    this->save << this->wave_on << std::endl;
    if(this->wave_on == NULL){
        int wave = 0;
        throw wave;
    }
    this->save << this->minutes << std::endl;
    this->save << this->seconds << std::endl;
    this->save << this->miliseconds << std::endl;
    this->save.close();
}

void Save::drawLine(sf::RenderWindow &window, const std::string msg, const unsigned x, const unsigned y, const unsigned wait, const unsigned line_num,
                    sf::Sprite *sprite, sf::Color color, unsigned size)
{
    ///Don't do anything until Save isn't done with previous line
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

void Save::draw(sf::RenderWindow &window)
{
    this->score_disp.draw(window);
    this->clock_disp.draw(window);

    this->drawLine(window, "PLAY", (Globals::SCREEN_WIDTH / 2) - 80, 70, this->PAUSE, 1, nullptr, sf::Color::White, 80);
    this->drawLine(window, "SPACE INVADERS", (Globals::SCREEN_WIDTH / 2) - 350, 120, this->PAUSE, 2, nullptr, sf::Color::White, 128);

    if (this->line_on >= 3)
    {
        Game::draw_text(window, "* SAVE YOUR GAME *", (Globals::SCREEN_WIDTH / 2)- 225, 270, sf::Color::White, 64);

        if (this->line_on == 3)
            ++this->line_on;

        else if (this->line_on == 4 && this->str_char_on == 1)
        {
            sf::sleep(sf::milliseconds(200));
            this->display_scores = true;
        }
    }

    Game::draw_text(window, "PRESS                 TO RETURN", (Globals::SCREEN_WIDTH / 2) - 205, 670, sf::Color::White, 38);
    Game::draw_text(window, "ESCAPE", (Globals::SCREEN_WIDTH / 2) - 75, 670, sf::Color::Green, 38);

    window.draw(arrow);
    if (!this->sprite_drawn){
        sf::sleep(sf::milliseconds(5));
        this->sprite_drawn = true;
    }

}

void Save::update(Textures &textures)
{
    --this->frame_tick;
    if(this->frame_tick <= 0){
        this->flipFrame(textures);
        this->frame_tick = this->FRAME_TICK_MAX;
    }
}
