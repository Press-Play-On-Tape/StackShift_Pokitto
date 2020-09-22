#include "Pokitto.h"
#include "Game.h"
#include "utils/Consts.h"
#include "images/Images.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ------------------------------------------------------------
//  Is this an existing board piece?
//
bool Game::isExistingPart(uint8_t col, uint8_t row) {

    switch (this->gameBoard[col][row]) {

        case BoardType::Existing_First ... BoardType::Existing_Last:

            return true;

        default:

            return false;

    }

}


// ------------------------------------------------------------
//  Is this an existing board piece?
//
bool Game::isExistingPart(BoardType boardType) {

    switch (boardType) {

        case BoardType::Existing_First ... BoardType::Existing_Last:

            return true;

        default:

            return false;

    }

}


// ------------------------------------------------------------
//  Is this a new board piece? (ie a moving column piece)
//
bool Game::isNewPart(uint8_t col, uint8_t row) {

    switch (this->gameBoard[col][row]) {

        case BoardType::New_First ... BoardType::New_Last:

            return true;

        default:

            return false;
            
    }

}


// ------------------------------------------------------------
//  Is this a new board piece? (ie a moving column piece)
//
bool Game::isNewPart(BoardType boardType) {

    switch (boardType) {

        case BoardType::New_First ... BoardType::New_Last:

            return true;

        default:

            return false;
            
    }

}


// ------------------------------------------------------------
//  Is this a new board piece? (ie a moving column piece)
//
bool Game::isMarkedPart(uint8_t col, uint8_t row) {

    switch (this->gameBoard[col][row]) {

        case BoardType::Marked_First ... BoardType::Marked_Last:

            return true;

        default:

            return false;
            
    }

}


// ------------------------------------------------------------
//  Is this a new board piece? (ie a moving column piece)
//
bool Game::isMarkedPart(BoardType boardType) {

    switch (boardType) {

        case BoardType::Marked_First ... BoardType::Marked_Last:

            return true;

        default:

            return false;
            
    }

}


// ------------------------------------------------------------
//  Is this an rock piece?
//
bool Game::isRockPart(uint8_t col, uint8_t row) {

    switch (this->gameBoard[col][row]) {

        case BoardType::Existing_Rock:
        case BoardType::New_Rock:
        case BoardType::Marked_Rock:

            return true;

        default:

            return false;

    }

}


// ------------------------------------------------------------
//  Is this an rock piece?
//
bool Game::isRockPart(BoardType boardType) {

    switch (boardType) {

        case BoardType::Existing_Rock:
        case BoardType::New_Rock:
        case BoardType::Marked_Rock:

            return true;

        default:

            return false;

    }

}


// ------------------------------------------------------------
//  Convert a new piece to an existing piece
//
BoardType Game::convertNewToExisting(BoardType boardType) {

    switch (boardType) {

        case BoardType::New_First ... BoardType::New_Last:

            return static_cast<BoardType>(static_cast<uint8_t>(boardType) - 4);

        default:

            return boardType;
            
    }

}



// ------------------------------------------------------------
//  Convert any piece to an existing piece
//
BoardType Game::convertAnyToExisting(BoardType boardType) {

    switch (boardType) {

        case BoardType::Marked_First ... BoardType::Marked_Last:

            return static_cast<BoardType>(static_cast<uint8_t>(boardType) - 8);

        case BoardType::New_First ... BoardType::New_Last:

            return static_cast<BoardType>(static_cast<uint8_t>(boardType) - 4);

        default:

            return boardType;
            
    }

}

// ------------------------------------------------------------
//  Convert a piece to an 'clear' block
//
BoardType Game::convertToMarkedBlock(BoardType boardType) {

    switch (boardType) {

        case BoardType::Existing_First ... BoardType::Existing_Last:

            return static_cast<BoardType>(static_cast<uint8_t>(boardType) + 8);

        case BoardType::New_First ... BoardType::New_Last:

            return static_cast<BoardType>(static_cast<uint8_t>(boardType) + 4);

        default:

            return boardType;
            
    }

}


// ------------------------------------------------------------
//  Search the board for an existing, moving column ..
//
void Game::findMovingPart(uint8_t &col, uint8_t &row) {

    for (int rowIndex = BOARD_HEIGHT - 1; rowIndex > -1; rowIndex--) {

        for (int colIndex = BOARD_WIDTH - 1; colIndex > -1; colIndex--) {

            if (this->isNewPart(colIndex, rowIndex)) {     

                col = colIndex;
                row = rowIndex;
                return;

            }

        }

    }

    col = NO_BLOCK_FOUND;
    row = NO_BLOCK_FOUND;

}


// ------------------------------------------------------------
//  Rotate the falling column downwards ..
//
void Game::rotateColumnDown() {

    uint8_t col = NO_BLOCK_FOUND;
    uint8_t row = NO_BLOCK_FOUND;
    BoardType spare = BoardType::None;
    uint8_t spare_Frames = 0;
    
    findMovingPart(col, row);

    if (col != NO_BLOCK_FOUND && row != NO_BLOCK_FOUND) {     

        spare = this->gameBoard[col][row];
        spare_Frames = this->gameBoard_Frames[col][row];

        switch (row) {

            case 0:
                this->gameBoard[col][row] = this->launchBlocks[0];
                this->gameBoard_Frames[col][row] = this->launchBlocks_Frames[0];
                this->launchBlocks[0] = this->launchBlocks[1];
                this->launchBlocks_Frames[0] = this->launchBlocks_Frames[1];
                this->launchBlocks[1] = spare;
                this->launchBlocks_Frames[1] = spare_Frames;
                break;

            case 1:
                this->gameBoard[col][row] = this->gameBoard[col][row - 1];
                this->gameBoard_Frames[col][row] = this->gameBoard_Frames[col][row - 1];
                this->gameBoard[col][row - 1] = this->launchBlocks[0];
                this->gameBoard_Frames[col][row - 1] = this->launchBlocks_Frames[0];
                this->launchBlocks[0] = spare;
                this->launchBlocks_Frames[0] = spare_Frames;
                break;

            default:
                this->gameBoard[col][row] = this->gameBoard[col][row - 1];
                this->gameBoard_Frames[col][row] = this->gameBoard_Frames[col][row - 1];
                this->gameBoard[col][row - 1] = this->gameBoard[col][row - 2];
                this->gameBoard_Frames[col][row - 1] = this->gameBoard_Frames[col][row - 2];
                this->gameBoard[col][row - 2] = spare;
                this->gameBoard_Frames[col][row - 2] = spare_Frames;
                break;


        }

    }

}


