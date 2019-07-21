/**
* Name: main.cpp
* Purpose: Main file
*
* @author Fenris
* @version 0.94a 03/05/2017
*/
#include <ctime>
#include <SFML/Graphics.hpp>
#include "globals.h"
#include "rand.h"
#include "game.h"
#include "Textures.h"
#include "Stars.h"

int main(){
    unsigned minutes = 0;
    unsigned seconds = 0;
    unsigned miliseconds = 0;
    unsigned game_score = 0;
    unsigned wave_on = 0;

    srand(time(0));

    sf::RenderWindow window(sf::VideoMode(Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT), Globals::SCREEN_TITLE);//, sf::Style::Fullscreen);
    window.setFramerateLimit(Globals::FRAME_RATE);

    window.sf::Window::setMouseCursorVisible(false);

    Textures textures;

    InvaderFormation invaders(window);

    Spaceship ship(textures, 100);

    PlayerLaser player_laser;

    Stars stars(window, 0, 1);

    ClockDisplay clock_disp(minutes, seconds, miliseconds);

    ScoreDisplay score_disp(game_score);

    LivesDisplay lives_disp(textures);

    Menu menu(textures, score_disp, clock_disp);

    MenuIG menuig(textures, score_disp, clock_disp);

    Info info(textures, score_disp, clock_disp);

    Load load(textures, score_disp, clock_disp, lives_disp, wave_on, game_score, minutes, seconds, miliseconds);

    Save save(textures, score_disp, clock_disp, lives_disp, wave_on, game_score, minutes, seconds, miliseconds);

    Explosions explosions(textures);

    while (window.isOpen())
    {
        Game::handle_events(window, window, textures, clock_disp, info, save, menuig, load, menu, score_disp, lives_disp, invaders, player_laser, ship, explosions, wave_on);
        Game::update_objects(window, stars, menuig, load, save, menu, textures, ship, player_laser, invaders, lives_disp, explosions, game_score, wave_on, minutes, seconds, miliseconds);
        Game::draw_objects(window, stars, clock_disp, menuig, load, save, info, menu, score_disp, lives_disp, invaders, ship, player_laser, explosions, wave_on);
    }
}
