/**
* Name: Bonus.h
* Purpose: Declaration of class Bonus
*
* @author Fenris
* @version 0.81b 03/05/2017
*/
#pragma once

#include "Invader.h"
#include "LivesDisplay.h"
#include "PlayerLaser.h"

///Class which consists of functions for displaying bonuses
class Bonus{
    public:
        ///Container for types of bonuses
        enum BonusType { BONUS_1, BONUS_2, BONUS_3, BONUS_4, BONUS_5, BONUS_6, BONUS_7, BONUS_8 };

    private:

        static constexpr unsigned WIDTH = 28;               ///<Static WIDTH of Bonus
        static constexpr unsigned HEIGHT = 16;              ///<Static HEIGHT of Bonus
        unsigned SPEED;                                     ///<How fast the Bonus moves.
        bool hit;                                           ///<Whether or not hit something and about to be removed.

        Invader &owner;                                     ///<From which Invader it was dropped out

        BonusType type;                                     ///<Variable for caring about type of Bonus
        sf::Texture *bonus_txtr;                            ///<Texture to show in sprite for each type of Bonus
        sf::Sprite sprite;                                  ///<Sprite of Bonus

    public:
        ///Default constructor for Bonus
        /**
        \param x X Position of Bonus on scene
        \param y Y Position of Bonus on scene
        \param owner Invader from which Bonus was dropped out
        \param textures Textures of Bonuses
        \param type Type of Bonus
        */
        Bonus(const unsigned x, const unsigned y, Invader &owner, Textures &textures, const BonusType type);
        ///Default destructor for Bonus
        ~Bonus(){ this->owner.decBonusesOnScreen(); }

        ///Check if Bonus get status: hit
        /**
        \return Bool for status (is hit?)
        */
        bool isHit() const { return this->hit; }
        ///Set that Bonus got status: hit
        void setHit() { this->hit = true; }

        ///Get bonus from Bonus you caught
        /**
        \param type Type of Bonus
        \param lives For operations on lives
        \param game_score For operations on game score
        \param laser For operations on players laser
        */
        void getBonus(const BonusType type, LivesDisplay &lives, unsigned &game_score, PlayerLaser &laser);

        ///Check what type of Bonus is this
        /**
        \return Type of bonus
        */
        BonusType getType(){ return this->type; }

        ///Get X Position of Bonus on scene
        unsigned getX() const { return this->sprite.getPosition().x; }
        ///Get Y Position of Bonus on scene
        unsigned getY() const { return this->sprite.getPosition().y; }

        ///Move Bonus
        void move();

        ///Draw sprite of Bonus
        /**
        \param window Where it should be drawn
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
