/**
* Name: Stars.h
* Purpose: Declaration of class Stars
*
* @author Fenris
* @version 0.81b 03/05/2017
*/
#pragma once

#include <SFML/Graphics.hpp>
#include "globals.h"
#include "rand.h"

class Stars;

///Vector which has Stars in it
typedef std::vector<Stars*> Constellation;

///Class of Stars
class Stars{
    private:
        static constexpr unsigned WIDTH = 1;                    ///<Width of star
        static constexpr unsigned HEIGHT = 1;                   ///<Height of star

        const int SPEED;                                        ///<How fast the star moves.
        bool hit;                                               ///<Whether or not hit something and about to be removed.
        int shot_chance = 60;                                   ///<1/Chance that we will see star on scene

        sf::RectangleShape part;                                ///<Shape of star
        sf::RenderWindow &window;                               ///<Where it will be displayed

        ///Create star and push it to vector
        /**
        \param window Where it will be displayed
        \param x X Position of Star on scene
        \param scale How much bigger this star should be
        */
        void shootStar(sf::RenderWindow &window, const unsigned x, float scale);
        ///Create stars that will be displayed
        /**
        \param window Where it will be displayed
        */
        void shootStars(sf::RenderWindow &window);
        ///Move stars
        void moveStars();

        Constellation constellation;                              ///<Vector for keeping stars

    public:
        ///Default constructor of Stars
        /**
        \param window Where it should be displayed
        \param x X Position of Star on scene
        \param scale How much bigger this star should be
        */
        Stars(sf::RenderWindow &window, const unsigned x, float scale);
        ///Default destructor of Stars
        ~Stars(){}

        ///See if star was hit
        bool isHit() const { return this->hit; }
        ///Set that this star got hit
        void setHit() { this->hit = true; }
        ///Get the constellation
        Constellation& getStars(){ return this->constellation; };

        ///Update stars to get them moving and shooting
        /**
        \param window Where to display the stars
        */
        void updateStars(sf::RenderWindow &window);

        ///Remove stars that got hit
        void removeHitStars();
        ///Draw stars
        void drawStars();

        ///Check if star gone to far
        void checkHitEdge();

        ///Get X Position of star
        unsigned getX() const;
        ///Get Y Position of star
        unsigned getY() const;
        ///Move star
        void move();
        ///Display stars on scene
        /**
        \param window Where to display them
        */
        void draw(sf::RenderWindow &window);
};
