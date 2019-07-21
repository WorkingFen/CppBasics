/**
* Name: PlayerLaser.h
* Purpose: Declaration of class PlayerLaser
*
* @author Fenris
* @version 0.88a 03/05/2017
*/
#pragma once

#include <SFML/Graphics.hpp>
#include "Explosions.h"

///Class for PlayerLaser
class PlayerLaser{
    private:
        static constexpr unsigned WIDTH = 3;                                ///<Width of laser
        static constexpr unsigned HEIGHT = 15;                              ///<Height of laser

        int SPEED = 10;                                                     ///<Speed of laser
        sf::RectangleShape laser;                                           ///<Shape of first laser
        sf::RectangleShape laser2;                                          ///<Shape of second laser
        bool is_shooting;                                                   ///<Is first laser shooting?
        bool is_shooting2;                                                  ///<Is second laser shooting?
        bool is_double;                                                     ///<Is it a bonus with double laser?
        bool firstStop = false;                                             ///<Does first laser stopped?
        bool secondStop = false;                                            ///<Does second laser stopped?

    public:
        ///Default constructor of Player laser
        PlayerLaser();
        ///Get shape of first laser
        /**
        \return The shape of laser
        */
        sf::RectangleShape& getShape(){ return this->laser; }
        ///Get shape of second laser
        /**
        \return The shape of laser
        */
        sf::RectangleShape& getShape2(){ return this->laser2; }
        ///Check the first laser (Is it shooting?)
        bool isShooting() const { return this->is_shooting; }
        ///Check the second laser (Is it shooting?)
        bool isShooting2() const { return this->is_shooting2; }
        ///Check if there is a bonus
        bool isDouble() const { return this->is_double; }

        ///Get the bonus
        void nowDouble(){ this->is_double = true; }

        ///Check the speed of the laser
        int getSpeed(){ return this->SPEED; }
        ///Set the speed of the laser
        /**
        \param speed Value of speed that will be set
        */
        void setSpeed(int speed){ this->SPEED = speed; }

        ///Check if the first laser stopped shooting
        bool getStop1(){ return this->firstStop; }
        ///Check if the second laser stopped shooting
        bool getStop2(){ return this->secondStop; }

        ///Shoot the laser
        /**
        \param startx X Position of the laser that will be displayed
        \param starty Y Position of the laser that will be displayed
        */
        void shoot(const unsigned startx, const unsigned starty);
        ///Move the laser
        /**
        \param explosions Explosions after collision with something
        */
        void move(Explosions &explosions);

        ///Stop the first laser
        void stop1();
        ///Stop the second laser
        void stop2();
        ///Reset player laser (Laser won't be double and speed will has the starting value)
        void reset();
};
