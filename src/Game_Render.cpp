#include "Pokitto.h"
#include "Game.h"
#include "utils/Consts.h"
#include "utils/Utils.h"
#include "images/Images.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::drawScore(bool renderHeadings, bool grey) {

    if (renderHeadings) {

        switch (this->level) {

            case Level::Easy:
                if (grey) {
                    PD::drawBitmap(17, 44, Images::Easy_Grey);
                }
                else {
                    PD::drawBitmap(17, 44, Images::Easy);
                }
                break;

            case Level::Hard:
                if (grey) {
                    PD::drawBitmap(17, 44, Images::Hard_Grey);
                }
                else {
                    PD::drawBitmap(17, 44, Images::Hard);
                }
                break;

            case Level::Timer:
                if (grey) {
                    PD::drawBitmap(12, 44, Images::Timer_Grey);
                }
                else {
                    PD::drawBitmap(12, 44, Images::Timer);
                }
                break;

        }

        if (grey) {
            PD::drawBitmap(13, 83, Images::Score_Grey);
            PD::drawBitmap(151, 83, Images::HiScore_Grey);
        }
        else {
            PD::drawBitmap(13, 83, Images::Score);
            PD::drawBitmap(151, 83, Images::HiScore);
        }

    }


    PD::setColor(grey ? 5 : 7, 0);

    if (highScore > currentScore) {

        uint8_t digits[6] = {};
        Utils::extractDigits(digits, highScore);


        for (uint8_t j = 5, x2 = 162; j > 0; --j, x2 += 8) {

            PD::setCursor(x2, 122);
            PD::print(digits[j - 1], 14);

        }

        Utils::extractDigits(digits, currentScore);

        for (uint8_t j = 5, x2 = 14; j > 0; --j, x2 += 8) {

            PD::setCursor(x2, 122);
            PD::print(digits[j - 1], 10);

        }

    }
    else {

        uint8_t digits[5] = {};
        Utils::extractDigits(digits, currentScore);

        if (Utils::getFrameCountHalf(48)) {

            PD::setColor(8, 0);

            for (uint8_t j = 5, x2 = 162; j > 0; --j, x2 += 8) {

                PD::setCursor(x2, 122);
                PD::print(digits[j - 1], 14);

            }

            for (uint8_t j = 5, x2 = 14; j > 0; --j, x2 += 8) {

                PD::setCursor(x2, 122);
                PD::print(digits[j - 1], 10);

            }   

        }         

    }


    // Render Hourglass?

    if (this->level == Level::Timer && this->gameState != GameState::End) {

        uint8_t digits[5] = {};
        uint16_t target = this->currentScore - this->lastScore;
        Utils::extractDigits(digits, target);
        PD::setColor(grey ? 5 : 7, 0);

        for (uint8_t j = 3, x2 = 152; j > 0; --j, x2 += 8) {

            PD::setCursor(x2, 67);
            PD::print(digits[j - 1], 14);

        }

        PD::setCursor(178, 67);
        PD::print("/");
        PD::print("500");
        
        
        //PD::setColor(grey ? 1 : 2, 0);
        PD::setColor(0, 0);


        float gaugeWidth = 57 - static_cast<float>(57) * static_cast<float>(this->timer) / static_cast<float>(100);

        PD::drawBitmap(153, 57, grey ? Images::Gauge_Grey : Images::Gauge);

        PD::fillRect(154 + 57, 59, -gaugeWidth, 2);
        if (gaugeWidth >= 1 && gaugeWidth < 57) {
            PD::fillRect(155 + 55, 58, -gaugeWidth + 1, 4);
        }

        // if ((this->timer < 10 && (PC::frameCount / 16) % 2 == 0) || this->timer >= 10) {

        //     PD::drawBitmap(171, 44, grey ? Images::Hourglass_Grey : Images::Hourglass[this->timer_seq / 4]);
            
        //     if (grey) {
        //         PD::setColor(5, 0);
        //     }
        //     else {
        //         PD::setColor(this->timer < 10 ? 6 : 7, 0);
        //     }
            
        //     PD::setCursor(174, 68);

        //     if (this->timer < 10) PD::print("0");
        //     PD::print(this->timer, 10);

        // }

    }


}

int16_t xPos_Top = 0;
int16_t xPos_Bot = 0;

