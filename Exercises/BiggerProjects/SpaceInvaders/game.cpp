/**
* Name: game.cpp
* Purpose: Namespace Game
*
* @author Fenris
* @version 1.03a 14/05/2017
*/
#include <fstream>
#include <sstream>
#include "game.h"
#include "globals.h"
#include <windows.h>

bool Game::life_awarded = false;                        //Bool to check if you got extra life

///It's just controls for getting to menu, or to close the game
void Game::handle_events(sf::Window &window, sf::RenderWindow &windows, Textures &textures, ClockDisplay &clock_disp, Info &info, Save &save,
                         MenuIG &menuig, Load &load, Menu &menu, ScoreDisplay &score_disp, LivesDisplay &lives_disp, InvaderFormation &invaders,
                         PlayerLaser &player_laser, Spaceship &ship, Explosions &explosions, unsigned &wave_on){
    sf::Event event;
    while (window.pollEvent(event)){
        switch (event.type){
            case sf::Event::Closed:                     //First case: Event::Closed
                window.close();
                break;
            case sf::Event::KeyPressed:                 //Second case: Event::KeyPressed
                if(Globals::GAME_STATE != Globals::States::MENU && Globals::GAME_STATE != Globals::States::MENUIG){
                    switch (event.key.code){                ///Which key?
                        case sf::Keyboard::Escape:          //Escape
                            if(Globals::GAME_STATE == Globals::States::SAVE)
                                save.fileName = "";
                            if(Globals::GAME_STATE == Globals::States::PLAY || Globals::PREVIOUS_STATE == Globals::States::MENUIG)
                                goto_menuig(menuig);
                            else if(Globals::PREVIOUS_STATE == Globals::States::MENU)
                                goto_menu(menu, clock_disp, score_disp, lives_disp, invaders, ship, player_laser, explosions, wave_on);
                            break;
                        default:
                            break;
                    }
                }
                break;
            case sf::Event::KeyReleased:
                if(Globals::GAME_STATE == Globals::States::MENU){               ///If you are in state MENU
                    switch(event.key.code){
                        case sf::Keyboard::Up:                                  //Change option if you pressed UP
                            menu.setSelect(menu.getSelect()-1);
                            break;
                        case sf::Keyboard::Down:                                //Change option if you pressed DOWN
                            menu.setSelect(menu.getSelect()+1);
                            break;
                        case sf::Keyboard::Return:
                            if (menu.getSelect()%5 == 0){                       //Play if you pressed ENTER and is on Option NEW_GAME
                                play_game(windows, textures, invaders, player_laser, ship, explosions, wave_on);
                                Globals::PREVIOUS_STATE = Globals::States::MENUIG;
                            }
                            else if (menu.getSelect()%5 == 1)                   //Save game if you pressed ENTER and is on Option SAVE
                                goto_saving(save);
                            else if (menu.getSelect()%5 == 2)                   //Load your game if you pressed ENTER and is on Option LOAD
                                goto_loading(load);
                            else if (menu.getSelect()%5 == 3)                   //Check info if you pressed ENTER and is on Option INFO
                                goto_info(info);
                            else if (menu.getSelect()%5 == 4)                   //Quit if you pressed ENTER and is on Option QUIT
                                window.close();
                            break;
                        default:
                            break;
                    }
                }

                else if(Globals::GAME_STATE == Globals::States::LOAD){          ///If you are in state LOAD
                    switch(event.key.code){
                        case sf::Keyboard::A:
                            load.fileName.push_back('A');
                            break;
                        case sf::Keyboard::B:
                            load.fileName.push_back('B');
                            break;
                        case sf::Keyboard::C:
                            load.fileName.push_back('C');
                            break;
                        case sf::Keyboard::D:
                            load.fileName.push_back('D');
                            break;
                        case sf::Keyboard::E:
                            load.fileName.push_back('E');
                            break;
                        case sf::Keyboard::F:
                            load.fileName.push_back('F');
                            break;
                        case sf::Keyboard::G:
                            load.fileName.push_back('G');
                            break;
                        case sf::Keyboard::H:
                            load.fileName.push_back('H');
                            break;
                        case sf::Keyboard::I:
                            load.fileName.push_back('I');
                            break;
                        case sf::Keyboard::J:
                            load.fileName.push_back('J');
                            break;
                        case sf::Keyboard::K:
                            load.fileName.push_back('K');
                            break;
                        case sf::Keyboard::L:
                            load.fileName.push_back('L');
                            break;
                        case sf::Keyboard::M:
                            load.fileName.push_back('M');
                            break;
                        case sf::Keyboard::N:
                            load.fileName.push_back('N');
                            break;
                        case sf::Keyboard::O:
                            load.fileName.push_back('O');
                            break;
                        case sf::Keyboard::P:
                            load.fileName.push_back('P');
                            break;
                        case sf::Keyboard::Q:
                            load.fileName.push_back('Q');
                            break;
                        case sf::Keyboard::R:
                            load.fileName.push_back('R');
                            break;
                        case sf::Keyboard::S:
                            load.fileName.push_back('S');
                            break;
                        case sf::Keyboard::T:
                            load.fileName.push_back('T');
                            break;
                        case sf::Keyboard::U:
                            load.fileName.push_back('U');
                            break;
                        case sf::Keyboard::V:
                            load.fileName.push_back('V');
                            break;
                        case sf::Keyboard::W:
                            load.fileName.push_back('W');
                            break;
                        case sf::Keyboard::X:
                            load.fileName.push_back('X');
                            break;
                        case sf::Keyboard::Y:
                            load.fileName.push_back('Y');
                            break;
                        case sf::Keyboard::Z:
                            load.fileName.push_back('Z');
                            break;
                        case sf::Keyboard::Space:
                            load.fileName.push_back('_');
                            break;
                        case sf::Keyboard::Num0:
                            load.fileName.push_back('0');
                            break;
                        case sf::Keyboard::Num1:
                            load.fileName.push_back('1');
                            break;
                        case sf::Keyboard::Num2:
                            load.fileName.push_back('2');
                            break;
                        case sf::Keyboard::Num3:
                            load.fileName.push_back('3');
                            break;
                        case sf::Keyboard::Num4:
                            load.fileName.push_back('4');
                            break;
                        case sf::Keyboard::Num5:
                            load.fileName.push_back('5');
                            break;
                        case sf::Keyboard::Num6:
                            load.fileName.push_back('6');
                            break;
                        case sf::Keyboard::Num7:
                            load.fileName.push_back('7');
                            break;
                        case sf::Keyboard::Num8:
                            load.fileName.push_back('8');
                            break;
                        case sf::Keyboard::Num9:
                            load.fileName.push_back('9');
                            break;
                        case sf::Keyboard::Numpad0:
                            load.fileName.push_back('0');
                            break;
                        case sf::Keyboard::Numpad1:
                            load.fileName.push_back('1');
                            break;
                        case sf::Keyboard::Numpad2:
                            load.fileName.push_back('2');
                            break;
                        case sf::Keyboard::Numpad3:
                            load.fileName.push_back('3');
                            break;
                        case sf::Keyboard::Numpad4:
                            load.fileName.push_back('4');
                            break;
                        case sf::Keyboard::Numpad5:
                            load.fileName.push_back('5');
                            break;
                        case sf::Keyboard::Numpad6:
                            load.fileName.push_back('6');
                            break;
                        case sf::Keyboard::Numpad7:
                            load.fileName.push_back('7');
                            break;
                        case sf::Keyboard::Numpad8:
                            load.fileName.push_back('8');
                            break;
                        case sf::Keyboard::Numpad9:
                            load.fileName.push_back('9');
                            break;
                        case sf::Keyboard::Return:
                            try{
                                load.doLoad();
                            }
                            catch(std::string msg){
                                MessageBox(NULL, msg.c_str(), NULL, MB_OK | MB_ICONEXCLAMATION);
                                reset_game(menu, clock_disp, score_disp, lives_disp, invaders, ship, player_laser, explosions, wave_on);
                                wave_on = -1;
                                play_game(windows, textures, invaders, player_laser, ship, explosions, wave_on);
                            }
                            catch(...){
                                std::string msg = "Fatal error while loading game from file " + load.fileName + "No file or directory";
                                MessageBox(NULL, msg.c_str(), NULL, MB_OK | MB_ICONEXCLAMATION);
                                exit(20);
                            }
                            load.fileName = "";
                            play_game(windows, textures, invaders, player_laser, ship, explosions, wave_on);
                            break;
                        case sf::Keyboard::BackSpace:
                            if(load.fileName != "")
                                load.fileName.pop_back();
                            break;
                        default:
                            break;
                    }
                }

                else if(Globals::GAME_STATE == Globals::States::SAVE){          ///If you are in state SAVE
                    switch(event.key.code){
                        case sf::Keyboard::A:
                            save.fileName.push_back('A');
                            break;
                        case sf::Keyboard::B:
                            save.fileName.push_back('B');
                            break;
                        case sf::Keyboard::C:
                            save.fileName.push_back('C');
                            break;
                        case sf::Keyboard::D:
                            save.fileName.push_back('D');
                            break;
                        case sf::Keyboard::E:
                            save.fileName.push_back('E');
                            break;
                        case sf::Keyboard::F:
                            save.fileName.push_back('F');
                            break;
                        case sf::Keyboard::G:
                            save.fileName.push_back('G');
                            break;
                        case sf::Keyboard::H:
                            save.fileName.push_back('H');
                            break;
                        case sf::Keyboard::I:
                            save.fileName.push_back('I');
                            break;
                        case sf::Keyboard::J:
                            save.fileName.push_back('J');
                            break;
                        case sf::Keyboard::K:
                            save.fileName.push_back('K');
                            break;
                        case sf::Keyboard::L:
                            save.fileName.push_back('L');
                            break;
                        case sf::Keyboard::M:
                            save.fileName.push_back('M');
                            break;
                        case sf::Keyboard::N:
                            save.fileName.push_back('N');
                            break;
                        case sf::Keyboard::O:
                            save.fileName.push_back('O');
                            break;
                        case sf::Keyboard::P:
                            save.fileName.push_back('P');
                            break;
                        case sf::Keyboard::Q:
                            save.fileName.push_back('Q');
                            break;
                        case sf::Keyboard::R:
                            save.fileName.push_back('R');
                            break;
                        case sf::Keyboard::S:
                            save.fileName.push_back('S');
                            break;
                        case sf::Keyboard::T:
                            save.fileName.push_back('T');
                            break;
                        case sf::Keyboard::U:
                            save.fileName.push_back('U');
                            break;
                        case sf::Keyboard::V:
                            save.fileName.push_back('V');
                            break;
                        case sf::Keyboard::W:
                            save.fileName.push_back('W');
                            break;
                        case sf::Keyboard::X:
                            save.fileName.push_back('X');
                            break;
                        case sf::Keyboard::Y:
                            save.fileName.push_back('Y');
                            break;
                        case sf::Keyboard::Z:
                            save.fileName.push_back('Z');
                            break;
                        case sf::Keyboard::Space:
                            save.fileName.push_back('_');
                            break;
                        case sf::Keyboard::Num0:
                            save.fileName.push_back('0');
                            break;
                        case sf::Keyboard::Num1:
                            save.fileName.push_back('1');
                            break;
                        case sf::Keyboard::Num2:
                            save.fileName.push_back('2');
                            break;
                        case sf::Keyboard::Num3:
                            save.fileName.push_back('3');
                            break;
                        case sf::Keyboard::Num4:
                            save.fileName.push_back('4');
                            break;
                        case sf::Keyboard::Num5:
                            save.fileName.push_back('5');
                            break;
                        case sf::Keyboard::Num6:
                            save.fileName.push_back('6');
                            break;
                        case sf::Keyboard::Num7:
                            save.fileName.push_back('7');
                            break;
                        case sf::Keyboard::Num8:
                            save.fileName.push_back('8');
                            break;
                        case sf::Keyboard::Num9:
                            save.fileName.push_back('9');
                            break;
                        case sf::Keyboard::Numpad0:
                            save.fileName.push_back('0');
                            break;
                        case sf::Keyboard::Numpad1:
                            save.fileName.push_back('1');
                            break;
                        case sf::Keyboard::Numpad2:
                            save.fileName.push_back('2');
                            break;
                        case sf::Keyboard::Numpad3:
                            save.fileName.push_back('3');
                            break;
                        case sf::Keyboard::Numpad4:
                            save.fileName.push_back('4');
                            break;
                        case sf::Keyboard::Numpad5:
                            save.fileName.push_back('5');
                            break;
                        case sf::Keyboard::Numpad6:
                            save.fileName.push_back('6');
                            break;
                        case sf::Keyboard::Numpad7:
                            save.fileName.push_back('7');
                            break;
                        case sf::Keyboard::Numpad8:
                            save.fileName.push_back('8');
                            break;
                        case sf::Keyboard::Numpad9:
                            save.fileName.push_back('9');
                            break;
                        case sf::Keyboard::Return:
                            try{
                                save.doSave();
                            }
                            catch(std::string msg){
                                MessageBox(NULL, msg.c_str(), NULL, MB_OK | MB_ICONEXCLAMATION);
                            }
                            catch(int wave){
                                std::string msg = "An error occurred with saving level";
                                MessageBox(NULL, msg.c_str(), NULL, MB_OK | MB_ICONEXCLAMATION);
                                wave_on = wave;
                            }
                            catch(...){
                                std::string msg = "Fatal error while saving game in file " + save.fileName;
                                MessageBox(NULL, msg.c_str(), NULL, MB_OK | MB_ICONEXCLAMATION);
                                exit(21);
                            }
                            save.fileName = "";
                            if(Globals::GAME_STATE == Globals::States::PLAY || Globals::PREVIOUS_STATE == Globals::States::MENUIG)
                                goto_menuig(menuig);
                            else if(Globals::PREVIOUS_STATE == Globals::States::MENU)
                                goto_menu(menu, clock_disp, score_disp, lives_disp, invaders, ship, player_laser, explosions, wave_on);
                            break;
                        case sf::Keyboard::BackSpace:
                            if(save.fileName != "")
                                save.fileName.pop_back();
                            break;
                        default:
                            break;
                    }
                }

                else if(Globals::GAME_STATE == Globals::States::MENUIG){        ///If you are in state MENUIG
                    switch(event.key.code){
                        case sf::Keyboard::Up:                                  //Change option if you pressed UP
                            menuig.setSelect(menuig.getSelect()-1);
                            break;
                        case sf::Keyboard::Down:                                //Change option if you pressed DOWN
                            menuig.setSelect(menuig.getSelect()+1);
                            break;
                        case sf::Keyboard::Return:
                            if (menuig.getSelect()%5 == 0)                      //Return to game if you pressed ENTER and is on Option RETURN
                                Globals::GAME_STATE = Globals::States::PLAY;    //Well... This one line makes everything fine
                            else if (menuig.getSelect()%5 == 1)                 //Save game if you pressed ENTER and is on Option SAVE
                                goto_saving(save);
                            else if (menuig.getSelect()%5 == 2)                 //Load your game if you pressed ENTER and is on Option LOAD
                                goto_loading(load);
                            else if (menuig.getSelect()%5 == 3)                 //Check info if you pressed ENTER and is on Option INFO
                                goto_info(info);
                            else if (menuig.getSelect()%5 == 4)                 //Go to menu if you pressed ENTER and is on Option MENU
                                goto_menu(menu, clock_disp, score_disp, lives_disp, invaders, ship, player_laser, explosions, wave_on);
                            break;
                        default:
                            break;
                    }
                }
                break;
            case sf::Event::MouseButtonPressed:         //Third case: Event::MouseButtonPressed
                switch (event.mouseButton.button){      ///Which button?
                    case sf::Mouse::Middle:             //Middle button
                        window.close();
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        } //switch[event.type]
    } //while
} //Function

///Controls to move your ship, play game or fire lasers
void Game::real_time_key(PlayerLaser &player_laser, Spaceship &ship){
    if (Globals::GAME_STATE == Globals::States::WAVE_SETUP || Globals::GAME_STATE == Globals::States::GAME_OVER)
        return;

    ///Move your ship out of my property!
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        ship.move(1);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        ship.move(-1);

    ///I'M A' FIRIN' MAH LAZER!!
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !ship.isHit() && !player_laser.isShooting()){
        sf::Vector2f shippos = ship.getSprite().getPosition();
        player_laser.shoot(shippos.x, shippos.y);
    }
}

