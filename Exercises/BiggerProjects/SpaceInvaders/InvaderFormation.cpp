/**
* Name: InvaderFormation.cpp
* Purpose: Class InvaderFormation
*
* @author Fenris
* @version 0.98a 03/05/2017
*/
#include "globals.h"
#include "rand.h"
#include "InvaderFormation.h"
#include "Spaceship.h"

using Json = nlohmann::json;

void InvaderFormation::reset()
{
    this->move_tick = 0;
    this->move_tick_max = MOVE_TICK_MAX_START;
    this->move_tick_change = MOVE_TICK_CHANGE_START;
    this->num_killed = 0;
    this->has_hit_edge = false;
    this->shot_chance = this->SHOT_CHANCE_START;
    this->bonus_chance = this->BONUS_CHANCE_START;

    this->removeLasers();
    this->removeBonuses();

    for (unsigned i = 0; i < this->invaders.size(); ++i)
    {
        for (unsigned j = 0; j < this->invaders[i].size(); ++j)
            this->invaders[i][j]->reset(this->STARTX + (j * this->xgap), this->STARTY+ (i * this->ygap));
    }

    this->xgap = 55;
    this->ygap = 50;
}

void InvaderFormation::incDeathTick()
{
    for (auto& invader_row : this->invaders)
    {
        for (auto& invader : invader_row)
        {
            if (invader->isExploding())
                invader->incDeathTick();
        }
    }
}

void InvaderFormation::increaseFire(int amount)
{
   this->shot_chance -= amount;
   if (this->shot_chance < 10)
       shot_chance = 10;
}

bool InvaderFormation::toShootOrNah() const
{
    //There is 1/shot_chance of returning true.
    return Rand::random(1, this->shot_chance) == 1;
}

void InvaderFormation::shootLaser(unsigned x, unsigned y, const bool will_hurt, Invader &owner)
{
    this->lasers.push_back(new InvaderLaser(x, y, will_hurt, owner));
}

void InvaderFormation::shootBonus(unsigned x, unsigned y, Invader &owner, Textures &textures, const Bonus::BonusType type)
{
    this->bonuses.push_back(new Bonus(x, y, owner, textures, type));
}

void InvaderFormation::handleCollisions(Explosions &explosions, PlayerLaser &player_laser)
{
    for (unsigned i = 0; i < this->lasers.size(); ++i){
        InvaderLaser *laser = this->lasers[i];

        if (laser->checkCollide(player_laser.getShape().getGlobalBounds())){
            // Player laser always gets destroyed.
            explosions.newExplosion(sf::Color::White, laser->getX(), laser->getY());
            player_laser.stop1();

            // Lasers have a 1 in 3 chance of being destroyed if hit by player laser.
            if ((Rand::random(1, 3) == 2))
                laser->setHit();
        }

        if (laser->checkCollide(player_laser.getShape2().getGlobalBounds())){
            // Player laser always gets destroyed.
            explosions.newExplosion(sf::Color::White, laser->getX(), laser->getY());
            player_laser.stop2();

            // Lasers have a 1 in 3 chance of being destroyed if hit by player laser.
            if ((Rand::random(1, 3) == 2))
                laser->setHit();
        }
    }
}

void InvaderFormation::shootLasers()
{
    for(unsigned i = 0; i < this->invaders.size(); ++i){
        for(unsigned j = 0; j < this->invaders[i].size(); ++j){
            Invader *invader = this->invaders[i][j];


            if(!invader->isDead() && invader->isVisible() && invader->getLasersOnScreen() < 3 && this->toShootOrNah()){        //Will shoot if Invader is alive and has less than 3 lasers on screen already
                bool shoot = true;
                for (unsigned k = i + 1; k <= this->invaders.size(); ++k){                              //Will shoot the laser if there is no Invader below
                    if (k != this->invaders.size() && !this->invaders[k][j]->isDead()){
                        shoot = false;
                        break;
                    }
                }

                if (shoot){
                    sf::Vector2f invader_pos = invader->getSprite().getPosition();
                    this->shootLaser(invader_pos.x, invader_pos.y, invader->getSprite().getPosition().y < (this->INVADE_LINE - 40), *invader);
                }
            }//if[invader alive and less than 3 lasers]
        }
    }//for[main]
}

