/**
* Name: ClockDisplay.h
* Purpose: Declaration of class ClockDisplay
*
* @author Fenris
* @version 1.05 21/05/2017
*/
#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>

///Class for displaying clock
class ClockDisplay{
    private:
        static constexpr unsigned X = 0;                ///<X Position on start
        static constexpr unsigned Y = 0;                ///<Y Position on start

        unsigned &minutes;                              ///<Minutes on clock
        unsigned &seconds;                              ///<Seconds on clock
        unsigned &miliseconds;                          ///<Miliseconds on clock

    public:
        ///Default constructor for ClockDisplay
        /**
        \param minutes Variable for minutes to display on Clock
        \param seconds Variable for seconds to display on Clock
        \param miliseconds Variable for miliseconds to display on Clock
        */
        ClockDisplay(unsigned &minutes, unsigned &seconds, unsigned &miliseconds);

        ///Get text to display on scene
        /**
        \param window Where it should be drawn
        \param minutes Variable for minutes to display on Clock
        \param seconds Variable for seconds to display on Clock
        \param miliseconds Variable for miliseconds to display on Clock
        \param x X Position of ClockDisplay on scene
        \param y Y Position of ClockDisplay on scene
        */
        void drawClock(sf::RenderWindow &window, const unsigned minutes, const unsigned seconds, const unsigned miliseconds, const unsigned x, const unsigned y);
        ///Draw Clock(text) on scene
        void draw(sf::RenderWindow &window);
        ///Reset minutes, seconds and miliseconds to drop them down to 0
        void reset();
};
