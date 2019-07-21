/**
* Name: Textures.cpp
* Purpose: Class Textures
*
* @author Fenris
* @version 1.03a 14/05/2017
*/
#include "Textures.h"

sf::Image Textures::loadSprites(const std::string img)
{
    sf::Image ss;
    ss.loadFromFile(img);
    return ss;
}

Textures::Textures()
{
    this->spritesheet = this->loadSprites(Globals::SPRITES_PATH + "sprites.png");
    this->monsterssheet = this->loadSprites(Globals::SPRITES_PATH + "monsters.png");

    sf::IntRect INVADER_11_RECT(7, 35, 20, 20);                             //It creates rectangle with (coordinates x, coordinates y, width, height)
    sf::IntRect INVADER_12_RECT(36, 35, 20, 20);
    sf::IntRect INVADER_13_RECT(7, 73, 20, 24);
    sf::IntRect INVADER_14_RECT(36, 69, 20, 28);
    this->INVADER_11.loadFromImage(this->monsterssheet, INVADER_11_RECT);
    this->INVADER_12.loadFromImage(this->monsterssheet, INVADER_12_RECT);
    this->INVADER_13.loadFromImage(this->monsterssheet, INVADER_13_RECT);
    this->INVADER_14.loadFromImage(this->monsterssheet, INVADER_14_RECT);

    sf::IntRect INVADER_21_RECT(76, 35, 20, 20);
    sf::IntRect INVADER_22_RECT(106, 35, 20, 24);
    sf::IntRect INVADER_23_RECT(76, 73, 20, 24);
    sf::IntRect INVADER_24_RECT(102, 73, 28, 24);
    this->INVADER_21.loadFromImage(this->monsterssheet, INVADER_21_RECT);
    this->INVADER_22.loadFromImage(this->monsterssheet, INVADER_22_RECT);
    this->INVADER_23.loadFromImage(this->monsterssheet, INVADER_23_RECT);
    this->INVADER_24.loadFromImage(this->monsterssheet, INVADER_24_RECT);

    sf::IntRect INVADER_31_RECT(146, 35, 24, 24);
    sf::IntRect INVADER_32_RECT(183, 35, 24, 28);
    sf::IntRect INVADER_33_RECT(142, 69, 32, 36);
    sf::IntRect INVADER_34_RECT(179, 73, 32, 24);
    this->INVADER_31.loadFromImage(this->monsterssheet, INVADER_31_RECT);
    this->INVADER_32.loadFromImage(this->monsterssheet, INVADER_32_RECT);
    this->INVADER_33.loadFromImage(this->monsterssheet, INVADER_33_RECT);
    this->INVADER_34.loadFromImage(this->monsterssheet, INVADER_34_RECT);

    sf::IntRect INVADER_41_RECT(231, 35, 28, 28);
    sf::IntRect INVADER_42_RECT(275, 35, 28, 28);
    sf::IntRect INVADER_43_RECT(231, 73, 28, 32);
    sf::IntRect INVADER_44_RECT(275, 69, 28, 36);
    this->INVADER_41.loadFromImage(this->monsterssheet, INVADER_41_RECT);
    this->INVADER_42.loadFromImage(this->monsterssheet, INVADER_42_RECT);
    this->INVADER_43.loadFromImage(this->monsterssheet, INVADER_43_RECT);
    this->INVADER_44.loadFromImage(this->monsterssheet, INVADER_44_RECT);

    sf::IntRect UFO_1_RECT(310, 94, 64, 36);
    sf::IntRect UFO_2_RECT(381, 94, 64, 36);
    sf::IntRect UFO_3_RECT(451, 94, 64, 36);
    sf::IntRect UFO_4_RECT(522, 94, 64, 36);
    this->UFO_1.loadFromImage(this->monsterssheet, UFO_1_RECT);
    this->UFO_2.loadFromImage(this->monsterssheet, UFO_2_RECT);
    this->UFO_3.loadFromImage(this->monsterssheet, UFO_3_RECT);
    this->UFO_4.loadFromImage(this->monsterssheet, UFO_4_RECT);

    sf::IntRect CREEPER_1_RECT(514, 7, 28, 22);
    sf::IntRect CREEPER_2_RECT(547, 7, 28, 22);
    sf::IntRect CREEPER_3_RECT(514, 33, 28, 22);
    sf::IntRect CREEPER_4_RECT(547, 33, 28, 22);
    this->CREEPER_1.loadFromImage(this->monsterssheet, CREEPER_1_RECT);
    this->CREEPER_2.loadFromImage(this->monsterssheet, CREEPER_2_RECT);
    this->CREEPER_3.loadFromImage(this->monsterssheet, CREEPER_3_RECT);
    this->CREEPER_4.loadFromImage(this->monsterssheet, CREEPER_4_RECT);

    sf::IntRect TOUGH_1_RECT(435, 6, 32, 32);
    sf::IntRect TOUGH_2_RECT(478, 6, 32, 32);
    sf::IntRect TOUGH_3_RECT(435, 45, 32, 32);
    sf::IntRect TOUGH_4_RECT(478, 45, 32, 32);
    this->TOUGH_1.loadFromImage(this->monsterssheet, TOUGH_1_RECT);
    this->TOUGH_2.loadFromImage(this->monsterssheet, TOUGH_2_RECT);
    this->TOUGH_3.loadFromImage(this->monsterssheet, TOUGH_3_RECT);
    this->TOUGH_4.loadFromImage(this->monsterssheet, TOUGH_4_RECT);

    sf::IntRect BOSS_1_RECT(318, 6, 44, 32);
    sf::IntRect BOSS_2_RECT(379, 6, 44, 32);
    sf::IntRect BOSS_3_RECT(318, 48, 44, 32);
    sf::IntRect BOSS_4_RECT(379, 48, 44, 32);
    this->BOSS_1.loadFromImage(this->monsterssheet, BOSS_1_RECT);
    this->BOSS_2.loadFromImage(this->monsterssheet, BOSS_2_RECT);
    this->BOSS_3.loadFromImage(this->monsterssheet, BOSS_3_RECT);
    this->BOSS_4.loadFromImage(this->monsterssheet, BOSS_4_RECT);

    sf::IntRect SHIP_1_RECT(332, 35, 30, 20);
    sf::IntRect SHIP_2_RECT(372, 35, 30, 22);
    sf::IntRect SHIP_3_RECT(332, 72, 30, 24);
    sf::IntRect SHIP_4_RECT(372, 72, 30, 26);
    this->SHIP_1.loadFromImage(this->spritesheet, SHIP_1_RECT);
    this->SHIP_2.loadFromImage(this->spritesheet, SHIP_2_RECT);
    this->SHIP_3.loadFromImage(this->spritesheet, SHIP_3_RECT);
    this->SHIP_4.loadFromImage(this->spritesheet, SHIP_4_RECT);

    sf::IntRect EXPLOSION_1_RECT(429, 42, 16, 16);
    sf::IntRect EXPLOSION_2_RECT(451, 34, 28, 28);
    sf::IntRect EXPLOSION_3_RECT(485, 34, 28, 28);
    this->EXPLOSION_1.loadFromImage(this->spritesheet, EXPLOSION_1_RECT);
    this->EXPLOSION_2.loadFromImage(this->spritesheet, EXPLOSION_2_RECT);
    this->EXPLOSION_3.loadFromImage(this->spritesheet, EXPLOSION_3_RECT);

    sf::IntRect ARROW_1_RECT(437, 74, 24, 28);
    sf::IntRect ARROW_2_RECT(461, 74, 24, 28);
    sf::IntRect ARROW_3_RECT(485, 74, 24, 28);
    sf::IntRect ARROW_4_RECT(509, 74, 24, 28);
    sf::IntRect ARROW_5_RECT(533, 74, 24, 28);
    sf::IntRect ARROW_6_RECT(557, 74, 24, 28);
    sf::IntRect ARROW_7_RECT(581, 74, 24, 28);
    sf::IntRect ARROW_8_RECT(605, 74, 24, 28);
    sf::IntRect ARROW_9_RECT(437, 102, 24, 28);
    sf::IntRect ARROW_10_RECT(461, 102, 24, 28);
    sf::IntRect ARROW_11_RECT(485, 102, 24, 28);
    sf::IntRect ARROW_12_RECT(509, 102, 24, 28);
    sf::IntRect ARROW_13_RECT(533, 102, 24, 28);
    sf::IntRect ARROW_14_RECT(557, 102, 24, 28);
    sf::IntRect ARROW_15_RECT(581, 102, 24, 28);
    this->ARROW_1.loadFromImage(this->spritesheet, ARROW_1_RECT);
    this->ARROW_2.loadFromImage(this->spritesheet, ARROW_2_RECT);
    this->ARROW_3.loadFromImage(this->spritesheet, ARROW_3_RECT);
    this->ARROW_4.loadFromImage(this->spritesheet, ARROW_4_RECT);
    this->ARROW_5.loadFromImage(this->spritesheet, ARROW_5_RECT);
    this->ARROW_6.loadFromImage(this->spritesheet, ARROW_6_RECT);
    this->ARROW_7.loadFromImage(this->spritesheet, ARROW_7_RECT);
    this->ARROW_8.loadFromImage(this->spritesheet, ARROW_8_RECT);
    this->ARROW_9.loadFromImage(this->spritesheet, ARROW_9_RECT);
    this->ARROW_10.loadFromImage(this->spritesheet, ARROW_10_RECT);
    this->ARROW_11.loadFromImage(this->spritesheet, ARROW_11_RECT);
    this->ARROW_12.loadFromImage(this->spritesheet, ARROW_12_RECT);
    this->ARROW_13.loadFromImage(this->spritesheet, ARROW_13_RECT);
    this->ARROW_14.loadFromImage(this->spritesheet, ARROW_14_RECT);
    this->ARROW_15.loadFromImage(this->spritesheet, ARROW_15_RECT);

    sf::IntRect BONUS_1_RECT(6, 117, 28, 17);
    sf::IntRect BONUS_2_RECT(36, 117, 28, 17);
    sf::IntRect BONUS_3_RECT(66, 117, 28, 17);
    sf::IntRect BONUS_4_RECT(96, 117, 28, 17);
    sf::IntRect BONUS_5_RECT(126, 117, 28, 17);
    sf::IntRect BONUS_6_RECT(156, 117, 28, 17);
    sf::IntRect BONUS_7_RECT(186, 117, 28, 17);
    sf::IntRect BONUS_8_RECT(216, 117, 28, 17);
    this->BONUS_1.loadFromImage(this->spritesheet, BONUS_1_RECT);
    this->BONUS_2.loadFromImage(this->spritesheet, BONUS_2_RECT);
    this->BONUS_3.loadFromImage(this->spritesheet, BONUS_3_RECT);
    this->BONUS_4.loadFromImage(this->spritesheet, BONUS_4_RECT);
    this->BONUS_5.loadFromImage(this->spritesheet, BONUS_5_RECT);
    this->BONUS_6.loadFromImage(this->spritesheet, BONUS_6_RECT);
    this->BONUS_7.loadFromImage(this->spritesheet, BONUS_7_RECT);
    this->BONUS_8.loadFromImage(this->spritesheet, BONUS_8_RECT);
}
