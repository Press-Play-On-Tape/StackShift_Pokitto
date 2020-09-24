#include "Game.h"
#include "images/Images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

constexpr const static uint8_t UPLOAD_DELAY = 16;

int16_t xCass = 0;
int16_t yCass = 0;

// ----------------------------------------------------------------------------
//  Initialise state ..
//
void Game::doPause_Init() {
	
    this->gameState = GameState::Pause;
    this->cursor = this->cookie->track;

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::doPause() {
	
    if (xCass == 0) {

        if (PC::buttons.pressed(BTN_UP)) {
            if (this->cursor == 0) {
                this->cursor = 2;
            }
            else {
                this->cursor = (this->cursor - 1) % 3;
            }
        }

        if (PC::buttons.pressed(BTN_DOWN)) {
            this->cursor = (this->cursor + 1) % 3;
        }

        if (PC::buttons.pressed(BTN_C)) {
            this->gameState = GameState::Play;
        }

        if (PC::buttons.pressed(BTN_A)) {

            if (this->cookie->sfx == SoundEffects::None) {

                this->cookie->sfx = SoundEffects::Music;
                xCass = 86;
                yCass = 80 + (this->cursor * 12);

            }
            else if (this->cookie->sfx == SoundEffects::SFX) {

                this->cookie->sfx = SoundEffects::Both;
                xCass = 86;
                yCass = 80 + (this->cursor * 12);

            }
            else if (this->cookie->track != this->cursor) {

                xCass = 86;
                yCass = 80 + (this->cursor * 12);

            }

        }

    }


    if (xCass > 0) {

        if (xCass < 164) {
            xCass = xCass + 4;
        }
        // else if (xCass < 166) {
        //     xCass = xCass + 2;
        // }

        yCass = yCass - 4;

        if (yCass <= 0) {
            
            xCass = 0;

            this->cookie->track = this->cursor;
            this->cookie->saveCookie();
            this->playTheme(this->cookie->track);

        }

    }


    // ----------------------------------------------------------------------------
    //  Render the state .. 

    this->drawScore(true);
    this->drawFrame();
    this->drawTrack();

    PD::drawBitmap(90, 34, Images::Pause);


    for (uint8_t i = 0; i < 3; i++) {

        if (xCass > 0 && i == this->cursor) {

            PD::drawBitmap(xCass, yCass, Images::Tapes[this->cursor][0]);

        }
        else {

            PD::drawBitmap(80 + (this->cursor == i ? 6: 0), 80 + (i * 12), Images::Tapes[i][0]);

        }

    }

}
