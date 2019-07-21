/**
* Name: InvaderFormation.h
* Purpose: Declaration of class InvaderFormation
*
* @author Fenris
* @version 0.91 03/05/2017
*/
#pragma once

#include <SFML/Graphics.hpp>
#include "Invader.h"
#include "InvaderLaser.h"
#include "PlayerLaser.h"
#include "LivesDisplay.h"
#include "Explosions.h"
#include "Bonus.h"
#include <fstream>
#include "json.hpp"

class Spaceship;

///Vector which has Invaders in it
typedef std::vector<Invader*> InvaderRow;
///Vector which has InvadersRows in it
typedef std::vector<InvaderRow> InvaderVector2D;
///Vector which has InvadersLasers in it
typedef std::vector<InvaderLaser*> Lasers;
///Vector which has Bonuses in it
typedef std::vector<Bonus*> Bonuses;

///Class of InvaderFormation
class InvaderFormation{
    private:
        unsigned total;                                                         ///<How many invaders there is to kill

        static constexpr unsigned STARTX = 120;                                 ///<X Position where formation starts
        const unsigned STARTY = 150;                                            ///<Y Position where formation starts

        static constexpr unsigned WAVE_SHIFT_Y = 50;                            ///<How low should formation drop down

        static constexpr unsigned INVADE_LINE = Globals::SCREEN_HEIGHT - 110;   ///<Line which has to be protected from invaders

        static constexpr int MOVE_TICK_MAX_START = 45;                          ///<How much tick formation wait to move
        static constexpr int MOVE_TICK_CHANGE_START = 1;                        ///<The amount of change made to move tick

        /*///Chance of UFO appearing: 1/CHANCE
        static constexpr int APPEAR_CHANCE = 100;*/

        static constexpr int SHOT_CHANCE_START = 1500;                          ///<Chance of each Invader shooting: 1/SHOT_CHANCE

        static constexpr int BONUS_CHANCE_START = 400;                          ///<Chance of each Invader shooting bonuses: 1/SHOT_CHANCE

        sf::RenderWindow &window;                                               ///<Where the formation should be displayed
        InvaderVector2D invaders;                                               ///<The name for formation (vector)

        int move_tick;                                                          ///<Actual move tick
        int move_tick_max;                                                      ///<Actual max that can be for move tick
        int move_tick_change;                                                   ///<Actual move tick change

        unsigned num_killed;                                                    ///<Number of killed invaders

        bool has_hit_edge;                                                      ///<Does invader got across the line that player's ship was protecting?

        int shot_chance;                                                        ///<Actual chance of invaders shooting
        int bonus_chance;                                                       ///<Actual chance of bonuses shooting

        int xgap;                                                               ///<X Position gap between each invader
        int ygap;                                                               ///<Y Position gap between each invader

        ///Incrementing death tick
        void incDeathTick();

        ///Increase fire
        /**
        \param amount How much it should be increased
        */
        void increaseFire(const int amount);

        ///To shoot or not to shoot?
        bool toShootOrNah() const;
        ///Shoot laser
        /**
        \param x X Position of the laser
        \param y Y Position of the laser
        \param will_hurt It will hurt?
        \param owner Invader whose laser it is
        */
        void shootLaser(const unsigned x, const unsigned y, const bool will_hurt, Invader &owner);
        ///Shoot bonus
        /**
        \param x X Position of the laser
        \param y Y Position of the laser
        \param owner Invader whose bonus it is
        \param textures Textures of bonuses
        \param type Type of the bonus
        */
        void shootBonus(const unsigned x, const unsigned y, Invader &owner, Textures &textures, const Bonus::BonusType type);
        ///Handle collision with players laser
        /**
        \param explosions Explosion while there is hit
        \param player_laser Player laser was hit so it should be removed
        */
        void handleCollisions(Explosions &explosions, PlayerLaser &player_laser);
        ///Get lasers to vector
        void shootLasers();
        ///Get bonuses to vector
        /**
        \param invader From which invader it was dropped
        */
        void shootBonuses(Invader *invader);
        ///Move all the lasers in vector
        /**
        \param explosions Just to check if there was hit
        \param player_laser Just to check if there was hit
        */
        void moveLasers(Explosions &explosions, PlayerLaser &player_laser);
        ///Move all the bonuses in vector
        void moveBonuses();
        ///Remove lasers that were hit
        void removeHitLasers();
        ///Update lasers, movements and their frames
        /**
        \param explosions Just to check if there was hit
        \param player_laser Just to check if there was hit
        */
        void updateLasers(Explosions &explosions, PlayerLaser &player_laser);
        ///Update bonuses and their movements
        void updateBonuses();

        Textures textures;                                                      ///<Variable with textures for Invaders
        Lasers lasers;                                                          ///<Vector with lasers
        Bonuses bonuses;                                                        ///<Vector with bonuses

        ///Move formation
        /**
        \param ship
        \param player_laser
        \param lives_disp
        \param explosions
        \param minutes
        \param seconds
        \param miliseconds
        */
        bool move(Spaceship &ship, PlayerLaser &player_laser, LivesDisplay &lives_disp, Explosions &explosions, unsigned &minutes, unsigned &seconds, unsigned &miliseconds);

        ///Drop down the formation
        void shift();               //Increase speed, drop down, and reverse direction

        ///Check if Invader was hit
        /**
        \param laser Check collision with player laser
        \param game_score Add points for Invader
        */
        void checkHit(PlayerLaser &laser, unsigned &game_score);

    public:
        ///Default constructor for InvaderFormation
        /**
        \param window Where it should be displayed
        */
        InvaderFormation(sf::RenderWindow &window);
        ///Default destructor for InvaderFormation
        ~InvaderFormation();
        ///Get vector with lasers
        /**
        \return Vector with lasers
        */
        Lasers& getLasers(){ return this->lasers; }
        ///Get vector with bonuses
        /**
        \return Vector with bonuses
        */
        Bonuses& getBonuses(){ return this->bonuses; };
        ///Get vector with formation
        /**
        \return Vector with InvaderRows
        */
        InvaderVector2D& getInvaders(){ return this->invaders; }
        ///Get how many invaders there are to kill
        unsigned getTotal() const { return this->total; }
        ///Get how many invaders there are already killed
        unsigned getNumKilled() const { return this->num_killed; }

        ///Reset the formation
        void reset();

        ///Update the formation and it's movement
        /**
        \param laser For updating movement
        \param ship For updating movement
        \param player_laser For updating lasers
        \param lives_disp For checking if there was a hit
        \param explosions For updating lasers
        \param game_score For updating score
        \param minutes For updating clock
        \param seconds For updating clock
        \param miliseconds For updating clock
        */
        void update(PlayerLaser &laser, Spaceship &ship, PlayerLaser &player_laser, LivesDisplay &lives_disp, Explosions &explosions, unsigned &game_score, unsigned &minutes, unsigned &seconds, unsigned &miliseconds);

        ///Draw formation
        /**
        \param amount
        */
        void draw(int amount = -1);
        ///Draw lasers
        void drawLasers();
        ///Draw bonuses
        void drawBonuses();

        ///Clear level from invisible invaders
        void clearLevel();

        ///Load level from files
        void loadLevel(sf::RenderWindow &window, Textures &textures, std::string fileName);

        ///Remove bonuses that got hit
        void removeHitBonuses();

        ///Remove all lasers
        void removeLasers();
        ///Remove all bonuses
        void removeBonuses();
};

