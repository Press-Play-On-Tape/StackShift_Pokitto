#pragma once

#include "ppot/PPOT.h"
#include "score/Score_Balloons.h"
#include "tapes/Tapes.h"
#include "shapes/Shapes.h"

namespace Images {
    
    #include "title/Title.h"
    #include "title/Title_00.h"
    #include "title/Title_01.h"
    #include "title/Title_02.h"
    #include "title/Title_03.h"
    #include "Background.h"
    #include "GameOver.h"
    #include "HighScore.h"
    #include "HS_Highlight.h"

    #include "game/Score.h"
    #include "game/HiScore.h"
    #include "game/Easy.h"
    #include "game/Hard.h"

    #include "game/Score_Grey.h"
    #include "game/HiScore_Grey.h"
    #include "game/Easy_Grey.h"
    #include "game/Hard_Grey.h"
    #include "game/PausePlay.h"

    #include "Wave_Top_00.h"
    #include "Wave_Top_01.h"
    #include "Wave_Top_02.h"
    #include "Wave_Top_03.h"

    #include "Wave_Bot_00.h"
    #include "Wave_Bot_01.h"
    #include "Wave_Bot_02.h"
    #include "Wave_Bot_03.h"

    const uint8_t * const Title_Anim[4] = { 
        Title_00, Title_01, Title_02, Title_03
    };

    const uint8_t * const Wave_Top[4] = { 
        Wave_Top_00, Wave_Top_01, Wave_Top_02, Wave_Top_03
    };

    const uint8_t * const Wave_Bot[4] = { 
        Wave_Bot_00, Wave_Bot_01, Wave_Bot_02, Wave_Bot_03
    };

};