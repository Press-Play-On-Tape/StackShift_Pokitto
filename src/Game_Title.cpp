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

    if (this->splashScreenVariables.buttonCounter == 0 && PC::buttons.pressed(BTN_RIGHT) && this->titleCursor  < 4) {

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
                this->level = Level::Timer;
                this->gameState = GameState::Play_Init;
                break;

            case 3:
                this->cookie->setScoreIndex(NO_SCORE);
                this->gameState = GameState::HighScore_Init;
                break;

            case 4:
                this->cookie->sfx++;
                this->cookie->saveCookie();
                break;

        }
                            

    }
   

    draw_waves();

    PD::drawBitmap(1, 30, Images::Title);
    PD::drawBitmap(98, 30, Images::Title_Anim[(PC::frameCount / 2) % 4]);
    PD::drawBitmap(6, 140, this->titleCursor == 0 ? Images::Easy_Level_White : Images::Easy_Level_Grey);
    PD::drawBitmap(46, 140, this->titleCursor == 1 ? Images::Hard_Level_White : Images::Hard_Level_Grey);
    PD::drawBitmap(86, 140, this->titleCursor == 2 ? Images::Time_White : Images::Time_Grey);
    PD::drawBitmap(132, 140, this->titleCursor == 3 ? Images::Scores_White : Images::Scores_Grey);

    switch (this->cookie->sfx) {

        case SoundEffects::Music:
            PD::drawBitmap(187, 139, this->titleCursor == 4 ? Images::Sound_Music_White: Images::Sound_Music_Grey);
            break;

        case SoundEffects::SFX:
            PD::drawBitmap(187, 139, this->titleCursor == 4 ? Images::Sound_SFX_White: Images::Sound_SFX_Grey);
            break;

        case SoundEffects::Both:
            PD::drawBitmap(187, 139, this->titleCursor == 4 ? Images::Sound_Both_White: Images::Sound_Both_Grey);
            break;

        default:
            PD::drawBitmap(187, 139, this->titleCursor == 4 ? Images::Sound_None_White: Images::Sound_None_Grey);
            break;
    }

    constexpr uint8_t xPos[] = { 16, 55, 99, 149, 198 };
    PD::drawBitmap(xPos[this->titleCursor], 128, Images::Symbols[static_cast<uint8_t>(BoardType::Existing_Red)][0]);

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