///Draw the player's laser beam
void Game::draw_player_laser(sf::RenderWindow &window, PlayerLaser &laser){
    if (laser.isShooting())
        window.draw(laser.getShape());
    if (laser.isShooting2())
        window.draw(laser.getShape2());
}

///Up to date with all the objects on the screen
void Game::update_objects(sf::RenderWindow &window, Stars &stars, MenuIG &menuig, Load &load, Save &save, Menu &menu, Textures &textures, Spaceship &ship, PlayerLaser &player_laser, InvaderFormation &invaders, LivesDisplay &lives_disp, Explosions &explosions, unsigned &game_score, unsigned &wave_on, unsigned &minutes, unsigned &seconds, unsigned &miliseconds){
    stars.updateStars(window);

    if (Globals::GAME_STATE == Globals::States::WAVE_SETUP || Globals::GAME_STATE == Globals::States::GAME_OVER)
        return;

    if (Globals::GAME_STATE == Globals::States::MENU){
        menu.update(textures);
        real_time_key(player_laser, ship);
        return;
    }

    if (Globals::GAME_STATE == Globals::States::MENUIG){
        menuig.update(textures);
        real_time_key(player_laser, ship);
        return;
    }

    if (Globals::GAME_STATE == Globals::States::INFO){
        real_time_key(player_laser, ship);
        return;
    }

    if (Globals::GAME_STATE == Globals::States::SAVE){
        save.update(textures);
        real_time_key(player_laser, ship);
        return;
    }

    if (Globals::GAME_STATE == Globals::States::LOAD){
        load.update(textures);
        real_time_key(player_laser, ship);
        return;
    }

    if (Globals::GAME_STATE != Globals::States::PLAYER_KILLED){
        real_time_key(player_laser, ship);
        player_laser.move(explosions);
        invaders.update(player_laser, ship, player_laser, lives_disp, explosions, game_score, minutes, seconds, miliseconds);
        explosions.update();
    }

    ship.update(invaders, player_laser, lives_disp, explosions, game_score);

    if (invaders.getNumKilled() == invaders.getTotal())
        setup_wave(window, textures, invaders, player_laser, ship, explosions, wave_on);

    if (game_score >= 2500 && !life_awarded){               //Win free life after 2.500 points
        life_awarded = true;
        lives_disp.addLife();
    }

    if (game_score > 100000)                                //You can't get more than 100.000 points
        game_score = 0;
}