void InvaderFormation::shootBonuses(Invader *invader)
{
    bool bonus = true;

    if (bonus){
        sf::Vector2f invader_pos = invader->getSprite().getPosition();

        int i = Rand::random(1, this->bonus_chance);
        switch(i){
            case 1:
                this->shootBonus(invader_pos.x, invader_pos.y, *invader, textures, Bonus::BONUS_1);
                break;
            case 102:
                this->shootBonus(invader_pos.x, invader_pos.y, *invader, textures, Bonus::BONUS_1);
                break;
            case 11:
                this->shootBonus(invader_pos.x, invader_pos.y, *invader, textures, Bonus::BONUS_2);
                break;
            case 112:
                this->shootBonus(invader_pos.x, invader_pos.y, *invader, textures, Bonus::BONUS_2);
                break;
            case 213:
                this->shootBonus(invader_pos.x, invader_pos.y, *invader, textures, Bonus::BONUS_2);
                break;
            case 314:
                this->shootBonus(invader_pos.x, invader_pos.y, *invader, textures, Bonus::BONUS_2);
                break;
            case 21:
                if(i%5 == 0)
                    this->shootBonus(invader_pos.x, invader_pos.y, *invader, textures, Bonus::BONUS_3);
                break;
            case 31:
                this->shootBonus(invader_pos.x, invader_pos.y, *invader, textures, Bonus::BONUS_4);
                break;
            case 132:
                this->shootBonus(invader_pos.x, invader_pos.y, *invader, textures, Bonus::BONUS_4);
                break;
            case 233:
                this->shootBonus(invader_pos.x, invader_pos.y, *invader, textures, Bonus::BONUS_4);
                break;
            case 334:
                this->shootBonus(invader_pos.x, invader_pos.y, *invader, textures, Bonus::BONUS_4);
                break;
            case 375:
                this->shootBonus(invader_pos.x, invader_pos.y, *invader, textures, Bonus::BONUS_4);
                break;
            case 41:
                this->shootBonus(invader_pos.x, invader_pos.y, *invader, textures, Bonus::BONUS_5);
                break;
            case 142:
                this->shootBonus(invader_pos.x, invader_pos.y, *invader, textures, Bonus::BONUS_5);
                break;
            case 243:
                this->shootBonus(invader_pos.x, invader_pos.y, *invader, textures, Bonus::BONUS_5);
                break;
            case 344:
                this->shootBonus(invader_pos.x, invader_pos.y, *invader, textures, Bonus::BONUS_5);
                break;
            case 285:
                this->shootBonus(invader_pos.x, invader_pos.y, *invader, textures, Bonus::BONUS_5);
                break;
            case 156:
                this->shootBonus(invader_pos.x, invader_pos.y, *invader, textures, Bonus::BONUS_5);
                break;
            case 267:
                this->shootBonus(invader_pos.x, invader_pos.y, *invader, textures, Bonus::BONUS_5);
                break;
            case 378:
                this->shootBonus(invader_pos.x, invader_pos.y, *invader, textures, Bonus::BONUS_5);
                break;
            case 51:
                this->shootBonus(invader_pos.x, invader_pos.y, *invader, textures, Bonus::BONUS_6);
                break;
            case 152:
                this->shootBonus(invader_pos.x, invader_pos.y, *invader, textures, Bonus::BONUS_6);
                break;
            case 253:
                this->shootBonus(invader_pos.x, invader_pos.y, *invader, textures, Bonus::BONUS_6);
                break;
            case 61:
                this->shootBonus(invader_pos.x, invader_pos.y, *invader, textures, Bonus::BONUS_7);
                break;
            case 71:
                this->shootBonus(invader_pos.x, invader_pos.y, *invader, textures, Bonus::BONUS_8);
                break;
            case 172:
                this->shootBonus(invader_pos.x, invader_pos.y, *invader, textures, Bonus::BONUS_8);
                break;
            case 273:
                this->shootBonus(invader_pos.x, invader_pos.y, *invader, textures, Bonus::BONUS_8);
                break;
            case 374:
                this->shootBonus(invader_pos.x, invader_pos.y, *invader, textures, Bonus::BONUS_8);
                break;
            case 295:
                this->shootBonus(invader_pos.x, invader_pos.y, *invader, textures, Bonus::BONUS_8);
                break;
            default:
                break;
        }
    }
}

