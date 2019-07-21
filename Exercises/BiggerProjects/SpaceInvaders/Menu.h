/**
* Name: Menu.h
* Purpose: Declaration of class Menu
*
* @author Fenris
* @version 1.04 14/05/2017
*/
#pragma once

#include <SFML/Graphics.hpp>
#include "Textures.h"
#include "ScoreDisplay.h"
#include "ClockDisplay.h"

///Class of State MENU
class Menu{
    private:
        static constexpr unsigned PAUSE = 5;                ///<Pause got while drawing lines
        static constexpr unsigned FRAME_TICK_MAX = 6;       ///<Frame tick for animation of arrow

        int select;                                         ///<Selected option

        sf::Sprite arrow;                                   ///<Sprite for arrow

        ScoreDisplay &score_disp;                           ///<Score displayed on scene
        ClockDisplay &clock_disp;                           ///<Clock displayed on scene

        unsigned frame_on;                                  ///<On which frame it is
        unsigned frame_tick;                                ///<Frame tick

        unsigned str_char_on;                               ///<On which character of string is currently on
        unsigned line_on;                                   ///<On which line is currently on
        bool sprite_drawn;                                  ///<Sprite was drawn?
        bool display_scores;                                ///<Score for each Invader was displayed?

        ///Flip frame
        /**
        \param textures Texture of next frame
        */
        void flipFrame(Textures &textures);

    public:
        ///Default constructor for Info
        /**
        \param textures Textures which will be displayed next to score
        \param score_disp Score displayed on scene
        \param clock_disp Clock displayed on scene
        */
        Menu(Textures &textures, ScoreDisplay &score_disp, ClockDisplay &clock_disp);

        ///Set which option is selected
        /**
        \param select Option which will be selected
        */
        void setSelect(int select){ this->select = select;};
        ///Get which option is selected
        int getSelect(){ return this->select;};

        ///Reset Menu to get specific type of drawing
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
        void drawLine(sf::RenderWindow &window, const std::string msg, const unsigned x, const unsigned y, const unsigned wait, const unsigned line_num,
                      sf::Sprite *sprite = nullptr, sf::Color color = sf::Color::White, unsigned size = 24);
        ///Draw Menu
        /**
        \param window Where should it be displayed
        */
        void draw(sf::RenderWindow &window);
        ///Update arrow to get new frame
        /**
        \param textures Textures for animated arrow
        */
        void update(Textures &textures);

};
