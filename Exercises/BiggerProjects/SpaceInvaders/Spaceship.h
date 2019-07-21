/**
* Name: Spaceship.h
* Purpose: Declaration of class Spaceship
*
* @author Fenris
* @version 0.84a 03/05/2017
*/
#pragma once

#include <SFML/Graphics.hpp>
#include "Textures.h"
#include "InvaderFormation.h"
#include "Explosions.h"

///Class for Spaceship
class Spaceship{
    private:
        const unsigned START_X;                                         ///<X Position of the ship at the start of the game
        static constexpr unsigned Y = 623;                              ///<Y Position of the ship at the start of the game

        static constexpr int SPEED = 3;                                 ///<Speed of the ship
        static constexpr unsigned DEATH_TICK_MAX = 50;                  ///<How much time it will be showing death frames
        static constexpr unsigned FRAME_TICK_MAX = 3;                   ///<How much time it will take to change frame

        Textures &textures;                                             ///<Textures for sprite of the ship
        sf::Sprite sprite;                                              ///<Sprite of the ship

        unsigned frame_on;                                              ///<On which frame we are currently on
        bool hit;                                                       ///<Did it get hit?
        unsigned death_tick;                                            ///<Which death tick it is?
        unsigned frame_tick;                                            ///<Which frame tick it is?

        ///Flip frame to the next one while dying
        void flipFrame();
        ///Flip frame to the next one while living
        void flipLiveFrame();

    public:
        ///Default constructor of Spaceship
        /**
        \param textures Textures that will be displayed on scene
        \param startx X Position of the ship while starting the game
        */
        Spaceship(Textures &textures, const int startx);
        ///Check if it was hit
        bool isHit() const { return this->hit; }

        ///Reset the spaceship
        void reset();
        ///Move the ship
        /**
        \param dir Direction which depends on key that we pressed on keyboard
        */
        void move(const int dir);
        ///Get the sprite of the ship
        /**
        \return Sprite of the ship with all parameters
        */
        const sf::Sprite& getSprite() const { return this->sprite; }
        ///Check the X Position of the ship
        unsigned getX() const { return this->sprite.getPosition().x; }
        ///Check the width of the sprite
        unsigned getWidth() const { return this->getSprite().getGlobalBounds().width; }
        ///Die
        /**
        \param invaders For removal of theirs lasers
        \param player_laser To stop all players lasers
        \param explosions To clear all explosions
        */
        void die(InvaderFormation &invaders, PlayerLaser &player_laser, Explosions &explosions);
        ///Handle hit from bonuses and lasers
        /**
        \param invaders For removal of theirs lasers
        \param player_laser To stop all player lasers and to speed up or decelerate them
        \param explosions To remove all explosions
        \param lives To change lives
        \param game_score To change the game score
        */
        void handleHit(InvaderFormation &invaders, PlayerLaser &player_laser, Explosions &explosions, LivesDisplay &lives, unsigned &game_score);
        ///Update ship while playing
        /**
        \param invaders For removal of theirs lasers
        \param player_laser To stop all player lasers and to speed up or decelerate them
        \param explosions To remove all explosions
        \param lives To change lives
        \param game_score To change the game score
        */
        void update(InvaderFormation &invaders, PlayerLaser &player_laser, LivesDisplay &lives_disp, Explosions &explosions, unsigned &game_score);

};
