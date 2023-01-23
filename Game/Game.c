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

    initPeripherals();      // Initialization of peripherals

    // Array of function pointers of each game window and levels.
    GamePhase_t GamePhases[] = {GameInitWindow,
                                GameSelWindow ,
                                GameSRTWindow ,
                                GameLV1Window ,
                                GameLV2Window ,
                                GameLV3Window ,
                                GameLV4Window ,
                                GameLVFWindow ,
                                GameENLWindow ,
                                GameENFWindow ,
                                GamePGNWindow ,
                                GameEndWindow ,
                               };

    srand(time(NULL));      // Random seed so the random values are not always the same sequence.

    GameEngine(GamePhases); // Game Engine and main loop.

    closePeripherals();     // Close all peripherals.

}

void initPeripherals()
{
    ASSERT(WIN_WIDTH > 0 && WIN_HIGH > 0);  //Asume that Window sizes are higher than 0;

    initwindow(WIN_WIDTH, WIN_HIGH);
    initfont();
    initkeyboard();
    initmouse();
    create_event_queue();

    reg_keyboard_events();
    reg_mouse_events();
    reg_display_events();
    hide_mouse_cursor();

    amio_init_audio();

    //Load audio files so they are ready to use.
    amio_load_sample("init",  "./data/mixkit-magic-astral-sweep-effect-2629.wav");
    amio_load_sample("trans", "./data/mixkit-fast-small-sweep-transition-166.wav");
    amio_load_sample("shoot", "./data/mixkit-short-laser-gun-shot-1670.wav");
    amio_load_sample("lose" , "./data/mixkit-player-losing-or-failing-2042.wav");
    amio_load_sample("ctch" , "./data/mixkit-quick-positive-video-game-notification-interface-265.wav");
    amio_load_sample("bad"  , "./data/mixkit-falling-hit-on-gravel-756.wav" );
    amio_load_sample("win"  , "./data/mixkit-melodic-bonus-collect-1938.wav");
}

void closePeripherals(void)
{
    //Terminates peripherals
    closemouse();
    closekeyboard();
    amio_destroy_audio();
    closegraph();
}

STATES_t GameInitWindow(GEng_t * Machine)
{
    STATES_t NextState = INIT_e;

    ASSERT(Machine != NULL); // Check Machine is not NULL .

    if(Machine->PrevS == BOOT_e)    //First run on this state
    {
        ASSERT(Machine->PrevS == BOOT_e);
        amio_add_sample_instance("init", PLAY_ONCE, 0.3);
        amio_update_audio();
        Machine->PrevS = INIT_e;

        dprintf("Just Once\n");
        Machine->nObjects = 0;
        Machine->nTObjs = 1;
        Machine->Object = (proj_t*)calloc(Machine->nTObjs,sizeof(proj_t));
        Machine->Object[0].Pos_y = WIN_HIGH + 30;
        Machine->Player->lives = ATTEMPTS;
        Machine->Player->Score = 0;
    }

    NextState = EventHandler(Machine);
    Draw_BackGround(Machine);
    update_display();
    pausefor(2);        //Wait time from one state to another.

    return NextState;   //Return to the next state or cycle to the same state.
}

STATES_t GameSelWindow(GEng_t * Machine)
{
    ASSERT(Machine != NULL);    // Check if Machine is not NULL

    if(Machine->PrevS == INIT_e)    // First run on this state.
    {
        //Play transition sound once when entering the state.
        amio_add_sample_instance("trans", PLAY_ONCE, 1);
        amio_update_audio();
    }

    Machine->PrevS = SELCTING_e;
    STATES_t NextState = SELCTING_e;

    Draw_BackGround(Machine);
    update_display();

    NextState = EventHandler(Machine);

    return NextState;   // Return the next State to be used.
}

