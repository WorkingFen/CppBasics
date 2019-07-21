/**
* Name: Info.h
* Purpose: Declaration of class Info
*
* @author Fenris
* @version 1.01 14/05/2017
*/
#pragma once

#include "Textures.h"
#include "ScoreDisplay.h"
#include "ClockDisplay.h"

///Class of State INFO
class Info{
    private:
        static constexpr unsigned PAUSE = 6;                ///<Pause got while drawing lines

        sf::Sprite invader1;                                ///<Sprite for first Invader
        sf::Sprite invader2;                                ///<Sprite for second Invader
        sf::Sprite invader3;                                ///<Sprite for third Invader
        sf::Sprite invader4;                                ///<Sprite for fourth Invader

        ScoreDisplay &score_disp;                           ///<Score displayed on scene
        ClockDisplay &clock_disp;                           ///<Clock displayed on scene

        unsigned str_char_on;                               ///<On which character of string is currently on
        unsigned line_on;                                   ///<On which line is currently on
        bool sprite_drawn;                                  ///<Sprite was drawn?
        bool display_scores;                                ///<Score for each Invader was displayed?

    public:
        ///Default constructor for Info
        /**
        \param textures Textures which will be displayed next to score
        \param score_disp Score displayed on scene
        \param clock_disp Clock displayed on scene
        */
        Info(Textures &textures, ScoreDisplay &score_disp, ClockDisplay &clock_disp);

        ///Reset Info to get specific type of drawing
        void reset();

        ///Draws a string with pauses after each character (wait)
        /**
        \param window Where should it be displayed
        \param msg What message should be displayed
        \param x X Position where it should be displayed on scene
        \param y Y Position where it should be displayed on scene
        \param wait How much time pause should take
        \param line_num What line is it on?
        \param sprite What sprite should be displayed next to text
        \param color In which color text should be displayed?
        \param size What size of font should text has?
        */
        void drawLine(sf::RenderWindow &window, const std::string msg, const unsigned x, const unsigned y, const unsigned wait, const unsigned line_num, sf::Sprite *sprite = nullptr, sf::Color color = sf::Color::White, unsigned size = 24);

        ///Draw Info
        /**
        \param window Where should it be displayed
        */
        void draw(sf::RenderWindow &window);

};

