/**
* Name: Spaceship.cpp
* Purpose: Class Spaceship
*
* @author Fenris
* @version 0.92 03/05/2017
*/
#include "globals.h"
#include "game.h"
#include "Spaceship.h"

void Spaceship::flipFrame()
{
    if(this->frame_on == 1){
        this->sprite.setTexture(this->textures.EXPLOSION_1, true);
        this->frame_on = 2;
    }
    else if(this->frame_on == 2){
        this->sprite.setTexture(this->textures.EXPLOSION_2, true);
        this->frame_on = 3;
    }
    else{
        this->sprite.setTexture(this->textures.EXPLOSION_3, true);
        this->frame_on = 1;
    }
}

void Spaceship::flipLiveFrame()
{
    if(this->frame_on == 1){
        this->sprite.setTexture(this->textures.SHIP_1, true);
        this->frame_on = 2;
    }
    else if(this->frame_on == 2){
        this->sprite.setTexture(this->textures.SHIP_2, true);
        this->frame_on = 3;
    }
    else if(this->frame_on == 3){
        this->sprite.setTexture(this->textures.SHIP_3, true);
        this->frame_on = 4;
    }
    else{
        this->sprite.setTexture(this->textures.SHIP_4, true);
        this->frame_on = 1;
    }
}

void Spaceship::reset()
{
    this->death_tick = this->DEATH_TICK_MAX;
    this->frame_tick = this->FRAME_TICK_MAX;
    this->frame_on = 1;
    this->hit = false;

    this->sprite.setTexture(this->textures.SHIP_1, true);
    this->sprite.setPosition(this->START_X, this->Y);

    this->sprite.setOrigin(this->sprite.getTexture()->getSize().x / 2, this->sprite.getTexture()->getSize().y / 2);

    if(Globals::GAME_STATE != Globals::States::WAVE_SETUP && Globals::GAME_STATE != Globals::States::GAME_OVER && Globals::GAME_STATE != Globals::States::MENU)
        Globals::GAME_STATE = Globals::States::PLAY;
}

Spaceship::Spaceship(Textures &textures, const int startx): START_X(startx), textures(textures), frame_on(1), hit(false), death_tick(DEATH_TICK_MAX), frame_tick(FRAME_TICK_MAX)
{
    this->reset();
}

void Spaceship::move(const int dir)
{
    if(!this->hit && ((dir == 1 && (this->getX() < (Globals::SCREEN_WIDTH - (this->getWidth() / 2) - 10))) || (dir == -1 && (this->getX() > (0 + (this->getWidth() / 2) + 10)))))
        this->sprite.move(this->SPEED * dir, 0);
    this->flipLiveFrame();
}

void Spaceship::die(InvaderFormation &invaders, PlayerLaser &player_laser, Explosions &explosions)
{
    this->hit = true;
    this->sprite.setTexture(this->textures.EXPLOSION_1, true);

    Game::handle_player_kill(invaders, player_laser, explosions);
}

void Spaceship::handleHit(InvaderFormation &invaders, PlayerLaser &player_laser, Explosions &explosions, LivesDisplay &lives, unsigned &game_score)
{
    for(auto& laser : invaders.getLasers()){
        if(!this->hit && laser->willHurt() && (laser->checkCollide(this->sprite.getGlobalBounds()))){
            this->die(invaders, player_laser, explosions);
            return;
        }
    }
    for(auto& bonus : invaders.getBonuses()){
        if((bonus->checkCollide(this->sprite.getGlobalBounds()))){
            bonus->setHit();
            bonus->getBonus(bonus->getType(), lives, game_score, player_laser);
            invaders.removeHitBonuses();
            return;
        }
    }
}

void Spaceship::update(InvaderFormation &invaders, PlayerLaser &player_laser, LivesDisplay &lives_disp, Explosions &explosions, unsigned &game_score)
{
    this->handleHit(invaders, player_laser, explosions, lives_disp, game_score);
    if(this->hit){
        --this->death_tick;
        if(this->death_tick <= 0){
            lives_disp.removeLife();
            this->reset();
        }

        --this->frame_tick;
        if(this->frame_tick <= 0){
            this->flipFrame();
            this->frame_tick = this->FRAME_TICK_MAX;
        }
    }
}