STATES_t GameSRTWindow(GEng_t * Machine)
{
    ASSERT(Machine != NULL);    // Check if Machine is not NULL

    if(Machine->PrevS == SELCTING_e)     // First run on this state.
    {
        //Play transition sound when entering this state for the first time.
        amio_add_sample_instance("trans", PLAY_ONCE, 1);
        amio_update_audio();
        // Initialize some elements.
        Machine->PrevS = STARTING_e;
        Machine->nObjects = 0;
    }

    STATES_t NextState = EventHandler(Machine);
    Draw_BackGround(Machine);
    Draw_Objects(Machine);
    Stickman_draw(Machine->Player);
    Get_Score(Machine);
    update_display();
    pausefor(5);    //Pause the game for 5ms before next state/window.

    return NextState;   // Return the next State to be used.
}

STATES_t GameLV1Window(GEng_t * Machine)
{
    const int elem2catch = 5;
    ASSERT(Machine != NULL);    // Check if Machine is not NULL
    ASSERT(elem2catch > 0);     // Check if Elements to be catch form level 1 is greater than zero

    if(Machine->PrevS == STARTING_e)
    {
        //Play transition sound when entering this state for the first time.
        amio_add_sample_instance("trans", PLAY_ONCE, 1);
        amio_update_audio();
        ASSERT(Machine->Player->lives > 0); // Check if lives are greater than zero
        ASSERT(Machine->Player->Score == 0);// Check score being zero for the first level.
        Machine->nObjects = elem2catch + 1; // Number of Objects to be thrown is catch elements +1.
        Machine->PrevS = LEVEL1_e;
    }

    STATES_t NextState = EventHandler(Machine);
    Draw_BackGround(Machine);
    Draw_Objects(Machine);
    Stickman_draw(Machine->Player);
    Get_Score(Machine);
    update_display();
    pausefor(5);    // Pause the game for 5ms before next state/window.

    if(Machine->nObjects == 0)      // If the number of Objects to be catch is zero the next level follows.
    {
        NextState = LEVEL2_e;
    }
    if(Machine->Player->lives == 0) // If lives is zero then the next state is the End Game / Out of Lives.
    {
        NextState = ENL_e;
    }

    return NextState;   // Return the next State to be used.
}

STATES_t GameLV2Window(GEng_t * Machine)
{
    const int elem_catch = 7;
    ASSERT(Machine != NULL);    // Check if Machine is not NULL.
    ASSERT(elem_catch == 7);    // Check if Elements to be catch form level 1 is greater than zero.

    STATES_t NextState = Machine->CurrS;

    if(Machine->PrevS == LEVEL1_e)
    {
        //Play transition sound when entering this state for the first time.
        amio_add_sample_instance("trans", PLAY_ONCE, 1);
        amio_update_audio();
        ASSERT(Machine->nObjects == 0); // Check if lives are greater than zero
        ASSERT(Machine->Player->lives > 0); // Check score being zero for the first level.
        Machine->nObjects = elem_catch; // Number of Objects to be thrown is catch elements +1.
        Machine->PrevS = LEVEL2_e;
    }

    NextState = EventHandler(Machine);
    Draw_BackGround(Machine);
    Draw_Objects(Machine);
    Stickman_draw(Machine->Player);
    Get_Score(Machine);
    update_display();
    pausefor(5);    //Pause the game for 5ms before next state/window.

    if(Machine->nObjects == 0)  // If the number of Objects to be catch is zero the next level follows.
    {
        NextState = LEVEL3_e;
    }
    if(Machine->Player->lives == 0) // If lives is zero then the next state is the End Game / Out of Lives.
    {
        NextState = ENL_e;
    }

    return NextState;   // Return the next State to be used.
}

