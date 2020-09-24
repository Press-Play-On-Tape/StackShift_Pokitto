#pragma once

namespace Images {

    #include "BlueTape_00.h"
    #include "BlueTape_01.h"
    #include "BlueTape_02.h"

    #include "GreenTape_00.h"
    #include "GreenTape_01.h"
    #include "GreenTape_02.h"

    #include "RedTape_00.h"
    #include "RedTape_01.h"
    #include "RedTape_02.h"

    #include "Pause.h"

    const uint8_t * const Tapes[3][3] = { 
        GreenTape_00,
        GreenTape_01,
        GreenTape_02,
        RedTape_00,
        RedTape_01,
        RedTape_02,
        BlueTape_00,
        BlueTape_01,
        BlueTape_02,
    };

};