/** @file Game.c
 *  @brief Function Implementations for the Game.
 *
 *  @author Y3913624
 */

/*******************************************************************************
* Includes
*******************************************************************************/
#include "Game.h"

/*******************************************************************************
* Static Global Variables
*******************************************************************************/

/*******************************************************************************
* Function Implementation
*******************************************************************************/

void CatchGame_Init()
{
    ASSERT(WIN_WIDTH > 0 && WIN_HIGH > 0);
    initwindow(WIN_WIDTH, WIN_HIGH);
    initfont();
    initkeyboard();
    initmouse();

    create_event_queue();

    reg_keyboard_events();
    reg_mouse_events();
    reg_display_events();

    amio_init_audio();
    amio_load_sample("init", "./data/mixkit-magic-astral-sweep-effect-2629.wav");


    GamePhase_t GamePhases[] = {GameInitWindow,
                                GameSelWindow ,
                                GameSRTWindow ,
                                GameLV1Window ,
                                GameLVFWindow ,
                                GameRETWindow ,
                                GamePGNWindow ,
                                GameEndWindow ,
                               };
    GameEngine(GamePhases);

    closemouse();
    closekeyboard();
    amio_destroy_audio();
    closegraph();
}

//! @TODO: Check if any other assert is needed.
STATES_t GameInitWindow(GEng_t * Machine)
{
    STATES_t NextState = INIT_e;

    ASSERT(Machine != NULL);

    if(Machine->PrevS == BOOT_e)
    {
        amio_update_audio();
        amio_add_sample_instance("init", PLAY_ONCE, 0.3);
        Machine->PrevS = INIT_e;
    }

    Draw_BackGround(&Machine->CurrS);
    update_display();

    NextState = EventHandler(Machine);

    return NextState;
}

STATES_t GameSelWindow(GEng_t * Machine)
{
    ASSERT(Machine != NULL);

    Machine->PrevS = SELCTING_e;
    STATES_t NextState = SELCTING_e;

    Draw_BackGround(&Machine->CurrS);
    update_display();

    NextState = EventHandler(Machine);

    return NextState;
}

STATES_t GameSRTWindow(GEng_t * Machine)
{
    ASSERT(Machine != NULL);

    STATES_t NextState = STARTING_e;

    Draw_BackGround(&Machine->CurrS);
    Stickman_draw(Machine->Player);
    update_display();

    NextState = (EventHandler(Machine) == END_e)? (END_e):(NextState);

    return NextState;
}

STATES_t GameLV1Window(GEng_t * Machine)
{
    return END_e;
}

STATES_t GameLVFWindow(GEng_t * Machine)
{
    return END_e;
}

STATES_t GameRETWindow(GEng_t * Machine)
{
    return END_e;
}

STATES_t GamePGNWindow(GEng_t * Machine)
{
    ASSERT(Machine != NULL);
    STATES_t NextState = PLAYGND_e;
    Draw_BackGround(&Machine->CurrS);
    Stickman_draw(Machine->Player);
    update_display();

    pausefor(5);
    NextState = EventHandler(Machine);

    Machine->PrevS = PLAYGND_e;
    return NextState;
}

STATES_t GameEndWindow(GEng_t * Machine)
{
    ASSERT(Machine->PrevS >= INIT_e);
    switch(Machine->PrevS)
    {
        case INIT_e:
            dprintf("Ending from Init\n");
            break;
        case SELCTING_e:
            dprintf("Ending from Colour Select\n");
            break;
        case STARTING_e:
            dprintf("Ending from Starting Window\n");
            break;
        case PLAYGND_e:
            dprintf("Ending from Playground\n");
            break;
        default:
            dprintf("Ended from ??\n");
            break;
    }
    return END_e;
}
