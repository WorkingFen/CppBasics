/**
* Name: Explosions.h
* Purpose: Declaration of classes Explosion and Explosions
*
* @author Fenris
* @version 0.98 03/05/2017
*/
#pragma once

#include <vector>
#include "Textures.h"

///Class for one explosion
class Explosion{
    private:
        static constexpr unsigned SHOW_TICK_START = 20;                         ///<How much time it will take to remove explosion

        sf::Sprite sprite;                                                      ///<Sprite for explosion
        unsigned show_tick;                                                     ///<Variable to update \param showing
        bool showing;                                                           ///Is explosion showing?

    public:
        ///Default constructor for Explosion
        /**
        \param textures Texture of Explosion
        \param color Color of Explosion
        \param x X Position of Explosion on scene
        \param y Y Position of Explosion on scene
        */
        Explosion(Textures &textures, sf::Color color, const unsigned x, const unsigned y);
        ///Get bool of showing (is Explosion showing?)
        /**
        \return Bool if Explosion is showing or no?
        */
        bool isShowing() const { return this->showing; }
        ///Update explosion till it's showing
        void update();
        ///Draw Explosion on scene
        /**
        \param window Where it should be drawn
        */
        void draw(sf::RenderWindow &window);
};

///Class for all explosions
class Explosions{
    private:
        std::vector<Explosion*> explosions;                                     ///<Vector which keeps explosions
        Textures &textures;                                                     ///<Texture to show in sprite for explosions

    public:
        ///Default constructor for Explosions
        /**
        \param textures Texture of Explosions
        */
        Explosions(Textures &textures);
        ///Default destructor for Explosions
        ~Explosions();

        ///Clear vector to get it clean
        void reset();
        ///If Explosion is not showing -> Delete it
        void update();
        ///Draw explosions on scene
        /**
        \param window Where they should be drawn
        */
        void draw(sf::RenderWindow &window);
        ///Push new explosion to vector
        /**
        \param color Color of new Explosion
        \param x X Position for new Explosion
        \param y Y Position for new Explosion
        */
        void newExplosion(sf::Color color, const unsigned x, const unsigned y);
};
