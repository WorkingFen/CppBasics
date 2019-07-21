/**
* Name: InvaderLaser.cpp
* Purpose: Class InvaderLaser
*
* @author Fenris
* @version 0.88a 03/05/2017
*/
#include "InvaderLaser.h"

InvaderLaser::InvaderLaser(const unsigned x, const unsigned y, const bool will_hurt, Invader &owner): SPEED(6), hit(false), will_hurt(will_hurt), owner(owner), flip_tick(FLIP_TICK_MAX)
{
    owner.incLasersOnScreen();
    this->part1 = sf::RectangleShape(sf::Vector2f(this->WIDTH, this->HEIGHT));
    this->part1.setOrigin(this->WIDTH / 2, this->HEIGHT / 2);
    this->part1.setFillColor(sf::Color::White);

    this->part2 = this->part1;
    this->part3 = this->part2;
    this->part4 = this->part3;

    this->part1.setPosition(x, y);
    this->part2.setPosition(x, y + this->HEIGHT - 2);
    this->part3.setPosition(x, y + (this->HEIGHT - 2) * 2);
    this->part4.setPosition(x, y + (this->HEIGHT - 2) * 3);

    this->part1.setRotation(45);
    this->part2.setRotation(315);
    this->part3.setRotation(45);
    this->part4.setRotation(315);
}

void InvaderLaser::flip()
{
    --this->flip_tick;
    if(this->flip_tick <= 0){
        this->part1.rotate(90);
        this->part2.rotate(90);
        this->part3.rotate(90);
        this->part4.rotate(90);

        this->flip_tick = this->FLIP_TICK_MAX;
    }
}

unsigned InvaderLaser::getX() const
{
    return this->part2.getPosition().x;
}

unsigned InvaderLaser::getY() const
{
    return this->part2.getPosition().y;
}

void InvaderLaser::move()
{
    this->flip();
    this->part1.move(0, this->SPEED);
    this->part2.move(0, this->SPEED);
    this->part3.move(0, this->SPEED);
    this->part4.move(0, this->SPEED);
}

void InvaderLaser::draw(sf::RenderWindow &window)
{
    window.draw(this->part1);
    window.draw(this->part2);
    window.draw(this->part3);
    window.draw(this->part4);
}

bool InvaderLaser::checkCollide(const unsigned x, const unsigned y) const
{
    if(this->part1.getGlobalBounds().contains(x, y) || this->part2.getGlobalBounds().contains(x, y) || this->part3.getGlobalBounds().contains(x, y) || this->part4.getGlobalBounds().contains(x, y))
        return true;
    return false;
}

bool InvaderLaser::checkCollide(const sf::FloatRect rect) const
{
    if(rect.intersects(this->part1.getGlobalBounds()) || rect.intersects(this->part2.getGlobalBounds()) || rect.intersects(this->part3.getGlobalBounds()) || rect.intersects(this->part4.getGlobalBounds()))
        return true;
    return false;
}
