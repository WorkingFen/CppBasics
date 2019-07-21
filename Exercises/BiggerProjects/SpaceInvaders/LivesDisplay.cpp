/**
* Name: LivesDisplay.cpp
* Purpose: Class LivesDisplay
*
* @author Fenris
* @version 0.94a 03/05/2017
*/
#include <sstream>
#include "LivesDisplay.h"
#include "game.h"

void LivesDisplay::reset()
{
    for (auto& ship : this->ships)
        delete ship;
    this->ships.clear();

    this->lives = this->LIVES_START;

    for (unsigned i = 0; i < (this->lives - 1); ++i){               //Subtract one, because it's already shown on the screen, and you're playing with it
        sf::Sprite *sprite = new sf::Sprite;
        sprite->setTexture(this->textures.SHIP_1);
        sprite->setPosition(this->X + 155 + (i * 55), this->Y+18);
        this->ships.push_back(sprite);
    }
}

LivesDisplay::LivesDisplay(Textures &textures): lives(LIVES_START), textures(textures)
{
    this->reset();
}

LivesDisplay::~LivesDisplay()
{
    for (auto& ship : this->ships)
        delete ship;
    this->ships.clear();
}

void LivesDisplay::removeLife()
{
    if (this->lives > 1){
        delete this->ships[this->lives - 2];
        this->ships.pop_back();
    }

    if (this->lives > 0)
        --this->lives;

    if (lives == 0)
        Globals::GAME_STATE = Globals::States::GAME_OVER;
}

void LivesDisplay::addLife()
{
    sf::Sprite *sprite = new sf::Sprite;
    sprite->setTexture(this->textures.SHIP_1);
    sprite->setPosition(this->X + 155 + ((this->lives - 1) * 55), this->Y+18);
    this->ships.push_back(sprite);

    ++this->lives;
}

void LivesDisplay::setLives(const unsigned num)
{
    while (this->lives < num)
        this->addLife();

    while (this->lives > num)
        this->removeLife();
}

void LivesDisplay::draw(sf::RenderWindow &window)
{
    Game::draw_text(window, "LIFE" , this->X + 70, this->Y + 8, sf::Color::White, 30);

    std::ostringstream lives_left;
    lives_left << this->lives;
    Game::draw_text(window, lives_left.str(), this->X + 120, this->Y + 2, sf::Color::White, 36);

    for (auto& ship : this->ships)
        window.draw(*ship);
}
