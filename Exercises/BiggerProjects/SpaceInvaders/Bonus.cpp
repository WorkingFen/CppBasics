/**
* Name: Bonus.cpp
* Purpose: Class Bonus
*
* @author Fenris
* @version 0.88a 03/05/2017
*/
#include "Bonus.h"

Bonus::Bonus(const unsigned x, const unsigned y, Invader &owner, Textures &textures, const BonusType type): hit(false), owner(owner), type(type)
{
    switch(type){
        case Bonus::BONUS_1:                            //Bonus 1
            this->bonus_txtr = &(textures.BONUS_1);
            this->SPEED = 5;
            break;
        case Bonus::BONUS_2:                            //Bonus 2
            this->bonus_txtr = &(textures.BONUS_2);
            this->SPEED = 3;
            break;
        case Bonus::BONUS_3:                            //Bonus 3
            this->bonus_txtr = &(textures.BONUS_3);
            this->SPEED = 5;
            break;
        case Bonus::BONUS_4:                            //Bonus 4
            this->bonus_txtr = &(textures.BONUS_4);
            this->SPEED = 4;
            break;
        case Bonus::BONUS_5:                            //Bonus 5
            this->bonus_txtr = &(textures.BONUS_5);
            this->SPEED = 3;
            break;
        case Bonus::BONUS_6:                            //Bonus 6
            this->bonus_txtr = &(textures.BONUS_6);
            this->SPEED = 5;
            break;
        case Bonus::BONUS_7:                            //Bonus 7
            this->bonus_txtr = &(textures.BONUS_7);
            this->SPEED = 5;
            break;
        case Bonus::BONUS_8:                            //Bonus 8
            this->bonus_txtr = &(textures.BONUS_8);
            this->SPEED = 3;
            break;
        default:
            break;
    }
    owner.incBonusesOnScreen();
    this->sprite.setTexture(*(this->bonus_txtr), true);
    this->sprite.setOrigin(this->WIDTH / 2, this->HEIGHT / 2);
    this->sprite.setPosition(x, y);
}

void Bonus::getBonus(const BonusType type, LivesDisplay &lives, unsigned &game_score, PlayerLaser &laser)
{
    switch(type){
        case Bonus::BONUS_1:                            //Bonus 1
            lives.addLife();
            break;
        case Bonus::BONUS_2:                            //Bonus 2
            lives.removeLife();
            break;
        case Bonus::BONUS_3:                            //Bonus 3
            break;
        case Bonus::BONUS_4:                            //Bonus 4
            game_score += 200;
            break;
        case Bonus::BONUS_5:                            //Bonus 5
            if(game_score<500)
                game_score = 0;
            else
                game_score -= 500;
            break;
        case Bonus::BONUS_6:                            //Bonus 6
            laser.setSpeed((laser.getSpeed())+1);
            break;
        case Bonus::BONUS_7:                            //Bonus 7
            laser.nowDouble();
            laser.setSpeed((laser.getSpeed())-2);
            break;
        case Bonus::BONUS_8:                            //Bonus 8
            laser.setSpeed((laser.getSpeed())-1);
            break;
        default:
            break;
    }
}

void Bonus::move()
{
    this->sprite.move(0, this->SPEED);
}

void Bonus::draw(sf::RenderWindow &window)
{
    window.draw(this->sprite);
}

bool Bonus::checkCollide(const unsigned x, const unsigned y) const
{
    if(this->sprite.getGlobalBounds().contains(x, y))
        return true;
    return false;
}

bool Bonus::checkCollide(const sf::FloatRect rect) const
{
    if(rect.intersects(this->sprite.getGlobalBounds()))
        return true;
    return false;
}
