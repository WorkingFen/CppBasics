/**
* Name: PlayerLaser.cpp
* Purpose: Class PlayerLaser
*
* @author Fenris
* @version 0.94a 03/05/2017
*/
#include <cmath>
#include "PlayerLaser.h"

PlayerLaser::PlayerLaser(): is_shooting(false), is_shooting2(false), is_double(false)
{
    this->laser = sf::RectangleShape(sf::Vector2f(this->WIDTH, this->HEIGHT));
    this->laser.setPosition(999, 999);                                              //Position it off screen until shot
    this->laser.setFillColor(sf::Color::White);
    this->laser.setOrigin(round(this->WIDTH / 2), this->HEIGHT);                    //Make the origin bottom of laser

    this->laser2 = sf::RectangleShape(sf::Vector2f(this->WIDTH, this->HEIGHT));
    this->laser2.setPosition(999, 999);                                              //Position it off screen until shot
    this->laser2.setFillColor(sf::Color::White);
    this->laser2.setOrigin(round(this->WIDTH / 2), this->HEIGHT);                    //Make the origin bottom of laser
}

void PlayerLaser::shoot(const unsigned startx, const unsigned starty)
{
    ///You can't shoot while it already has been shot
    if(!this->is_shooting && !this->is_shooting2 && this->is_double){
        this->laser.setPosition(startx-12, starty);
        this->laser2.setPosition(startx+12, starty);
        this->is_shooting = true;
        this->is_shooting2 = true;
    }
    else if(!this->is_shooting && !this->is_double){
        this->laser.setPosition(startx, starty);
        this->is_shooting = true;
    }
}

void PlayerLaser::move(Explosions &explosions)
{
    if(!this->is_shooting && !this->is_shooting2)
        return;

    this->laser.move(0, this->SPEED * -1);
    if(this->is_double)
        this->laser2.move(0, this->SPEED * -1);

    if(this->laser.getPosition().y < 100){
        explosions.newExplosion(sf::Color::Red, this->getShape().getPosition().x, this->getShape().getPosition().y);
        this->stop1();
    }
    if(this->laser2.getPosition().y < 100){
        explosions.newExplosion(sf::Color::Red, this->getShape2().getPosition().x, this->getShape2().getPosition().y);
        this->stop2();
    }
}

void PlayerLaser::stop1()
{
    this->laser.setPosition(999, 999);
    this->is_shooting = false;
}

void PlayerLaser::stop2()
{
    this->laser2.setPosition(999, 999);
    this->is_shooting2 = false;
}

void PlayerLaser::reset()
{
    this->is_double = false;
    this->SPEED = 10;
}
