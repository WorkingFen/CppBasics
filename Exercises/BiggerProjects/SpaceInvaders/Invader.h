/**
* Name: Invader.h
* Purpose: Declaration of class Invader
*
* @author Fenris
* @version 0.94b 03/05/2017
*/
#pragma once

#include "Textures.h"

///Class for Invader
class Invader{
    public:
        ///Container for types of Invaders
        enum InvaderType { INVADER_1, INVADER_2, INVADER_3, INVADER_4, UFO, CREEPER, TOUGH, BOSS };

    private:
        static constexpr unsigned HEIGHT = 35;                                          ///<How much invader should drop down
        static constexpr unsigned DEATH_TICK_MAX = 10;                                  ///<How long death sprite should show

        sf::Texture *frame1_txtr;                                                       ///<First frame
        sf::Texture *frame2_txtr;                                                       ///<Second frame
        sf::Texture *frame3_txtr;                                                       ///<Third frame
        sf::Texture *frame4_txtr;                                                       ///<Fourth frame
        sf::Texture *death_txtr;                                                        ///<Fifth frame
        sf::Sprite sprite;                                                              ///<Sprite for Invader

        InvaderType type;                                                               ///<Type of Invader
        unsigned score_value;                                                           ///<How many points the invader is worth when killed
        int move_dir;                                                                   ///<Direction: 1 is right, -1 is left
        bool is_dead;                                                                   ///<Is Invader dead?
        bool is_exploding;                                                              ///<Is Invader exploding?
        bool is_visible;                                                                ///<Is Invader visible?
        int frame_on;                                                                   ///<On which frame it is?
        int lives;                                                                      ///<How many lives Invader has?
        int speed;                                                                      ///<Speed of Invader

        unsigned death_tick;                                                            ///<How long death sprite has shown
        unsigned lasers_on_screen;                                                      ///<How many lasers are there on screen
        unsigned bonuses_on_screen;                                                     ///<How many bonuses are there on screen

        ///Flip Invaders frame
        void flipFrame();

    public:
        ///Default constructor for Invader
        /**
        \param textures Texture for Invader's sprite
        \param type Type of Invader
        \param isVisible Is Invader visible?
        */
        Invader(Textures &textures, const InvaderType type, int isVisible);
        ///Get Invader's sprite
        sf::Sprite& getSprite() { return this->sprite; }
        ///Get how much invader should drop down
        static unsigned getHeight() { return Invader::HEIGHT; }
        ///Get how mush score user will get
        unsigned getScoreValue() const { return this->score_value; }
        ///Check if Invader is dead
        bool isDead() const { return this->is_dead; }
        ///Check if Invader is exploding
        bool isExploding() const { return this->is_exploding; }
        ///Check if Invader is visible
        bool isVisible() const { return this->is_visible; }
        ///Check movement direction
        int getMoveDir() const { return this->move_dir; }
        ///Check how many lives Invader has
        int getLives() const { return this->lives; }
        ///Set how many lives should Invader has
        void setLives(int life) { this->lives = life; }
        ///Check how many lasers there are on screen
        unsigned getLasersOnScreen() const { return this->lasers_on_screen; }
        ///Check how many bonuses there are on screen
        unsigned getBonusesOnScreen() const { return this->bonuses_on_screen; }

        ///Reset Invader
        /**
        \param x X Position for Invader
        \param y Y Position for Invader
        */
        void reset(const unsigned x, const unsigned y);

        ///Kill Invader
        void die();
        ///Move Invader
        void move();

        ///The invader lowers by one row
        void dropDown();
        ///The invader reverses its direction of movement
        void reverseDir();
        ///Did Invader hit edge of screen?
        /**
        \param screenw Width of screen
        */
        bool checkHitEdge(const int screenw);
        ///Increment death tick and hide once hit max
        void incDeathTick();

        ///Set one more laser on screen
        void incLasersOnScreen() { ++this->lasers_on_screen; }
        ///Erase one laser from screen
        void decLasersOnScreen() { --this->lasers_on_screen; }

        ///Set one more bonus on screen
        void incBonusesOnScreen() { ++this->bonuses_on_screen; }
        ///Erase one bonus from screen
        void decBonusesOnScreen() { --this->bonuses_on_screen; }
};