STATES_t GameLV3Window(GEng_t * Machine)
{
    const int elem_catch = 10;
    ASSERT(Machine != NULL);    // Check if Machine is not NULL.
    ASSERT(elem_catch == 10);   // Check if Elements to be catch form level 1 is greater than zero.

    STATES_t NextState = Machine->CurrS;

    if(Machine->PrevS == LEVEL2_e)
    {
        //Play transition sound when entering this state for the first time.
        amio_add_sample_instance("trans", PLAY_ONCE, 1);
        amio_update_audio();
        ASSERT(Machine->nObjects == 0); // Check if lives are greater than zero
        ASSERT(Machine->Player->lives > 0); // Check score being zero for the first level.
        Machine->nObjects = elem_catch; // Number of Objects to be thrown is catch elements +1.
        Machine->PrevS = LEVEL3_e;
    }

    NextState = EventHandler(Machine);
    Draw_BackGround(Machine);
    Draw_Objects(Machine);
    Stickman_draw(Machine->Player);
    Get_Score(Machine);
    update_display();
    pausefor(9);    //Pause the game for 9 ms before next state/window. More time creates a sense of lagging
                        // Used for the sliding effect.

    if(Machine->nObjects == 0)
    {
        NextState = LEVEL4_e;   // If the number of Objects to be catch is zero the next level follows.
    }
    if(Machine->Player->lives == 0) // If lives is zero then the next state is the End Game / Out of Lives.
    {
        NextState = ENL_e;
    }

    return NextState;   // Return the next State to be used.
}

STATES_t GameLV4Window(GEng_t * Machine)
{
    const int elem_catch = 13;
    ASSERT(Machine != NULL);    // Check if Machine is not NULL.
    ASSERT(elem_catch == 13);   // Check if Elements to be catch form level 1 is greater than zero.

    STATES_t NextState = Machine->CurrS;

    if(Machine->PrevS == LEVEL3_e)
    {
        //Play transition sound when entering this state for the first time.
        amio_add_sample_instance("trans", PLAY_ONCE, 1);
        amio_update_audio();
        ASSERT(Machine->nObjects == 0); // Check if lives are greater than zero
        ASSERT(Machine->Player->lives > 0); // Check score being zero for the first level.
        Machine->nTObjs = 3;    // Number of in-game balls.
        Machine->nObjects = elem_catch; // Number of Objects to be thrown is catch elements +1.
        Machine->PrevS = LEVEL4_e;
        Machine->Object = (proj_t*)realloc(Machine->Object ,Machine->nTObjs*sizeof(proj_t));
    }

    NextState = EventHandler(Machine);
    Draw_BackGround(Machine);
    Draw_Objects(Machine);
    Stickman_draw(Machine->Player);
    Get_Score(Machine);
    update_display();
    pausefor(5);    //Pause the game for 9 ms before next state/window.

    if(Machine->nObjects == 0)  // If the number of Objects to be catch is zero the next level follows.
    {
        NextState = LEVELF_e;
    }
    if(Machine->Player->lives == 0) // If lives is zero then the next state is the End Game / Out of Lives.
    {
        NextState = ENL_e;
    }

    return NextState;   // Return the next State to be used.
}

STATES_t GameLVFWindow(GEng_t * Machine)
{
    const int elem_catch = 15;
    ASSERT(Machine != NULL);    // Check if Machine is not NULL.
    ASSERT(elem_catch == 15);   // Check if Elements to be catch form level 1 is greater than zero.

    STATES_t NextState = Machine->CurrS;

    if(Machine->PrevS == LEVEL4_e)
    {
        //Play transition sound when entering this state for the first time.
        amio_add_sample_instance("trans", PLAY_ONCE, 1);
        amio_update_audio();
        ASSERT(Machine->nObjects == 0); // Check if lives are greater than zero
        ASSERT(Machine->Player->lives > 0); // Check score being zero for the first level.
        Machine->nTObjs = 3;    // Number of in-game balls.
        Machine->nObjects = elem_catch;  // Number of Objects to be thrown is catch elements +1.
        Machine->PrevS = LEVELF_e;
        Machine->Object = (proj_t*)realloc(Machine->Object ,Machine->nTObjs*sizeof(proj_t));
    }

    NextState = EventHandler(Machine);
    Draw_BackGround(Machine);
    Draw_Objects(Machine);
    Stickman_draw(Machine->Player);
    Get_Score(Machine);
    update_display();
    pausefor(9);    //Pause the game for 9 ms before next state/window. More time creates a sense of lagging
                        // Used for the sliding effect.

    if(Machine->nObjects == 0)  // Won is next state
    {
        dprintf("\nWOOOON\n");
        NextState = ENF_e;
    }
    if(Machine->Player->lives == 0) // If lives is zero then the next state is the End Game / Out of Lives.
    {
        NextState = ENL_e;
    }

    return NextState;   // Return the next State to be used.
}

