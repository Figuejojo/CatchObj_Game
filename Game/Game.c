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
    if(*PrevState != BOOT_e)
    {
        amio_update_audio();
        outtextxy(WIN_HIGH/2,WIN_HIGH/2-100,"Welcome to the catch game!");
        outtextxy(WIN_HIGH/2,WIN_HIGH/2,"Press xxx to start");
        update_display();
    }
    else
    {
        amio_add_sample_instance("init", PLAY_ONCE, 0.3);
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
                StickMan_t Player;
                Player.color = CYAN;

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
    outtextxy(0,0,"PlayGround Testing");

    setcolor(LIGHTGRAY);
    line(0,GND,WIN_WIDTH,GND,3);

    update_display();

    if(check_if_event())
    {
        wait_for_event();
        if(event_close_display())
        {
            *PrevState = PLAYGND_e;
            return END_e;
        }
        if(event_key_down())
        {
            if(event_key('q'))
            {
                *PrevState = PLAYGND_e;
                return END_e;
            }
        }
    }

    *PrevState = PLAYGND_e;
    return PLAYGND_e;
}

STATES_t GameEndWindow(STATES_t * PrevState)
{
    switch(*PrevState)
    {
        case INIT_e:
            dprintf("Ending from Init\n");
            break;
        case SELCTING_e:
            dprintf("Ending from Colour Select\n");
            break;
        case PLAYGND_e:
            dprintf("Ending from Playground");
            break;
        default:
            dprintf("Ended from ??");
            break;
    }
    return END_e;
}