void InvaderFormation::moveLasers(Explosions &explosions, PlayerLaser &player_laser)
{
    this->handleCollisions(explosions, player_laser);
    for(auto& laser : this->lasers)
        laser->move();
}

void InvaderFormation::moveBonuses()
{
    for(auto& bonus : this->bonuses)
        bonus->move();
}

void InvaderFormation::removeHitLasers()
{
    for(unsigned i = 0; i < this->lasers.size(); ++i){
        InvaderLaser *laser = lasers[i];
        if(laser->isHit()){
            delete laser;
            this->lasers.erase(lasers.begin() + i);
        }
    }
}

void InvaderFormation::removeHitBonuses()
{
    for(unsigned i = 0; i < this->bonuses.size(); ++i){
        Bonus *bonus = bonuses[i];
        if(bonus->isHit()){
            delete bonus;
            this->bonuses.erase(bonuses.begin() + i);
        }
    }
}

bool InvaderFormation::move(Spaceship &ship, PlayerLaser &player_laser, LivesDisplay &lives_disp, Explosions &explosions, unsigned &minutes, unsigned &seconds, unsigned &miliseconds)
{
    if (this->getNumKilled() == (this->getTotal() - 1)){
        if (this->invaders[0][0]->getMoveDir() == 1)
            this->move_tick_max = 2;
        else
            this->move_tick_max = 1;
    }

    if(minutes<99){
        if(miliseconds<100)
            miliseconds++;
        else if(seconds<59){
            seconds++;
            miliseconds = 0;
        }
        else{
            minutes++;
            seconds = 0;
        }
    }
    else
        minutes = 0;

    this->incDeathTick();
    ++this->move_tick;
    if(this->move_tick == this->move_tick_max){
        if(this->has_hit_edge){
            this->shift();
            this->has_hit_edge = false;
        }
        else{
            for(auto& invader_row : this->invaders){
                for(auto& invader : invader_row){
                    if (invader->getSprite().getPosition().y >= this->INVADE_LINE){         //If Invader has made it far enough down... YOU LOSE
                        ship.die(*this, player_laser, explosions);
                        lives_disp.setLives(0);
                    }
                    invader->move();
                    if (invader->checkHitEdge(Globals::SCREEN_WIDTH))
                        this->has_hit_edge = true;
                }
            }
        }//else[move_tick]
        this->move_tick = 0;
        return true;
    }//if[move_tick]
    return false;
}

void InvaderFormation::shift()
{
    if(this->move_tick_max > 2)
        --this->move_tick_max;

    for(auto& invader_row : this->invaders){
        for (auto& invader : invader_row){
            invader->dropDown();
            invader->reverseDir();
        }
    }
    this->increaseFire(10);
}

