/**
* Name: Textures.h
* Purpose: Declaration of class Textures
*
* @author Fenris
* @version 1.02a 14/05/2017
*/
#pragma once

#include "globals.h"

///Class for Textures
class Textures{
    private:
        sf::Image spritesheet;                              ///<Sheet with ship, explosion and other sprites
        sf::Image monsterssheet;                            ///<Sheet with monsters sprites
        ///Load sprite from file
        /**
        \param img Name of file from which textures will be loaded
        \return Image will be returned
        */
        sf::Image loadSprites(const std::string img);

    public:
        ///Invader 1
        sf::Texture INVADER_11;                              ///<Texture for first frame of Invader1
        sf::Texture INVADER_12;                              ///<Texture for second frame of Invader1
        sf::Texture INVADER_13;                              ///<Texture for third frame of Invader1
        sf::Texture INVADER_14;                              ///<Texture for fourth frame of Invader1
        ///Invader 2
        sf::Texture INVADER_21;                              ///<Texture for first frame of Invader2
        sf::Texture INVADER_22;                              ///<Texture for second frame of Invader2
        sf::Texture INVADER_23;                              ///<Texture for third frame of Invader2
        sf::Texture INVADER_24;                              ///<Texture for fourth frame of Invader2
        ///Invader 3
        sf::Texture INVADER_31;                              ///<Texture for first frame of Invader3
        sf::Texture INVADER_32;                              ///<Texture for second frame of Invader3
        sf::Texture INVADER_33;                              ///<Texture for third frame of Invader3
        sf::Texture INVADER_34;                              ///<Texture for fourth frame of Invader3
        ///Invader 4
        sf::Texture INVADER_41;                              ///<Texture for first frame of Invader4
        sf::Texture INVADER_42;                              ///<Texture for second frame of Invader4
        sf::Texture INVADER_43;                              ///<Texture for third frame of Invader4
        sf::Texture INVADER_44;                              ///<Texture for fourth frame of Invader4
        ///UFO
        sf::Texture UFO_1;                                   ///<Texture for first frame of UFO
        sf::Texture UFO_2;                                   ///<Texture for second frame of UFO
        sf::Texture UFO_3;                                   ///<Texture for third frame of UFO
        sf::Texture UFO_4;                                   ///<Texture for fourth frame of UFO
        ///Creeper
        sf::Texture CREEPER_1;                               ///<Texture for first frame of Creeper
        sf::Texture CREEPER_2;                               ///<Texture for second frame of Creeper
        sf::Texture CREEPER_3;                               ///<Texture for third frame of Creeper
        sf::Texture CREEPER_4;                               ///<Texture for fourth frame of Creeper
        ///Tough
        sf::Texture TOUGH_1;                                 ///<Texture for first frame of Tough
        sf::Texture TOUGH_2;                                 ///<Texture for second frame of Tough
        sf::Texture TOUGH_3;                                 ///<Texture for third frame of Tough
        sf::Texture TOUGH_4;                                 ///<Texture for fourth frame of Tough
        ///Boss
        sf::Texture BOSS_1;                                  ///<Texture for first frame of Boss
        sf::Texture BOSS_2;                                  ///<Texture for second frame of Boss
        sf::Texture BOSS_3;                                  ///<Texture for third frame of Boss
        sf::Texture BOSS_4;                                  ///<Texture for fourth frame of Boss
        ///Ship
        sf::Texture SHIP_1;                                  ///<Texture for first frame of Ship
        sf::Texture SHIP_2;                                  ///<Texture for second frame of Ship
        sf::Texture SHIP_3;                                  ///<Texture for third frame of Ship
        sf::Texture SHIP_4;                                  ///<Texture for fourth frame of Ship
        ///Explosion
        sf::Texture EXPLOSION_1;                             ///<Texture for first frame of Explosion
        sf::Texture EXPLOSION_2;                             ///<Texture for second frame of Explosion
        sf::Texture EXPLOSION_3;                             ///<Texture for third frame of Explosion
        ///Arrow
        sf::Texture ARROW_1;                                 ///<Texture for first frame of Arrow
        sf::Texture ARROW_2;                                 ///<Texture for second frame of Arrow
        sf::Texture ARROW_3;                                 ///<Texture for third frame of Arrow
        sf::Texture ARROW_4;                                 ///<Texture for fourth frame of Arrow
        sf::Texture ARROW_5;                                 ///<Texture for fifth frame of Arrow
        sf::Texture ARROW_6;                                 ///<Texture for sixth frame of Arrow
        sf::Texture ARROW_7;                                 ///<Texture for seventh frame of Arrow
        sf::Texture ARROW_8;                                 ///<Texture for eight frame of Arrow
        sf::Texture ARROW_9;                                 ///<Texture for ninth frame of Arrow
        sf::Texture ARROW_10;                                ///<Texture for tenth frame of Arrow
        sf::Texture ARROW_11;                                ///<Texture for eleventh frame of Arrow
        sf::Texture ARROW_12;                                ///<Texture for twelfth frame of Arrow
        sf::Texture ARROW_13;                                ///<Texture for thirteenth frame of Arrow
        sf::Texture ARROW_14;                                ///<Texture for fourteenth frame of Arrow
        sf::Texture ARROW_15;                                ///<Texture for fifteenth frame of Arrow
        ///Bonuses
        sf::Texture BONUS_1;                                 ///<Texture for Bonus1
        sf::Texture BONUS_2;                                 ///<Texture for Bonus2
        sf::Texture BONUS_3;                                 ///<Texture for Bonus3
        sf::Texture BONUS_4;                                 ///<Texture for Bonus4
        sf::Texture BONUS_5;                                 ///<Texture for Bonus5
        sf::Texture BONUS_6;                                 ///<Texture for Bonus6
        sf::Texture BONUS_7;                                 ///<Texture for Bonus7
        sf::Texture BONUS_8;                                 ///<Texture for Bonus8

        ///Default constructor for Textures
        Textures();
};
