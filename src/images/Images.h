#pragma once

#include "ppot/PPOT.h"
#include "score/Score_Balloons.h"

namespace Images {

    #include "shapes/Green_00.h"
    #include "shapes/Green_01.h"
    #include "shapes/Green_02.h"
    #include "shapes/Green_03.h"
    #include "shapes/Red_00.h"
    #include "shapes/Red_01.h"
    #include "shapes/Red_02.h"
    #include "shapes/Red_03.h"
    #include "shapes/Yellow_00.h"
    #include "shapes/Yellow_01.h"
    #include "shapes/Yellow_02.h"
    #include "shapes/Yellow_03.h"
    #include "shapes/Green_Clear_00.h"
    #include "shapes/Green_Clear_01.h"
    #include "shapes/Green_Clear_02.h"
    #include "shapes/Green_Clear_03.h"
    #include "shapes/Red_Clear_00.h"
    #include "shapes/Red_Clear_01.h"
    #include "shapes/Red_Clear_02.h"
    #include "shapes/Red_Clear_03.h"
    #include "shapes/Yellow_Clear_00.h"
    #include "shapes/Yellow_Clear_01.h"
    #include "shapes/Yellow_Clear_02.h"
    #include "shapes/Yellow_Clear_03.h"
    #include "shapes/Rock_00.h"
    #include "shapes/Rock_01.h"
    #include "shapes/Rock_02.h"
    #include "shapes/grey/Grey_Green_Clear_00.h"
    #include "shapes/grey/Grey_Green_Clear_01.h"
    #include "shapes/grey/Grey_Green_Clear_02.h"
    #include "shapes/grey/Grey_Green_Clear_03.h"
    #include "shapes/grey/Grey_Red_Clear_00.h"
    #include "shapes/grey/Grey_Red_Clear_01.h"
    #include "shapes/grey/Grey_Red_Clear_02.h"
    #include "shapes/grey/Grey_Red_Clear_03.h"
    #include "shapes/grey/Grey_Yellow_Clear_00.h"
    #include "shapes/grey/Grey_Yellow_Clear_01.h"
    #include "shapes/grey/Grey_Yellow_Clear_02.h"
    #include "shapes/grey/Grey_Yellow_Clear_03.h"
    
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


    const uint8_t * const Symbols[8][4] = { 
        { Green_00, Green_01, Green_02, Green_03 },
        { Red_00, Red_01, Red_02, Red_03 },
        { Yellow_00, Yellow_01, Yellow_02, Yellow_03 },
        { Rock_02, Rock_01, Rock_00, Rock_02 },
        { Green_Clear_00, Green_Clear_01, Green_Clear_02, Green_Clear_03 },
        { Red_Clear_00, Red_Clear_01, Red_Clear_02, Red_Clear_03 },
        { Yellow_Clear_00, Yellow_Clear_01, Yellow_Clear_02, Yellow_Clear_03 },
        { Rock_02, Rock_02, Rock_02, Rock_02 },
    };

    const uint8_t * const GreySymbols[3][4] = { 
        { Grey_Green_Clear_00, Grey_Green_Clear_01, Grey_Green_Clear_02, Grey_Green_Clear_03 },
        { Grey_Red_Clear_00, Grey_Red_Clear_01, Grey_Red_Clear_02, Grey_Red_Clear_03 },
        { Grey_Yellow_Clear_00, Grey_Yellow_Clear_01, Grey_Yellow_Clear_02, Grey_Yellow_Clear_03 },
    };

    const uint8_t * const Rocks[3] = { 
        Rock_00, Rock_01, Rock_02
    };

    const uint8_t * const Title_Anim[4] = { 
        Title_00, Title_01, Title_02, Title_03
    };

};