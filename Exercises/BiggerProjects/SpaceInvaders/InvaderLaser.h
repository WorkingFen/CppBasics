/**
* Name: InvaderLaser.h
* Purpose: Declaration of class InvaderLaser
*
* @author Fenris
* @version 0.81b 03/05/2017
*/
#pragma once

#include <SFML/Graphics.hpp>
#include "globals.h"
#include "Invader.h"

///Class for InvaderLaser
class InvaderLaser{
    private:
        static constexpr unsigned WIDTH = 2;                            ///<Width of the laser
        static constexpr unsigned HEIGHT = 8;                           ///<Height of the laser
        static constexpr unsigned FLIP_TICK_MAX = 7;                    ///<Flip tick

        const int SPEED;                                                ///<How fast the laser moves.
        bool hit;                                                       ///<Whether or not hit something and about to be removed.
        bool will_hurt;                                                 ///<Whether or not the laser will actually hurt the player.

        Invader &owner;                                                 ///<Whose laser is this?

        sf::RectangleShape part1;                                       ///<Part one of the laser
        sf::RectangleShape part2;                                       ///<Part two of the laser
        sf::RectangleShape part3;                                       ///<Part three of the laser
        sf::RectangleShape part4;                                       ///<Part four of the laser

        unsigned flip_tick;                                             ///<On which flip tick it currently is?

        ///Flip the laser
        void flip();

    public:
        ///Default constructor for InvaderLaser
        /**
        \param x X Position of the laser
        \param y Y Position of the laser
        \param will_hurt Whether or not the laser will hurt the player
        \param owner Whose laser is this?
        */
        InvaderLaser(const unsigned x, const unsigned y, const bool will_hurt, Invader &owner);
        ///Default destructor for InvaderLaser
        ~InvaderLaser() { this->owner.decLasersOnScreen(); }

        ///Check if the laser was hit
        bool isHit() const { return this->hit; }
        ///Check if it will hurt
        bool willHurt() const { return this->will_hurt; }
        ///Set that laser was hit
        void setHit() { this->hit = true; }

        ///Check the X Position of the laser
        unsigned getX() const;
        ///Check the Y Position of the laser
        unsigned getY() const;
        ///Move laser
        void move();
        ///Draw laser on the scene
        /**
        \param window Where it will be displayed?
        */
        void draw(sf::RenderWindow &window);

        ///Check collisions with players ship
        /**
        \param x X Position of players ship
        \param y Y Position of players ship
        */
        bool checkCollide(const unsigned x, const unsigned y) const;
        ///Check collisions with players ship
        /**
        \param rect Rectangle of players ship
        */
        bool checkCollide(const sf::FloatRect rect) const;
};
