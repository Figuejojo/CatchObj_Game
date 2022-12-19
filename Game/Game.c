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
    amio_load_sample("init",  "./data/mixkit-magic-astral-sweep-effect-2629.wav");
    amio_load_sample("trans", "./data/mixkit-fast-small-sweep-transition-166.wav");
    amio_load_sample("shoot", "./data/mixkit-short-laser-gun-shot-1670.wav");
    amio_load_sample("lose" , "./data/mixkit-player-losing-or-failing-2042.wav");
    amio_load_sample("ctch" , "./data/mixkit-quick-positive-video-game-notification-interface-265.wav");

    GamePhase_t GamePhases[] = {GameInitWindow,
                                GameSelWindow ,
                                GameSRTWindow ,
                                GameLV1Window ,
                                GameLV2Window ,
                                GameLV3Window ,
                                GameLV4Window ,
                                GameLVFWindow ,
                                GameENLWindow ,
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

        printf("Just Once\n");
        Machine->nObjects = 0;
        Machine->Object = (proj_t*)calloc(1,sizeof(proj_t));
        Machine->Object[0].Pos_y = WIN_HIGH + 30;
        Machine->Player->lives = ATTEMPTS;
        Machine->Player->Score = 0;
    }

    Draw_BackGround(Machine);
    update_display();

    NextState = EventHandler(Machine);

    return NextState;
}

STATES_t GameSelWindow(GEng_t * Machine)
{
    ASSERT(Machine != NULL);

    if(Machine->PrevS == INIT_e)
    {
        amio_add_sample_instance("trans", PLAY_ONCE, 1);
        amio_update_audio();
    }

    Machine->PrevS = SELCTING_e;
    STATES_t NextState = SELCTING_e;

    Draw_BackGround(Machine);
    update_display();

    NextState = EventHandler(Machine);

    return NextState;
}

STATES_t GameSRTWindow(GEng_t * Machine)
{
    ASSERT(Machine != NULL);

    if(Machine->PrevS == SELCTING_e)
    {
        amio_add_sample_instance("trans", PLAY_ONCE, 1);
        amio_update_audio();
        Machine->PrevS = STARTING_e;
        Machine->nObjects = 0;
    }

    STATES_t NextState = EventHandler(Machine);

    pausefor(5);

    Draw_BackGround(Machine);
    Draw_Objects(Machine);
    Stickman_draw(Machine->Player);
    Get_Score(Machine);
    update_display();

    return NextState;
}

STATES_t GameLV1Window(GEng_t * Machine)
{
    const int elem2catch = 5;
    ASSERT(Machine != NULL);
    ASSERT(elem2catch > 0);
    ASSERT(Machine->Player->lives > 0);

    if(Machine->PrevS == STARTING_e)
    {
        Machine->nObjects = elem2catch + 1; // Number of Objects + 1
    }

    Draw_BackGround(Machine);
    Draw_Objects(Machine);
    Stickman_draw(Machine->Player);
    Get_Score(Machine);

    update_display();

    pausefor(5);

    STATES_t NextState = EventHandler(Machine);
    Machine->PrevS = LEVEL1_e;

    if(Machine->nObjects == 0)
    {
        NextState = LEVEL2_e;
    }
    if(Machine->Player->lives == 0)
    {
        NextState = ENL_e;
    }

    return NextState;
}

STATES_t GameLV2Window(GEng_t * Machine)
{
    STATES_t NextState = Machine->CurrS;

    if(Machine->PrevS == LEVEL1_e)
    {
        Machine->nObjects = 7;
        Machine->PrevS = LEVEL2_e;
    }

    Draw_BackGround(Machine);
    Draw_Objects(Machine);
    Stickman_draw(Machine->Player);
    Get_Score(Machine);
    update_display();

    NextState = EventHandler(Machine);
    pausefor(5);

    if(Machine->nObjects == 0)
    {
        NextState = LEVEL3_e;
    }
    if(Machine->Player->lives == 0)
    {
        NextState = ENL_e;
    }

    return NextState;
}

STATES_t GameLV3Window(GEng_t * Machine)
{
    STATES_t NextState = Machine->CurrS;

    if(Machine->PrevS == LEVEL2_e)
    {
        Machine->nObjects = 10;
        Machine->PrevS = LEVEL3_e;
    }

    Draw_BackGround(Machine);
    Draw_Objects(Machine);
    Stickman_draw(Machine->Player);
    Get_Score(Machine);
    update_display();

    NextState = EventHandler(Machine);
    pausefor(8);

    if(Machine->nObjects == 0)
    {
        NextState = LEVEL4_e;
    }
    if(Machine->Player->lives == 0)
    {
        NextState = ENL_e;
    }

    return NextState;
}

STATES_t GameLV4Window(GEng_t * Machine)
{
    printf("LV4\n");
    return END_e;
}

STATES_t GameLVFWindow(GEng_t * Machine)
{
    return END_e;
}

STATES_t GamePGNWindow(GEng_t * Machine)
{
    ASSERT(Machine != NULL);

    STATES_t NextState = PLAYGND_e;
    NextState = EventHandler(Machine);

    Draw_BackGround(Machine);
    Draw_Objects(Machine);
    Stickman_draw(Machine->Player);
    Get_Score(Machine);

    update_display();

    pausefor(5);

    Machine->PrevS = PLAYGND_e;
    return NextState;
}

STATES_t GameENLWindow(GEng_t * Machine)
{
    STATES_t NextState = Machine->CurrS;

    ASSERT(Machine != NULL);
    ASSERT((Machine->PrevS >= LEVEL1_e && Machine->PrevS <= LEVELF_e) || Machine->PrevS == ENL_e);

    if(Machine->PrevS >= LEVEL1_e && Machine->PrevS <= LEVELF_e)
    {
        amio_add_sample_instance("lose",PLAY_ONCE, 1);
        amio_update_audio();
        printf("Out of Lives...Score %d\n",Machine->Player->Score);
        Draw_BackGround(Machine);
        update_display();
    }

    NextState = EventHandler(Machine);
    Machine->PrevS = ENL_e;

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


        case LEVEL1_e:
        case LEVEL2_e:
        case LEVEL3_e:
            dprintf("Ending from LV");
            break;

        case ENL_e:
            dprintf("Ended from ENDL");
            break;

        default:
            dprintf("Ended from ??\n");
            break;
    }
    destroy_bitmap(Machine->Bckgnd);
    free(Machine->Object);
    return END_e;
}