void InvaderFormation::checkHit(PlayerLaser &laser, unsigned &game_score)
{
    bool speedup = 0;
    for(auto& invader_row : this->invaders){
        for(auto& invader : invader_row){
            if(!invader->isDead() && invader->isVisible() && invader->getSprite().getGlobalBounds().intersects(laser.getShape().getGlobalBounds())){
                if(invader->getLives()==1){
                    invader->die();
                    this->shootBonuses(invader);
                    game_score += invader->getScoreValue();
                    ++this->num_killed;
                    this->increaseFire(17);
                    speedup = 1;
                }
                else
                    invader->setLives(invader->getLives()-1);
                if (this->getNumKilled() == (this->getTotal() - 1) && this->getTotal() != 1){
                    this->move_tick = 0;
                    this->move_tick_max = 1;
                }
                else if (!(this->num_killed % 6) && speedup && this->move_tick_max > 1){       //Formation speeds up for every 6 Invaders killed.
                    this->move_tick_max -= 5;

                    if (this->move_tick >= this->move_tick_max)
                        this->move_tick = this->move_tick_max - 1;

                    if (this->move_tick_max < 2)                                    //Not so fast!!
                        this->move_tick_max = 2;
                    speedup = 0;
                }

                laser.stop1();
                return;
            }
            if(!invader->isDead() && invader->isVisible() && invader->getSprite().getGlobalBounds().intersects(laser.getShape2().getGlobalBounds())){
                if(invader->getLives()==1){
                    invader->die();
                    this->shootBonuses(invader);
                    game_score += invader->getScoreValue();
                    ++this->num_killed;
                    this->increaseFire(17);
                    speedup = 1;
                }
                else
                    invader->setLives(invader->getLives()-1);
                if (this->getNumKilled() == (this->getTotal() - 1) && this->getTotal() != 1){
                    this->move_tick = 0;
                    this->move_tick_max = 1;
                }
                else if (!(this->num_killed % 6) && speedup && this->move_tick_max > 1){       //Formation speeds up for every 6 Invaders killed.
                    this->move_tick_max -= 5;

                    if (this->move_tick >= this->move_tick_max)
                        this->move_tick = this->move_tick_max - 1;

                    if (this->move_tick_max < 2)                                    //Not so fast!!
                        this->move_tick_max = 2;
                    speedup = 0;
                }

                laser.stop2();
                return;
            }
        }//for[invader : invader_row]
    }
}

void InvaderFormation::updateLasers(Explosions &explosions, PlayerLaser &player_laser)
{
    this->removeHitLasers();
    this->handleCollisions(explosions, player_laser);
    this->moveLasers(explosions, player_laser);
    this->shootLasers();
}

void InvaderFormation::updateBonuses()
{
    this->removeHitBonuses();
    this->moveBonuses();
}

void InvaderFormation::removeLasers()
{
    for (auto& laser : this->lasers)
        delete laser;
    this->lasers.clear();
}

void InvaderFormation::removeBonuses()
{
    for (auto& bonus : this->bonuses)
        delete bonus;
    this->bonuses.clear();
}

void InvaderFormation::drawLasers()
{
    for(auto& laser : this->lasers)
        laser->draw(this->window);
}

void InvaderFormation::drawBonuses()
{
    for(auto& bonus : this->bonuses)
        bonus->draw(this->window);
}

void InvaderFormation::clearLevel()
{
    for (auto& invader_row : this->invaders){
        for (auto& invader : invader_row)
            delete invader;
        invader_row.clear();
    }
    this->invaders.clear();
}