///It's a simple method to get text on the screen
void Game::draw_text(sf::RenderWindow &window, const std::string msg, const unsigned x, const unsigned y, sf::Color color, unsigned size){
    sf::Font font;
    font.loadFromFile(Globals::FONTS_PATH + "MunroNarrow.ttf");

    sf::Text text;
    text.setFont(font);
    text.setString(msg);
    text.setCharacterSize(size);
    text.setColor(color);
    text.setPosition(x, y);

    window.draw(text);
}

///Draw all the objects we want
void Game::draw_objects(sf::RenderWindow &window, Stars &stars, ClockDisplay &clock_disp, MenuIG &menuig, Load &load, Save &save, Info &info, Menu &menu, ScoreDisplay &score_disp, LivesDisplay &lives_disp, InvaderFormation &invaders, Spaceship &ship, PlayerLaser &playerlaser, Explosions &explosions, unsigned &wave_on){
    window.clear(Globals::BG_COLOR);                                //Window has a specific color which is declared in Globals

    stars.drawStars();

    if (Globals::GAME_STATE == Globals::States::MENU){              //Don't display anything but menu while being in state MENU
        menu.draw(window);
        window.display();
        return;
    }

    if (Globals::GAME_STATE == Globals::States::MENUIG){              //Don't display anything but menu while being in state MENU
        menuig.draw(window);
        window.display();
        return;
    }

    if (Globals::GAME_STATE == Globals::States::INFO){              //Don't display anything but info while being in state INFO
        info.draw(window);
        window.display();
        return;
    }

    if (Globals::GAME_STATE == Globals::States::LOAD){              //Don't display anything but loading info while being in state LOAD
        Game::draw_text(window, load.fileName.c_str() , (Globals::SCREEN_WIDTH / 2) - 398, 365, sf::Color::White, 64);
        load.draw(window);
        window.display();
        return;
    }

    if (Globals::GAME_STATE == Globals::States::SAVE){              //Don't display anything but saving info while being in state SAVE
        Game::draw_text(window, save.fileName.c_str() , (Globals::SCREEN_WIDTH / 2) - 398, 365, sf::Color::White, 64);
        save.draw(window);
        window.display();
        return;
    }

    clock_disp.draw(window);
    score_disp.draw(window);
    invaders.drawLasers();
    invaders.drawBonuses();
    Game::draw_player_laser(window, playerlaser);
    lives_disp.draw(window);
    explosions.draw(window);

    if (Globals::GAME_STATE != Globals::States::WAVE_SETUP){        //While state is different from WAVE_SETUP display everything
        if (Globals::GAME_STATE != Globals::States::GAME_OVER)
            window.draw(ship.getSprite());
        invaders.draw();
    }
    else                                                            //But if it is, display Invaders one by one
        draw_wave(invaders);

    if (Globals::GAME_STATE == Globals::States::GAME_OVER)          //If GAME_OVER
        handle_game_over(window, clock_disp, menu, score_disp, lives_disp, invaders, ship, playerlaser, explosions, wave_on);

    window.display();                                               //Now display the window
}

