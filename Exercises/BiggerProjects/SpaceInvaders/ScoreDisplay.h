/**
* Name: ScoreDisplay.h
* Purpose: Declaration of class ScoreDisplay
*
* @author Fenris
* @version 0.76 03/05/2017
*/
#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>

///Class for Score Display
class ScoreDisplay{
    private:
        static constexpr unsigned X = 0;                ///<X Position on start
        static constexpr unsigned Y = 0;                ///<Y Position on start

        unsigned &game_score;                           ///<Game score for display

    public:
        ///Default constructor for ScoreDisplay
        /**
        \param score Score which will be displayed
        */
        ScoreDisplay(unsigned &score);

        ///Get text to display on scene
        /**
        \param window Where it should be drawn
        \param score Score to be displayed
        \param x X Position of ScoreDisplay on scene
        \param y Y Position of ScoreDisplay on scene
        */
        void drawScore(sf::RenderWindow &window, const unsigned score, const unsigned x, const unsigned y);
        ///Draw Score(text) on scene
        void draw(sf::RenderWindow &window);
        ///Reset score to display 0
        void reset();
};
