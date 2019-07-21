/**
* Name: globals.h
* Purpose: Declaration of namespace Globals
*
* @author Fenris
* @version 1.03a 14/05/2017
*/
#pragma once

#include <string>
#include <SFML/Graphics.hpp>

namespace Globals
{
    ///States the game can be in.
    enum States{
        MENU,               //Menu of the game
        MENUIG,             //Menu in game
        PLAY,               //The actual gameplay
        WAVE_SETUP,         //When new game begins and Invaders have been drawn
        PLAYER_KILLED,      //Player got shot
        SAVE,               //Save the game
        LOAD,               //Load the game
        INFO,               //Show points
        GAME_OVER           //All lives are gone, or Invaders have fled (GAME OVER)
    };

    const std::string SCREEN_TITLE = "Space Invaders";              ///<Title of Window
    constexpr unsigned SCREEN_WIDTH = 1366;                         ///<Width of Window
    constexpr unsigned SCREEN_HEIGHT = 768;                         ///<Height of Window
    constexpr unsigned FRAME_RATE = 60;                             ///<Frame rate
    const sf::Color BG_COLOR = sf::Color(8,8,16);                   ///<Color of the background

    const std::string SPRITES_PATH = "sprites/";                    ///<Path to get sprites for Textures
    const std::string FONTS_PATH = "fonts/";                        ///<Path to get font
    const std::string SAVES_PATH = "saves/";                        ///<Path to get files for load and where will be saved new files
    const std::string LEVELS_PATH = "levels/";                      ///<Path to get files for loading levels

    extern States GAME_STATE;                                       ///<Variable to know in which state we are now
    extern States PREVIOUS_STATE;                                   ///<Variable to know in which state we were before
}