///Stop everything because you were killed
void Game::handle_player_kill(InvaderFormation &invaders, PlayerLaser &player_laser, Explosions &explosions){
    invaders.removeLasers();
    player_laser.stop1();
    player_laser.stop2();
    player_laser.reset();
    explosions.reset();
    Globals::GAME_STATE = Globals::States::PLAYER_KILLED;
}

///Set the new wave
void Game::setup_wave(sf::RenderWindow &window, Textures &textures, InvaderFormation &invaders, PlayerLaser &player_laser, Spaceship &ship, Explosions &explosions, unsigned &wave_on, bool start_game){
    Globals::GAME_STATE = Globals::States::WAVE_SETUP;

    invaders.clearLevel();

    if(wave_on == 0){
        invaders.loadLevel(window, textures, "level0");
        wave_on++;
    }
    else if(wave_on == 1){
        invaders.loadLevel(window, textures, "level1");
        wave_on++;
    }
    else if(wave_on == 2){
        invaders.loadLevel(window, textures, "level2");
        wave_on++;
    }
    else if(wave_on == 3){
        invaders.loadLevel(window, textures, "level3");
        wave_on++;
    }
    else if(wave_on == 4){
        invaders.loadLevel(window, textures, "level4");
        wave_on++;
    }
    else if(wave_on == 5){
        invaders.loadLevel(window, textures, "level5");
        wave_on++;
    }
    else if(wave_on == 6){
        invaders.loadLevel(window, textures, "level6");
        wave_on++;
    }
    else if(wave_on == 7){
        invaders.loadLevel(window, textures, "level7");
        wave_on++;
    }
    else if(wave_on == 8){
        invaders.loadLevel(window, textures, "level8");
        wave_on++;
    }
    else if(wave_on == 9){
        invaders.loadLevel(window, textures, "level9");
        wave_on++;
    }
    else{
        invaders.loadLevel(window, textures, "level10");
        wave_on = 0;
    }

    invaders.reset();
    player_laser.stop1();
    player_laser.stop2();
    ship.reset();
    explosions.reset();
}

