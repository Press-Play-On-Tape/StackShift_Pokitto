#include "Pokitto.h"
#include "Game.h"
#include "images/Images.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::setup(GameCookie *cookie) {

	this->cookie = cookie;

}


void Game::loop(){

    PD::clear();
    PC::buttons.pollButtons();


    // Decrement hourglass and timer if required ..

    if (this->level == Level::Timer && this->gameState == GameState::Play) {

        if (this->timer_seq > 0) this->timer_seq--;

        this->timer_counter--;

        if (this->timer_counter == 0) {

            this->timer--;
            this->timer_counter = 22 - (currentScore / 1000);

            if (this->timer == 0) {

                this->gameState = GameState::End;

            }

        }


        // If we have passed a 500 mark, reset the timer ..

        if (this->currentScore >= this->lastScore + 500) {

            this->timer_seq = 15;
            this->timer = 99;
            this->lastScore = this->lastScore + 500;
            this->playSoundEffect(SoundTheme::Timer);

        }

    }



    // == Camera Shake Department ===

    if (this->shake.count > 0) {

        this->shake.count--;

        switch (this->shake.explosionSize) {

            case ExplosionSize::Small:
                this->shake.yOffset = random(-1, 2);
                this->shake.xOffset = 0;
                break;

            case ExplosionSize::Medium:
                this->shake.yOffset = random(-1, 2);
                this->shake.xOffset = random(-1, 2);
                break;

            case ExplosionSize::Large:
                this->shake.xOffset = random(-2, 3);
                this->shake.yOffset = random(-2, 3);
                break;

        }

    }
    else {

        this->shake.explosionSize = ExplosionSize::None;
        this->shake.yOffset = 0;
        this->shake.xOffset = 0;

    }


    // Game state ..

    switch (this->gameState) {

        case GameState::SplashScreen:

            this->doSplashScreen(); 
            break;

        case GameState::Title:

            this->doTitle(); 
            break;

        case GameState::Play_Init:
            this->resetGame();
            this->playTheme(this->cookie->track);
            [[fallthrough]]

        case GameState::Play:


            // Update game speed ..

            #define GAME_SPEED_INC_HARD 800
            #define GAME_SPEED_INC_EASY 1600

            switch (this->level) {

                case Level::Easy:
                    gameSpeed = (currentScore - (this->clearDecks * 500) < (GAME_SPEED_INC_EASY * 6) ? 28 - ((currentScore - (this->clearDecks * 500) / GAME_SPEED_INC_EASY) * 4) : 4);
                    break;

                case Level::Hard:
                case Level::Timer:
                    gameSpeed = (currentScore - (this->clearDecks * 500) < (GAME_SPEED_INC_HARD * 6) ? 28 - ((currentScore - (this->clearDecks * 500) / GAME_SPEED_INC_HARD) * 4) : 4);
                    break;

            }

            drawDropped();


            if (this->scoringRowCount > 0) {

                this->scoringRowCount--;
                
                switch (this->scoringRowCount) {

                    case 0:
                        {
                            uint8_t col = this->launchNewColumn();

                            if (this->gameBoard[col][1] != BoardType::None) {

                                this->gameBoard[col][0] = this->convertNewToExisting(this->gameBoard[col][0]);
                                partStopped(col, 0);
                                if (this->scoringRowCount!= SCORING_ROW_COUNT_PART_STOPPED) {
                                    this->scoringRowCount = SCORING_ROW_COUNT_SCORING_COMBO;
                                }
                                else {
                                    this->gameState = GameState::End;
                                }

                            }

                        }
                        break;

                    case SCORING_ROW_COUNT_PART_STOPPED:

                        this->clearMarkedBlocks();

                        if (markScoringRows()) {
                            this->scoringRowCount = SCORING_ROW_COUNT_SCORING_COMBO;
                        }
                        break;

                }

            }



            if (!this->moveCycle()) {

                if (cycleCount >= gameSpeed || ((PC::buttons.pressed(BTN_DOWN) || PC::buttons.repeat(BTN_DOWN, 1) && cycleCount >= 2))) {
                    this->boardCycle();
                    cycleCount = 0;
                } 
                else {
                    cycleCount++;
                }

            }

            this->drawFrame();
            this->drawScore(true, false);
            this->drawTrack();
            this->drawNextColumn();
            this->drawBoard();

            break;

        case GameState::End:
            this->doGameEnd();
            break;

        case GameState::HighScore_Init:
            Audio::stop();
            this->doHighScore_Init();
            break;

        case GameState::HighScore:
            this->doHighScore();
            break;

        case GameState::Pause_Init:
            this->doPause_Init();
            break;

        case GameState::Pause:
            this->doPause();
            break;

    }

    renderParticles();

}
