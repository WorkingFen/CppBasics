/**
* Name: ClockDisplay.cpp
* Purpose: Class ClockDisplay
*
* @author Fenris
* @version 1.05a 03/05/2017
*/
#include "ClockDisplay.h"
#include "game.h"

ClockDisplay::ClockDisplay(unsigned &minutes, unsigned &seconds, unsigned &miliseconds): minutes(minutes), seconds(seconds), miliseconds(miliseconds)
{
    this->reset();
}

void ClockDisplay::reset()
{
    this->minutes = 0;
    this->seconds = 0;
    this->miliseconds = 0;
}

void ClockDisplay::drawClock(sf::RenderWindow &window, const unsigned minutes, const unsigned seconds, const unsigned miliseconds, const unsigned x, const unsigned y)
{
    std::ostringstream ss_Minutes;
    std::ostringstream ss_Seconds;
    std::ostringstream ss_Miliseconds;
    std::ostringstream ss_Clock;
    ss_Minutes <<(minutes / 10) % 10 << " " <<(minutes / 1) % 10 << " : ";
    ss_Seconds <<(seconds / 10) % 10 << " " <<(seconds / 1) % 10 << " : ";
    ss_Miliseconds <<(miliseconds/ 10) % 10 << " " <<(miliseconds / 1) % 10;
    ss_Clock << ss_Minutes.str() << ss_Seconds.str() << ss_Miliseconds.str();
    Game::draw_text(window, ss_Clock.str(), x, y, sf::Color::White, 44);
}

void ClockDisplay::draw(sf::RenderWindow &window)
{
    Game::draw_text(window, "TIME", this->X + 1040, this->Y + 34, sf::Color::White, 30);
    this->drawClock(window, this->minutes, this->seconds, this->miliseconds, this->X + 1110, this->Y + 20);
}