void Game::drawFrame() {

    uint8_t color = ((this->currentScore / 500) % 4) + 1;

    for (int16_t x = 0; x < 3; x++) {

        PD::drawBitmap(xPos_Top + (x * 204), 0, Images::Wave_Top[color - 1]);
        PD::drawBitmap((xPos_Bot - (x * 204)), 154, Images::Wave_Bot[color - 1]);

    } 

    xPos_Top = xPos_Top - 4;
    if (xPos_Top <= -204) xPos_Top = 0;
    xPos_Bot = xPos_Bot + 4;
    if (xPos_Bot >= 220) xPos_Bot = 16;

//    PD::drawBitmap(0, 176 -  28, Images::Background);
    

    int16_t xLeft = BOARD_X_OFFSET + this->shake.xOffset;
    int16_t yTop = this->shake.yOffset + BOARD_Y_OFFSET;
    uint8_t width = (BOARD_WIDTH * PART_SIZE) + 4;
    uint8_t height = (BOARD_HEIGHT * PART_SIZE) + 4;

    PD::setColor(0, 0);

    PD::fillRect(xLeft - 1, yTop - 1, width + 22 ,26);
    PD::fillRect(xLeft - 1, yTop + 148, width + 3 , 22);


    PD::setColor(color, 0);

    PD::drawLine(xLeft + 1, yTop, xLeft + width - 1, yTop); //Top
    PD::drawLine(xLeft + 1, yTop + height, xLeft + width - 1, yTop + height); //Bottom
    PD::drawLine(xLeft, yTop + 1, xLeft, yTop + height - 1); //Left side
    PD::drawLine(xLeft + width, yTop + 1, xLeft + width, yTop + 40); //Right side
    PD::drawLine(xLeft + width, yTop + 42, xLeft + width, yTop + height - 1); //Right side

    PD::drawLine(xLeft + width + 1, yTop, xLeft + width + 18, yTop); //Top
    PD::drawLine(xLeft + width + 19, yTop + 1, xLeft + width + 19, yTop + 40); //Side
    PD::drawLine(xLeft + width + 1, yTop + 41, xLeft + width + 18, yTop + 41); //Bottom

}


void Game::drawNextColumn() {

    for (uint8_t i = 4, y = 8; i > 1; i--, y = y + 11) {

        switch (this->launchBlocks[i]) {

            case BoardType::New_Rock:
            case BoardType::Existing_Rock:
            case BoardType::Marked_Rock:
                PD::drawBitmap(150 + this->shake.xOffset, y + this->shake.yOffset, Images::Symbols[this->getFrameNumber(this->launchBlocks[i])][2]);  
                break;

            default:
                PD::drawBitmap(150 + this->shake.xOffset, y + this->shake.yOffset, Images::Symbols[this->getFrameNumber(this->launchBlocks[i])][0]);  
                break;

        }

    }

}

void Game::drawTrack() {

    switch (this->cookie->sfx) {

        case SoundEffects::Both:
        case SoundEffects::Music:

            PD::drawBitmap(166, 2, Images::Tapes[this->cookie->track][(PC::frameCount % 48) / 16]);
            break;

        default: break;

    }

}


void Game::drawBoard() {

    for (int row = 0; row < BOARD_HEIGHT; row++) {

        for (int col = 0; col < BOARD_WIDTH; col++) {

            uint8_t x = (col * PART_SIZE) + BOARD_X_OFFSET + 3 + this->shake.xOffset;
            uint8_t y = (row * PART_SIZE) + 3 + this->shake.yOffset + BOARD_Y_OFFSET;

            switch (gameBoard[col][row]) {

                case BoardType::None:
                    break;

                default:
                    PD::drawBitmap(x , y, Images::Symbols[this->getFrameNumber(this->gameBoard[col][row])][this->gameBoard_Frames[col][row]]);  
                    break;

            }

        }

    }

}




void Game::drawDropped() {

    if (dropCount > 0) {

        dropCount--;
        PD::drawLine((dropCol * PART_SIZE) + BOARD_X_OFFSET + 6, (dropRow * PART_SIZE) + BOARD_Y_OFFSET, (dropCol * PART_SIZE) + BOARD_X_OFFSET + 6, ((dropRowSearch - 1)*PART_SIZE)  + BOARD_Y_OFFSET); //white

    }

}
