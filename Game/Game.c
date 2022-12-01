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

STATES_t GameInitWindow(GEng_t * Machine)
{
    STATES_t NextState = INIT_e;

    if(Machine->PrevS == BOOT_e)
    {
        amio_update_audio();
        amio_add_sample_instance("init", PLAY_ONCE, 0.3);
        Machine->PrevS = INIT_e;
    }

    Draw_BackGround(&Machine->CurrS);
    update_display();

    if(check_if_event())
    {
        wait_for_event();
        if(event_close_display())
        {
            NextState = END_e;
        }

        if(event_key_down())
        {
            Machine->PrevS = INIT_e;
            NextState = SELCTING_e;
        }
    }


    return NextState;
}

STATES_t GameSelWindow(GEng_t * Machine)
{
    Machine->PrevS = SELCTING_e;
    STATES_t nextstate = SELCTING_e;

    Draw_BackGround(&Machine->CurrS);
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
                Machine->Player->color = CYAN;
                nextstate = PLAYGND_e;
            }
            else if(event_key('r'))
            {
                Machine->Player->color = RED;
                nextstate = STARTING_e;
            }
            else if(event_key('g'))
            {
                Machine->Player->color = GREEN;
                nextstate = STARTING_e;
            }
            else if(event_key('b'))
            {
                Machine->Player->color = BLUE;
                nextstate = STARTING_e;
            }
            else if(event_key('w'))
            {
                Machine->Player->color = WHITE;
                nextstate = STARTING_e;
            }
        }
    }
    return nextstate;
}

STATES_t GameSRTWindow(GEng_t * Machine)
{
    STATES_t NextState = STARTING_e;

    Draw_BackGround(&Machine->CurrS);
    Stickman_draw(Machine->Player);
    update_display();
    if(check_if_event())
    {
        wait_for_event();
        if(event_close_display())
        {
            Machine->PrevS = PLAYGND_e;
            NextState = END_e;
        }
        else
        {
            if(event_key_down())
            {
                if(event_key('q'))
                {
                    Machine->PrevS = STARTING_e;
                    NextState = END_e;
                }
            }
            else if (event_key_right_arrow())
            {
                Machine->Player->move_x++;
            }
            else if(event_key_left_arrow())
            {
                Machine->Player->move_x--;
            }
        }
    }

    return NextState;
}

STATES_t GameLV1Window(GEng_t * Machine)
{
}

STATES_t GameLVFWindow(GEng_t * Machine)
{
}

STATES_t GameRETWindow(GEng_t * Machine)
{
}

STATES_t GamePGNWindow(GEng_t * Machine)
{
    STATES_t NextState = PLAYGND_e;
    Draw_BackGround(&Machine->CurrS);
    Stickman_draw(Machine->Player);

    update_display();

    if(check_if_event())
    {
        wait_for_event();
        if(event_close_display())
        {
            Machine->PrevS = PLAYGND_e;
            NextState = END_e;
        }
        else
        {
            if(event_key_down())
            {
                if(event_key('q'))
                {
                    Machine->PrevS = PLAYGND_e;
                    NextState = END_e;
                }
                else if(event_key('r')) //Todo: Only for debug (Delete this transition after)
                {
                    Machine->PrevS = INIT_e; //Might produce a bug
                    NextState = SELCTING_e;
                }
            }
            else if (event_key_right_arrow())
            {
                Machine->Player->move_x++;
            }
            else if(event_key_left_arrow())
            {
                Machine->Player->move_x--;
            }
        }

    }

    Machine->PrevS = PLAYGND_e;
    return NextState;
}

STATES_t GameEndWindow(GEng_t * Machine)
{
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