STATES_t GamePGNWindow(GEng_t * Machine)
{
    ASSERT(Machine != NULL);    // Check if Machine is not NULL.

    STATES_t NextState = PLAYGND_e;
    NextState = EventHandler(Machine);

    Draw_BackGround(Machine);
    Draw_Objects(Machine);
    Stickman_draw(Machine->Player);
    Get_Score(Machine);

    update_display();

    pausefor(5);    //Pause the game for 9 ms before next state/window.

    Machine->PrevS = PLAYGND_e;
    return NextState;   // Return the next State to be used.
}

STATES_t GameENFWindow(GEng_t * Machine)
{
    ASSERT(Machine != NULL);    // Check if Machine is not NULL.

    STATES_t NextState = Machine->CurrS;
    ASSERT(NextState == ENF_e); //Verify if the Game has ennded correctly.

    if(Machine->PrevS == LEVELF_e)
    {
        //Play transition sound when entering this state for the first time.
        amio_add_sample_instance("init", PLAY_ONCE, 0.3);
        amio_update_audio();
        ASSERT(Machine->nObjects == 0); // Check if lives are greater than zero
        ASSERT(Machine->Player->lives > 0); // Check score being zero for the first level.
        Machine->PrevS = ENF_e;
    }

    NextState = EventHandler(Machine);

    Draw_BackGround(Machine);
    update_display();

    return NextState;   // Return the next State to be used.
}

STATES_t GameENLWindow(GEng_t * Machine)
{
    STATES_t NextState = Machine->CurrS;

    ASSERT(Machine != NULL);    // Check if Machine is not NULL.
    //End of lives can only came form another level or from itself.
    ASSERT((Machine->PrevS >= LEVEL1_e && Machine->PrevS <= LEVELF_e) || Machine->PrevS == ENL_e);

    if(Machine->PrevS >= LEVEL1_e && Machine->PrevS <= LEVELF_e)
    {
        //Play transition sound when entering this state for the first time.
        amio_add_sample_instance("lose",PLAY_ONCE, 1);
        amio_update_audio();
        dprintf("Out of Lives...Score %d\n",Machine->Player->Score);
        Draw_BackGround(Machine);
        update_display();
    }

    NextState = EventHandler(Machine);
    Machine->PrevS = ENL_e;

    return NextState;   // Return the next State to be used.
}

STATES_t GameEndWindow(GEng_t * Machine)
{
    ASSERT(Machine->PrevS >= INIT_e);   // End Game has to come from a state different than the Init state.
    switch(Machine->PrevS)  //Debug form the state it is ending.
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

        case LEVELF_e:
        case LEVEL4_e:
        case LEVEL1_e:
        case LEVEL2_e:
        case LEVEL3_e:
            dprintf("Ending from LV");
            break;
        case ENF_e:
            dprintf("Ended from ENDF");
        case ENL_e:
            dprintf("Ended from ENDL");
            break;

        default:
            dprintf("Ended from ??\n");
            break;
    }
    destroy_bitmap(Machine->Bckgnd);    // Terminate bitmap before ending.
    free(Machine->Object);              // Free dynamic allocation.
    return END_e;
}
