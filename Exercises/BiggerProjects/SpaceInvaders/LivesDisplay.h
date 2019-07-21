/**
* Name: LivesDisplay.h
* Purpose: Declaration of class LivesDisplay
*
* @author Fenris
* @version 0.86a 02/05/2017
*/
#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Textures.h"

///Class for Lives Display
class LivesDisplay{
    private:
        static constexpr unsigned X = 0;                ///<X Position on start
        static constexpr unsigned Y = 685;              ///<Y Position on start

        static constexpr unsigned LIVES_START = 3;      ///<Lives at the beginning

        std::vector<sf::Sprite*> ships;                 ///<Vector to display sprites which represents the amount-1 lives you have

        unsigned lives;                                 ///<Current number of lives

        Textures &textures;                             ///<Textures for lives to display

    public:
        ///Default constructor for LivesDisplay
        /**
        \param textures Textures for lives to display
        */
        LivesDisplay(Textures &textures);
        ///Default destructor for LivesDisplay
        ~LivesDisplay();

        ///How many lives there is?
        unsigned getLives() const { return this->lives; }

        ///Reset display to show 0 lives
        void reset();

        ///Lose one life
        void removeLife();
        ///Add one life
        void addLife();                                 //After getting 2.500 points
        ///Set how many lives there should be
        /**
        \param num Number of lives to set
        */
        void setLives(const unsigned num);              //Used when Invader gets a touch down
        ///Draw LivesDisplay on scene
        /**
        \param window Where it should be displayed
        */
        void draw(sf::RenderWindow &window);
};
