/**
* Name: game.h
* Purpose: Declaration of namespace Game
*
* @author Fenris
* @version 1.03 14/05/2017
*/
#pragma once

#include <SFML/Graphics.hpp>
#include "ScoreDisplay.h"
#include "LivesDisplay.h"
#include "PlayerLaser.h"
#include "InvaderFormation.h"
#include "Spaceship.h"
#include "Menu.h"
#include "Explosions.h"
#include "Info.h"
#include "Load.h"
#include "Save.h"
#include "Menu_in_game.h"
#include "ClockDisplay.h"
#include "Stars.h"

///Namespace with logistic of the game
namespace Game
{
    extern bool life_awarded;                               ///<Variable to see if life was awarded

    ///Events(mainly window close)
    void handle_events(sf::Window &window, sf::RenderWindow &windows, Textures &textures, ClockDisplay &clock_disp,
                       Info &info, Save &save, MenuIG &menuig, Load &load, Menu &menu, ScoreDisplay &score_disp, LivesDisplay &lives_disp,
                       InvaderFormation &invaders, PlayerLaser &player_laser, Spaceship &ship, Explosions &explosions, unsigned &wave_on);

    ///Real-time keyboard input
    void real_time_key(PlayerLaser &player_laser, Spaceship &ship);

    ///Update all game objects
    void update_objects(sf::RenderWindow &window, Stars &stars, MenuIG &menuig, Load &load, Save &save, Menu &menu,
                        Textures &textures, Spaceship &ship, PlayerLaser &player_laser, InvaderFormation &invaders, LivesDisplay &lives_disp,
                        Explosions &explosions, unsigned &game_score, unsigned &wave_on, unsigned &minutes, unsigned &seconds, unsigned &miliseconds);

    ///Draw player lasers
    void draw_player_laser(sf::RenderWindow &window, PlayerLaser &laser);

    ///Draw text on screen
    void draw_text(sf::RenderWindow &window, const std::string msg, const unsigned x, const unsigned y,
                   sf::Color color = sf::Color::White, unsigned size = 24);

    ///Draw objects on screen
    void draw_objects(sf::RenderWindow &window, Stars &stars, ClockDisplay &clock_disp, MenuIG &menuig, Load &load,
                      Save &save, Info &info, Menu &menu, ScoreDisplay &score_disp, LivesDisplay &lives_disp, InvaderFormation &invaders,
                      Spaceship &ship, PlayerLaser &playerlaser, Explosions &explosions, unsigned &wave_on);

    ///An event after player was killed (mainly pause)
    void handle_player_kill(InvaderFormation &invaders, PlayerLaser &player_laser, Explosions &explosions);

    ///Setup new wave
    void setup_wave(sf::RenderWindow &window, Textures &textures, InvaderFormation &invaders, PlayerLaser &player_laser,
                    Spaceship &ship, Explosions &explosions, unsigned &wave_on, bool start_game = false);

    ///Draw wave on screen
    void draw_wave(InvaderFormation &invaders);

    ///An event after Game Over
    void handle_game_over(sf::RenderWindow &window, ClockDisplay &clock_disp, Menu &menu, ScoreDisplay &score_disp,
                          LivesDisplay &lives_disp, InvaderFormation &invaders, Spaceship &ship, PlayerLaser &playerlaser,
                          Explosions &explosions, unsigned &wave_on);

    ///Reset all objects
    void reset_game(Menu &menu, ClockDisplay &clock_disp, ScoreDisplay &score_disp, LivesDisplay &lives_disp, InvaderFormation &invaders,
                    Spaceship &ship, PlayerLaser &playerlaser, Explosions &explosions, unsigned &wave_on);

    ///Go to main menu
    void goto_menu(Menu &menu, ClockDisplay &clock_disp, ScoreDisplay &score_disp, LivesDisplay &lives_disp, InvaderFormation &invaders,
                   Spaceship &ship, PlayerLaser &playerlaser, Explosions &explosions, unsigned &wave_on);

    ///Go to menu in game
    void goto_menuig(MenuIG &menuig);

    ///See info about Invaders
    void goto_info(Info &info);

    ///Go to State for Loading game
    void goto_loading(Load &load);

    ///Go to State for Saving game
    void goto_saving(Save &save);

    ///Play New Game
    void play_game(sf::RenderWindow &window, Textures &textures, InvaderFormation &invaders, PlayerLaser &player_laser, Spaceship &ship,
                   Explosions &explosions, unsigned &wave_on);
}
