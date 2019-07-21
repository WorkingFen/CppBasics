/**
* Name: Invader.cpp
* Purpose: Class Invader
*
* @author Fenris
* @version 0.94a 03/05/2017
*/
#include "Invader.h"

void Invader::reset(const unsigned x, const unsigned y)
{
    this->move_dir = 1;
    this->is_dead = false;
    this->is_exploding = false;
    this->frame_on = 1;
    this->death_tick = 0;
    this->lasers_on_screen = 0;

    this->sprite.setTexture(*(this->frame1_txtr), true);
    if(this->type != Invader::BOSS)
        this->sprite.setPosition(x, y);
}

void Invader::flipFrame()
{
    if(this->frame_on == 1){
        this->sprite.setTexture(*(this->frame1_txtr), true);
        this->frame_on = 2;
    }
    else if(this->frame_on == 2){
        this->sprite.setTexture(*(this->frame2_txtr), true);
        this->frame_on = 3;
    }
    else if(this->frame_on == 3){
        this->sprite.setTexture(*(this->frame3_txtr), true);
        this->frame_on = 4;
    }
    else{
        this->sprite.setTexture(*(this->frame4_txtr), true);
        this->frame_on = 1;
    }
}

Invader::Invader(Textures &textures, const InvaderType type, int isVisible): type(type), move_dir(1), is_dead(false), is_exploding(false), frame_on(1), death_tick(0), lasers_on_screen(0), bonuses_on_screen(0){
    // Load different textures and set different score values based on type of Invader
    if(isVisible == 0)
        this->is_visible = false;
    else if(isVisible == 1)
        this->is_visible = true;

    switch(this->type){
        case Invader::INVADER_1:                            //Invader1
            this->frame1_txtr = &(textures.INVADER_11);
            this->frame2_txtr = &(textures.INVADER_12);
            this->frame3_txtr = &(textures.INVADER_13);
            this->frame4_txtr = &(textures.INVADER_14);
            this->score_value = 40;
            this->lives = 1;
            this->speed = 12;
            break;
        case Invader::INVADER_2:                            //Invader2
            this->frame1_txtr = &(textures.INVADER_21);
            this->frame2_txtr = &(textures.INVADER_22);
            this->frame3_txtr = &(textures.INVADER_23);
            this->frame4_txtr = &(textures.INVADER_24);
            this->score_value = 30;
            this->lives = 1;
            this->speed = 12;
            break;
        case Invader::INVADER_3:                            //Invader3
            this->frame1_txtr = &(textures.INVADER_31);
            this->frame2_txtr = &(textures.INVADER_32);
            this->frame3_txtr = &(textures.INVADER_33);
            this->frame4_txtr = &(textures.INVADER_34);
            this->score_value = 20;
            this->lives = 1;
            this->speed = 12;
            break;
        case Invader::INVADER_4:                            //Invader4
            this->frame1_txtr = &(textures.INVADER_41);
            this->frame2_txtr = &(textures.INVADER_42);
            this->frame3_txtr = &(textures.INVADER_43);
            this->frame4_txtr = &(textures.INVADER_44);
            this->score_value = 10;
            this->lives = 1;
            this->speed = 12;
            break;
        case Invader::UFO:                            //UFO
            this->frame1_txtr = &(textures.UFO_1);
            this->frame2_txtr = &(textures.UFO_2);
            this->frame3_txtr = &(textures.UFO_3);
            this->frame4_txtr = &(textures.UFO_4);
            this->score_value = 60;
            this->lives = 1;
            this->speed = 18;
            this->move_dir = -1;
            this->sprite.setScale(1.6, 1.6);
            break;
        case Invader::CREEPER:                          //Creeper
            this->frame1_txtr = &(textures.CREEPER_1);
            this->frame2_txtr = &(textures.CREEPER_2);
            this->frame3_txtr = &(textures.CREEPER_3);
            this->frame4_txtr = &(textures.CREEPER_4);
            this->score_value = 50;
            this->lives = 1;
            this->speed = 28;
            break;
        case Invader::TOUGH:                            //Tough
            this->frame1_txtr = &(textures.TOUGH_1);
            this->frame2_txtr = &(textures.TOUGH_2);
            this->frame3_txtr = &(textures.TOUGH_3);
            this->frame4_txtr = &(textures.TOUGH_4);
            this->score_value = 80;
            this->lives = 5;
            this->speed = 12;
            this->sprite.setScale(1.2, 1.2);
            break;
        case Invader::BOSS:                            //Boss
            this->frame1_txtr = &(textures.BOSS_1);
            this->frame2_txtr = &(textures.BOSS_2);
            this->frame3_txtr = &(textures.BOSS_3);
            this->frame4_txtr = &(textures.BOSS_4);
            this->score_value = 640;
            this->lives = 54;
            this->speed = 10;
            this->sprite.setScale(4, 4);
            this->sprite.setPosition(600, 620);
            break;
        default:
            break;
    }
    ///All Invaders have the same death
    this->death_txtr = &(textures.EXPLOSION_2);
    this->sprite.setTexture(*(this->frame1_txtr), true);

    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().width / 2);
}

void Invader::die()
{
    this->sprite.setTexture(*(this->death_txtr), true);
    this->is_exploding = true;
    this->is_dead = true;
}

void Invader::move()
{
    if(this->isDead())
        return;

    this->sprite.move(this->speed * this->move_dir, 0);
    this->flipFrame();
}

void Invader::dropDown()
{
    if(this->isDead())
        return;

    this->sprite.move(0, this->HEIGHT);
    this->flipFrame();
}

void Invader::reverseDir()
{
    this->move_dir *= -1;
}

bool Invader::checkHitEdge(const int screenw)
{
    if(this->isDead() || !this->isVisible())
        return false;

    int x = this->sprite.getPosition().x;
    int half_width = (this->sprite.getTexture()->getSize().x) / 2;

    if ((x >= (screenw - half_width - 20) && this->move_dir == 1) || (x <= (half_width + 20) && this->move_dir == -1))
        return true;

    return false;
}

void Invader::incDeathTick()
{
    ++this->death_tick;
    if (this->death_tick >= this->DEATH_TICK_MAX)
        this->is_exploding = false;
}