///Draw Invaders one by one
void Game::draw_wave(InvaderFormation &invaders){
    static unsigned amount = 1;
    invaders.draw(amount);
    ++amount;

    sf::sleep(sf::milliseconds(10));

    if (amount == (invaders.getTotal() + 1)){
        amount = 1;
        Globals::GAME_STATE = Globals::States::PLAY;
    }
}

///How to handle GAME OVER?
void Game::handle_game_over(sf::RenderWindow &window, ClockDisplay &clock_disp, Menu &menu, ScoreDisplay &score_disp, LivesDisplay &lives_disp, InvaderFormation &invaders, Spaceship &ship, PlayerLaser &playerlaser, Explosions &explosions, unsigned &wave_on){
    std::string msg = "GAME OVER ";
    static unsigned char_on = 0;

    ///Let's show you how I spell LOSER, letter by letter
    std::ostringstream ss;
    for (unsigned i = 0; i <= char_on; ++i){
        ss << msg[i];
        ss << " ";
    }

    draw_text(window, ss.str(), 100, 400, sf::Color::Green, 200);

    ///After this see for 5 seconds what have you done, then I will show you menu
    if (char_on == msg.length() - 1){
        sf::sleep(sf::seconds(4));
        char_on = 0;
        goto_menu(menu, clock_disp, score_disp, lives_disp, invaders, ship, playerlaser, explosions, wave_on);
        return;
    }
    else
        ++char_on;

    sf::sleep(sf::milliseconds(300));
}