void InvaderFormation::loadLevel(sf::RenderWindow &window, Textures &textures, std::string fileName)
{
    ///Vector for each row in the formation
    InvaderRow invaders1;
    InvaderRow invaders2;
    InvaderRow invaders31;
    InvaderRow invaders32;
    InvaderRow invaders4;

    std::ifstream level;
    level.open(Globals::LEVELS_PATH + fileName.c_str() + ".json");
    Json root;
    level >> root;
    level.close();

    int levelNum = root["level"];
    int total = root["total"];
    Json invader1 = root["invader1"];
    Json invader2 = root["invader2"];
    Json invader31 = root["invader31"];
    Json invader32 = root["invader32"];
    Json invader4 = root["invader4"];

    switch(levelNum){
            case 0:
                this->total = total;

                for (Json &status1 : invader1)
                    invaders1.push_back(new Invader(textures, Invader::INVADER_1, status1));
                for (Json &status2 : invader2)
                    invaders2.push_back(new Invader(textures, Invader::INVADER_2, status2));
                for (Json &status31 : invader31)
                    invaders31.push_back(new Invader(textures, Invader::INVADER_3, status31));
                for (Json &status32 : invader32)
                    invaders32.push_back(new Invader(textures, Invader::INVADER_3, status32));
                for (Json &status4 : invader4)
                    invaders4.push_back(new Invader(textures, Invader::INVADER_4, status4));
                break;
            case 1:
                this->total = total;

                for (Json &status1 : invader1)
                    invaders1.push_back(new Invader(textures, Invader::INVADER_1, status1));
                for (Json &status2 : invader2)
                    invaders2.push_back(new Invader(textures, Invader::INVADER_2, status2));
                for (Json &status31 : invader31)
                    invaders31.push_back(new Invader(textures, Invader::INVADER_3, status31));
                for (Json &status32 : invader32)
                    invaders32.push_back(new Invader(textures, Invader::INVADER_3, status32));
                for (Json &status4 : invader4)
                    invaders4.push_back(new Invader(textures, Invader::INVADER_4, status4));
                break;
            case 2:
                this->total = total;

                for (Json &status1 : invader1)
                    invaders1.push_back(new Invader(textures, Invader::INVADER_1, status1));
                for (Json &status2 : invader2)
                    invaders2.push_back(new Invader(textures, Invader::INVADER_2, status2));
                for (Json &status31 : invader31)
                    invaders31.push_back(new Invader(textures, Invader::INVADER_3, status31));
                for (Json &status32 : invader32)
                    invaders32.push_back(new Invader(textures, Invader::INVADER_3, status32));
                for (Json &status4 : invader4)
                    invaders4.push_back(new Invader(textures, Invader::INVADER_4, status4));
                break;
            case 3:
                this->total = total;

                for (Json &status1 : invader1)
                    invaders1.push_back(new Invader(textures, Invader::INVADER_1, status1));
                for (Json &status2 : invader2)
                    invaders2.push_back(new Invader(textures, Invader::INVADER_2, status2));
                for (Json &status31 : invader31)
                    invaders31.push_back(new Invader(textures, Invader::INVADER_3, status31));
                for (Json &status32 : invader32)
                    invaders32.push_back(new Invader(textures, Invader::INVADER_3, status32));
                for (Json &status4 : invader4)
                    invaders4.push_back(new Invader(textures, Invader::INVADER_4, status4));
                break;
            case 4:
                this->total = total;

                for (Json &status1 : invader1)
                    invaders1.push_back(new Invader(textures, Invader::TOUGH, status1));
                for (Json &status2 : invader2)
                    invaders2.push_back(new Invader(textures, Invader::TOUGH, status2));
                for (Json &status31 : invader31)
                    invaders31.push_back(new Invader(textures, Invader::TOUGH, status31));
                for (Json &status32 : invader32)
                    invaders32.push_back(new Invader(textures, Invader::TOUGH, status32));
                for (Json &status4 : invader4)
                    invaders4.push_back(new Invader(textures, Invader::TOUGH, status4));
                break;
            case 5:
                this->total = total;

                for (Json &status1 : invader1)
                    invaders1.push_back(new Invader(textures, Invader::INVADER_1, status1));
                for (Json &status2 : invader2)
                    invaders2.push_back(new Invader(textures, Invader::INVADER_2, status2));
                for (Json &status31 : invader31)
                    invaders31.push_back(new Invader(textures, Invader::INVADER_3, status31));
                for (Json &status32 : invader32)
                    invaders32.push_back(new Invader(textures, Invader::INVADER_3, status32));
                for (Json &status4 : invader4)
                    invaders4.push_back(new Invader(textures, Invader::INVADER_4, status4));
                break;
            case 6:
                this->total = total;

                for (Json &status1 : invader1)
                    invaders1.push_back(new Invader(textures, Invader::INVADER_1, status1));
                for (Json &status2 : invader2)
                    invaders2.push_back(new Invader(textures, Invader::INVADER_2, status2));
                for (Json &status31 : invader31)
                    invaders31.push_back(new Invader(textures, Invader::INVADER_3, status31));
                for (Json &status32 : invader32)
                    invaders32.push_back(new Invader(textures, Invader::INVADER_3, status32));
                for (Json &status4 : invader4)
                    invaders4.push_back(new Invader(textures, Invader::INVADER_4, status4));
                break;
            case 7:
                this->total = total;

                for (Json &status1 : invader1)
                    invaders1.push_back(new Invader(textures, Invader::INVADER_1, status1));
                for (Json &status2 : invader2)
                    invaders2.push_back(new Invader(textures, Invader::INVADER_2, status2));
                for (Json &status31 : invader31)
                    invaders31.push_back(new Invader(textures, Invader::INVADER_3, status31));
                for (Json &status32 : invader32)
                    invaders32.push_back(new Invader(textures, Invader::INVADER_3, status32));
                for (Json &status4 : invader4)
                    invaders4.push_back(new Invader(textures, Invader::INVADER_4, status4));
                break;
            case 8:
                this->total = total;

                for (Json &status1 : invader1)
                    invaders1.push_back(new Invader(textures, Invader::INVADER_1, status1));
                for (Json &status2 : invader2)
                    invaders2.push_back(new Invader(textures, Invader::INVADER_2, status2));
                for (Json &status31 : invader31)
                    invaders31.push_back(new Invader(textures, Invader::INVADER_3, status31));
                for (Json &status32 : invader32)
                    invaders32.push_back(new Invader(textures, Invader::INVADER_3, status32));
                for (Json &status4 : invader4)
                    invaders4.push_back(new Invader(textures, Invader::INVADER_4, status4));
                break;
            case 9:
                this->total = total;

                for (Json &status1 : invader1)
                    invaders1.push_back(new Invader(textures, Invader::INVADER_1, status1));
                for (Json &status2 : invader2)
                    invaders2.push_back(new Invader(textures, Invader::INVADER_2, status2));
                for (Json &status31 : invader31)
                    invaders31.push_back(new Invader(textures, Invader::INVADER_3, status31));
                for (Json &status32 : invader32)
                    invaders32.push_back(new Invader(textures, Invader::INVADER_3, status32));
                for (Json &status4 : invader4)
                    invaders4.push_back(new Invader(textures, Invader::INVADER_4, status4));
                break;
            case 10:
                this->total = total;

                for (Json &status1 : invader1)
                    invaders1.push_back(new Invader(textures, Invader::BOSS, status1));
                for (Json &status2 : invader2)
                    invaders2.push_back(new Invader(textures, Invader::BOSS, status2));
                for (Json &status31 : invader31)
                    invaders31.push_back(new Invader(textures, Invader::BOSS, status31));
                for (Json &status32 : invader32)
                    invaders32.push_back(new Invader(textures, Invader::BOSS, status32));
                for (Json &status4 : invader4)
                    invaders4.push_back(new Invader(textures, Invader::BOSS, status4));
                this->xgap = 100;
                this->ygap = 70;
                break;
            default:
                break;
        }


    ///Now add each row to the main vector
    this->invaders.push_back(invaders1);
    this->invaders.push_back(invaders2);
    this->invaders.push_back(invaders31);
    this->invaders.push_back(invaders32);
    this->invaders.push_back(invaders4);

    this->reset();
}

