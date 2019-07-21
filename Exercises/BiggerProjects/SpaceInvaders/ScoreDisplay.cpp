/**
* Name: ScoreDisplay.cpp
* Purpose: Class ScoreDisplay
*
* @author Fenris
* @version 0.84a 03/05/2017
*/
#include "ScoreDisplay.h"
#include "game.h"

ScoreDisplay::ScoreDisplay(unsigned &score): game_score(score)
{
    this->reset();
}

void ScoreDisplay::reset()
{
    this->game_score = 0;
}

void ScoreDisplay::drawScore(sf::RenderWindow &window, const unsigned score, const unsigned x, const unsigned y)
{
    std::ostringstream ss_score;
    ss_score <<(score / 10000) % 10 << " " <<(score / 1000) % 10 << " " << (score / 100) % 10 << " " << (score / 10) % 10 << " " << (score / 1) % 10;
    Game::draw_text(window, ss_score.str(), x, y, sf::Color::White, 44);
}

void ScoreDisplay::draw(sf::RenderWindow &window)
{
    Game::draw_text(window, "SCORE", this->X + 70, this->Y + 34, sf::Color::White, 30);
    this->drawScore(window, this->game_score, this->X + 150, this->Y + 20);
}