///Reset all you have already done
void Game::reset_game(Menu &menu, ClockDisplay &clock_disp, ScoreDisplay &score_disp, LivesDisplay &lives_disp, InvaderFormation &invaders, Spaceship &ship, PlayerLaser &playerlaser, Explosions &explosions, unsigned &wave_on){
    life_awarded = false;
    wave_on = 0;
    invaders.reset();
    playerlaser.stop1();
    playerlaser.stop2();
    playerlaser.reset();
    ship.reset();
    menu.reset();
    clock_disp.reset();
    score_disp.reset();
    lives_disp.reset();
    explosions.reset();
}

///Go to menu and reset all your progress
void Game::goto_menu(Menu &menu, ClockDisplay &clock_disp, ScoreDisplay &score_disp, LivesDisplay &lives_disp, InvaderFormation &invaders, Spaceship &ship, PlayerLaser &playerlaser, Explosions &explosions, unsigned &wave_on){
    reset_game(menu, clock_disp, score_disp, lives_disp, invaders, ship, playerlaser, explosions, wave_on);
    Globals::GAME_STATE = Globals::States::MENU;
    Globals::PREVIOUS_STATE = Globals::States::MENU;
}

void Game::goto_menuig(MenuIG &menuig){
    menuig.reset();
    Globals::GAME_STATE = Globals::States::MENUIG;
    Globals::PREVIOUS_STATE = Globals::States::MENUIG;
}

///Go to info
void Game::goto_info(Info &info){
    info.reset();
    Globals::GAME_STATE = Globals::States::INFO;
}

///Go to loading
void Game::goto_loading(Load &load){
    load.reset();
    Globals::GAME_STATE = Globals::States::LOAD;
}

///Go to saving
void Game::goto_saving(Save &save){
    save.reset();
    Globals::GAME_STATE = Globals::States::SAVE;
}

///State: Play game
void Game::play_game(sf::RenderWindow &window, Textures &textures, InvaderFormation &invaders, PlayerLaser &player_laser, Spaceship &ship, Explosions &explosions, unsigned &wave_on){
    setup_wave(window, textures, invaders, player_laser, ship, explosions, wave_on, true);   //Setup new wave
}
