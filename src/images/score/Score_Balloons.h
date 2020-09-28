#pragma once

namespace Images {

    #include "Score_Balloon_Sml_Green.h"
    #include "Score_Balloon_Sml_Red.h"
    #include "Score_Balloon_Sml_Yellow.h"
    #include "Score_Balloon_Sml_White.h"

    #include "Score_Balloon_Med_Green.h"
    #include "Score_Balloon_Med_Red.h"
    #include "Score_Balloon_Med_Yellow.h"
    #include "Score_Balloon_Med_White.h"

    #include "Score_Balloon_Lrg_Green.h"
    #include "Score_Balloon_Lrg_Red.h"
    #include "Score_Balloon_Lrg_Yellow.h"
    #include "Score_Balloon_Lrg_White.h"

    #include "Score_Balloon_Clear.h"
    #include "Score_Balloon_ClearStar_00.h"
    #include "Score_Balloon_ClearStar_01.h"
    #include "Score_Balloon_ClearStar_02.h"
    #include "Score_Balloon_ClearStar_03.h"
    #include "Score_Balloon_ClearStar_04.h"
    #include "Score_Balloon_ClearStar_05.h"

    const uint8_t * const ScoreBalloons_Sml[] = { 
        Score_Balloon_Sml_Green,
        Score_Balloon_Sml_Red,
        Score_Balloon_Sml_Yellow,
        Score_Balloon_Sml_White,
    };

    const uint8_t * const ScoreBalloons_Med[] = { 
        Score_Balloon_Med_Green,
        Score_Balloon_Med_Red,
        Score_Balloon_Med_Yellow,
        Score_Balloon_Med_White,
    };

    const uint8_t * const ScoreBalloons_Lrg[] = { 
        Score_Balloon_Lrg_Green,
        Score_Balloon_Lrg_Red,
        Score_Balloon_Lrg_Yellow,
        Score_Balloon_Lrg_White,
    };

    const uint8_t * const Score_Balloon_ClearStar[] = { 
        Score_Balloon_ClearStar_00,
        Score_Balloon_ClearStar_01,
        Score_Balloon_ClearStar_02,
        Score_Balloon_ClearStar_03,
        Score_Balloon_ClearStar_04,
        Score_Balloon_ClearStar_05,
    };

};