// ------------------------------------------------------------
//  Rotate the falling column upwards ..
//
void Game::rotateColumnUp() {

    uint8_t col = NO_BLOCK_FOUND;
    uint8_t row = NO_BLOCK_FOUND;
    BoardType spare = BoardType::None;
    uint8_t spare_Frames = 0;
    
    findMovingPart(col, row);

    if (col != NO_BLOCK_FOUND && row != NO_BLOCK_FOUND) {     

        switch (row) {

            case 0:
                spare = this->launchBlocks[1];
                spare_Frames = this->launchBlocks_Frames[1];
                this->launchBlocks[1] = this->launchBlocks[0];
                this->launchBlocks_Frames[1] = this->launchBlocks_Frames[0];
                this->launchBlocks[0] = this->gameBoard[col][row];
                this->launchBlocks_Frames[0] = this->gameBoard_Frames[col][row];
                this->gameBoard[col][row] = spare;
                this->gameBoard_Frames[col][row] = spare_Frames;
                break;

            case 1:
                spare = this->launchBlocks[0];
                spare_Frames = this->launchBlocks_Frames[0];
                this->launchBlocks[0] = this->gameBoard[col][row - 1];
                this->launchBlocks_Frames[0] = this->gameBoard_Frames[col][row - 1];
                this->gameBoard[col][row - 1] = this->gameBoard[col][row];
                this->gameBoard_Frames[col][row - 1] = this->gameBoard_Frames[col][row];
                this->gameBoard[col][row] = spare;
                this->gameBoard_Frames[col][row] = spare_Frames;
                break;

            default:
                spare = this->gameBoard[col][row - 2];
                spare_Frames = this->gameBoard_Frames[col][row - 2];
                this->gameBoard[col][row - 2] = this->gameBoard[col][row - 1];
                this->gameBoard_Frames[col][row - 2] = this->gameBoard_Frames[col][row - 1];
                this->gameBoard[col][row - 1] = this->gameBoard[col][row];
                this->gameBoard_Frames[col][row - 1] = this->gameBoard_Frames[col][row];
                this->gameBoard[col][row] = spare;
                this->gameBoard_Frames[col][row] = spare_Frames;
                break;


        }

    }

}


// ------------------------------------------------------------
//  Retrieve a frame number based on the board type ..
//
uint8_t Game::getFrameNumber(BoardType boardType) {

    switch (boardType) {

        case BoardType::Existing_First ... BoardType::Existing_Last:
            return static_cast<uint8_t>(boardType);

        case BoardType::New_First ... BoardType::New_Last:
            return static_cast<uint8_t>(boardType) - 4;

        case BoardType::Marked_First ... BoardType::Marked_Last:
            return static_cast<uint8_t>(boardType) - 4;

        default:
            return 255;

    }

}



// ------------------------------------------------------------
//  Retrieve a frame number based on the board type ..
//
Color Game::getColor(BoardType boardType) {

    switch (boardType) {

        case BoardType::Existing_First ... BoardType::Existing_Last:
            return static_cast<Color>(static_cast<uint8_t>(boardType));

        case BoardType::New_First ... BoardType::New_Last:
            return static_cast<Color>(static_cast<uint8_t>(boardType) - 4);
 
        case BoardType::Marked_First ... BoardType::Marked_Last:
            return static_cast<Color>(static_cast<uint8_t>(boardType) - 8);

        default:
            return Color::White;
 
    }

}


void Game::playSoundEffect(SoundTheme theme) {

    char sounds[4][19] = { "music/Stack_01.raw", "music/Stack_02.raw", 
                           "music/Stack_03.raw", "music/Stack_04.raw" };

    switch (this->cookie->sfx) {

        case SoundEffects::SFX:
        case SoundEffects::Both:

            if (soundEffectFile.openRO(sounds[static_cast<uint8_t>(theme)])) {

                auto& music = Audio::play<1>(soundEffectFile);
                music.setLoop(false);

            }

            break;

        default: break;
        
    }

}


void Game::playTheme() {

    char themes[1][19] = { "music/Stack_05.raw" };

    switch (this->cookie->sfx) {

        case SoundEffects::Music:
        case SoundEffects::Both:

            if (mainThemeFile.openRO(themes[0])) {
                auto& music = Audio::play<0>(mainThemeFile);
                music.setLoop(true);
            }

            break;

        default: break;

    }

}


BoardType Game::getRandomBoardType(Level level, uint8_t rock) {

    if (level == Level::Hard) {

        if (rock > 0 && random(0, rock) == 0) {

            return BoardType::New_Rock;

        }
        else {

            return static_cast<BoardType>(random(static_cast<uint8_t>(BoardType::New_First), static_cast<uint8_t>(BoardType::New_Last)));
            
        }

    }
    else {

        return static_cast<BoardType>(random(static_cast<uint8_t>(BoardType::New_First), static_cast<uint8_t>(BoardType::New_Yellow) + 1));

    }

}