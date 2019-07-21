/**
* Name: Stars.cpp
* Purpose: Class Stars
*
* @author Fenris
* @version 0.88a 03/05/2017
*/
#include "Stars.h"

Stars::Stars(sf::RenderWindow &window, const unsigned x, float scale): SPEED(5), hit(false), window(window)
{
    this->part = sf::RectangleShape(sf::Vector2f(this->WIDTH, this->HEIGHT));
    this->part.setOrigin(this->WIDTH / 2, this->HEIGHT / 2);
    this->part.setFillColor(sf::Color(250,250,210,150));
    this->part.setScale(scale , scale);

    this->part.setPosition(x, 0);
}

void Stars::shootStar(sf::RenderWindow &window, unsigned x, float scale)
{
    this->constellation.push_back(new Stars(window, x, scale));
}

void Stars::shootStars(sf::RenderWindow &window)
{
    int i = Rand::random(1, this->shot_chance);
    int x = Rand::random(1, Globals::SCREEN_WIDTH);
    switch(i){
        case 1:
            this->shootStar(window, x, 1);
            break;
        case 2:
            this->shootStar(window, x, 2);
            break;
        case 3:
            this->shootStar(window, x, 3);
            break;
        case 4:
            this->shootStar(window, x, 4);
            break;
        default:
            break;
    }
}

void Stars::moveStars()
{
    for(auto& star : this->constellation)
        star->move();
}

void Stars::removeHitStars()
{
    for(unsigned i = 0; i < this->constellation.size(); ++i){
        Stars *star = constellation[i];
        star->checkHitEdge();
        if(star->isHit()){
            delete star;
            this->constellation.erase(constellation.begin() + i);
        }
    }
}

void Stars::updateStars(sf::RenderWindow &window)
{
    this->shootStars(window);
    this->removeHitStars();
    this->moveStars();
}

void Stars::drawStars()
{
    for(auto& star : this->constellation)
        star->draw(this->window);
}

void Stars::checkHitEdge()
{
    unsigned int y = getY();

    if (y >= (Globals::SCREEN_HEIGHT + 20))
        this->setHit();

    this->hit = false;
}

unsigned Stars::getX() const
{
    return this->part.getPosition().x;
}

unsigned Stars::getY() const
{
    return this->part.getPosition().y;
}

void Stars::move()
{
    this->part.move(0, this->SPEED);
}

void Stars::draw(sf::RenderWindow &window)
{
    window.draw(this->part);
}