InvaderFormation::InvaderFormation(sf::RenderWindow &window): window(window), move_tick(0), move_tick_max(MOVE_TICK_MAX_START), move_tick_change(MOVE_TICK_CHANGE_START),  num_killed(0),
                                    has_hit_edge(false), shot_chance(SHOT_CHANCE_START), xgap(55), ygap(50)
{
}

InvaderFormation::~InvaderFormation()
{
    for (auto& invader_row : this->invaders){
        for (auto& invader : invader_row)
            delete invader;
        invader_row.clear();
    }
    this->invaders.clear();
    this->removeLasers();
    this->removeBonuses();
}

void InvaderFormation::update(PlayerLaser &laser, Spaceship &ship, PlayerLaser &player_laser, LivesDisplay &lives_disp, Explosions &explosions, unsigned &game_score, unsigned &minutes, unsigned &seconds, unsigned &miliseconds)
{
    this->move(ship, player_laser, lives_disp, explosions, minutes, seconds, miliseconds);
    this->checkHit(laser, game_score);
    this->updateLasers(explosions, player_laser);
    this->updateBonuses();
}

void InvaderFormation::draw(int amount)
{
    for (auto iter = this->invaders.end(); iter != this->invaders.begin();){
        --iter;                     //end() can't be dereferenced, so immediately decrement the iterator.
        for (auto& invader : *iter){
            if((!invader->isDead() || (invader->isDead() && invader->isExploding())) && invader->isVisible()){
                this->window.draw(invader->getSprite());
                --amount;
                if(amount == 0)
                    return;
            }//if
        }//for
    }//for
}
