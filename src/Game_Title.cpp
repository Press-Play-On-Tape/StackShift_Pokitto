#include "Game.h"
#include "Pokitto.h"
#include "images/images.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

float wave_y=-50;
float tt = PC::frameCount;;
float wave_sync = 0.37;


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::doTitle() { 

    if (this->splashScreenVariables.buttonCounter == 0 && PC::buttons.pressed(BTN_LEFT) && this->titleCursor > 0) {

        this->titleCursor--;

    }

    if (this->splashScreenVariables.buttonCounter == 0 && PC::buttons.pressed(BTN_RIGHT) && this->titleCursor  < 3) {

        this->titleCursor++;

    }


    if (this->splashScreenVariables.buttonCounter > 0 ? false : (PC::buttons.pressed(BTN_A) || PC::buttons.pressed(BTN_B))) {

        switch (this->titleCursor) {

            case 0:
                this->level = Level::Easy;
                this->gameState = GameState::Play_Init;
                break;

            case 1:
                this->level = Level::Hard;
                this->gameState = GameState::Play_Init;
                break;

            case 2:
                this->cookie->setScoreIndex(NO_SCORE);
                this->gameState = GameState::HighScore_Init;
                break;

            case 3:
                this->cookie->sfx++;
                this->cookie->saveCookie();
                break;

        }
                            

    }
   

//    if (Utils::isFrameCount(46)) this->launchHighScoreParticles();

    draw_waves();

    PD::drawBitmap(1, 30, Images::Title);


    PD::drawBitmap(98, 30, Images::Title_Anim[(PC::frameCount / 2) % 4]);

    PD::setColor(this->titleCursor == 0 ? 7 : 5, 0);
    PD::setCursor(12, 140);
    PD::print("EASY");

    PD::setColor(this->titleCursor == 1 ? 7 : 5, 0);
    PD::setCursor(58, 140);
    PD::print("HARD");

    PD::setColor(this->titleCursor == 2 ? 7 : 5, 0);
    PD::setCursor(105, 140);
    PD::print("SCORES");

    PD::setColor(this->titleCursor == 3 ? 7 : 5, 0);

    switch (this->cookie->sfx) {

        case SoundEffects::Music:
            PD::setCursor(166, 140);
            PD::print("MUSIC");
            break;

        case SoundEffects::SFX:
            PD::setCursor(174, 140);
            PD::print("SFX");
            break;

        case SoundEffects::Both:
            PD::setCursor(170, 140);
            PD::print("BOTH");
            break;

        default:
            PD::setCursor(170, 140);
            PD::print("NONE");
            break;
    }

    constexpr uint8_t xPos[] = { 26, 71, 127, 184 };
    PD::drawBitmap(xPos[this->titleCursor], 128, Images::Symbols[static_cast<uint8_t>(BoardType::Existing_Red)][0]);

    //this->renderParticles();

}

#define TOP_OFFSET -6
#define BOT_OFFSET 6

void Game::draw_waves() {

//    float amp = 6 * sin(wave_sync + (static_cast<float>(PC::frameCount)/static_cast<float>(48)));
    float amp = 6 * sin(static_cast<float>(PC::frameCount)/static_cast<float>(48));

    for (uint8_t x= 0; x<220; x = x + 2) {

        float tt = static_cast<float>(x) / static_cast<float>(32) + (PC::frameCount / 2);

        uint8_t largeColourHeight = static_cast<uint8_t>(20 + (amp*sin(0.56+tt)));
        int8_t smallColourHeight = static_cast<int8_t>(amp*sin(0.25+tt));

        PD::setColor(1, 1);
        PD::fillRect(x,0, 2, largeColourHeight + TOP_OFFSET);
        PD::fillRect(218 - x, 176 + BOT_OFFSET - largeColourHeight, 2, 176);

        PD::setColor(12, 12);
        PD::fillRect(x, largeColourHeight + TOP_OFFSET, 2, smallColourHeight);
        PD::fillRect(218 - x, 176 + BOT_OFFSET - largeColourHeight - smallColourHeight, 2, smallColourHeight);

    }

}
