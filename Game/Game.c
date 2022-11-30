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

    initwindow(WIN_WIDTH, WIN_HIGH);
    initfont();
    initkeyboard();

    create_event_queue();

    reg_keyboard_events();
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

    closekeyboard();
    amio_destroy_audio();
    closegraph();
}

STATES_t GameInitWindow(STATES_t * PrevState)
{

    if(*PrevState != SELCTING_e)
    {
        amio_add_sample_instance("init", PLAY_ONCE, 0.3);
        // update audio for changes to take effect.
        amio_update_audio();
        outtextxy(WIN_HIGH/2,WIN_HIGH/2-100,"Welcome to the catch game!");
        outtextxy(WIN_HIGH/2,WIN_HIGH/2,"Press xxx to start");
        update_display();
    }
    if(check_if_event())
    {
        wait_for_event();
        if(event_close_display())
        {
            return END_e;
        }

        if(event_key_down())
        {
            *PrevState = INIT_e;
            return SELCTING_e;
        }
    }

    *PrevState = INIT_e;
    return INIT_e;
}


STATES_t GameSelWindow(STATES_t * PrevState)
{
    const char jump = 20;

    outtextxy(WIN_HIGH/2,WIN_HIGH/2-100,"Choose you character Color");
    outtextxy(WIN_HIGH/2,WIN_HIGH/2-100+jump,"r - red");
    outtextxy(WIN_HIGH/2,WIN_HIGH/2-100+jump*2,"g - red");
    outtextxy(WIN_HIGH/2,WIN_HIGH/2-100+jump*3,"b - blue");
    outtextxy(WIN_HIGH/2,WIN_HIGH/2-100+jump*4,"w - white");
    update_display();

    if(check_if_event())
    {
        wait_for_event();
        if(event_close_display())
        {
            return END_e;
        }

        if(event_key_down())
        {
            if(event_key('j'))
            {
                *PrevState = SELCTING_e;
                return PLAYGND_e;
            }
        }
    }

    *PrevState = SELCTING_e;
    return SELCTING_e;
}


STATES_t GameSRTWindow(STATES_t * PrevState)
{
}

STATES_t GameLV1Window(STATES_t * PrevState)
{
}

STATES_t GameLVFWindow(STATES_t * PrevState)
{
}

STATES_t GameRETWindow(STATES_t * PrevState)
{
}

STATES_t GamePGNWindow(STATES_t * PrevState)
{
    outtextxy(WIN_HIGH/2,WIN_HIGH/2-50,"PlayGround Testing");

    if(check_if_event())
    {
        wait_for_event();
        if(event_key_down())
        {
            if(event_key('q'))
            {
                *PrevState = PLAYGND_e;
                return END_e;
            }
        }
    }

    update_display();

    PrevState = PLAYGND_e;
    return PLAYGND_e;
}

STATES_t GameEndWindow(STATES_t * PrevState)
{
    printf("Ending\n");
    return END_e;
}
