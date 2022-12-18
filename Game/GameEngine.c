/** @file GameEngine.c
 *  @brief Function Implementations for the GameEngine.
 *
 *  @author Y3913624
 */

/*******************************************************************************
* Includes
*******************************************************************************/
#include "GameEngine.h"

/*******************************************************************************
* Static Global Variables
*******************************************************************************/


/*******************************************************************************
* Function Implementation
*******************************************************************************/

void GameEngine(GamePhase_t * GPhase)
{
    ASSERT(GPhase != NULL);

    dprintf("Game Engine - Debug print and ASSERTS ON\n");
    GEng_t Machine;
    StickMan_t Player1 = {0,0,WIN_WIDTH/2};
    Machine.CurrS = INIT_e;
    Machine.PrevS = BOOT_e;
    Machine.Player = &Player1;
    Machine.Object = NULL;

    do
    {
        cleardevice();

        ASSERT(Machine.CurrS >= BOOT_e && Machine.CurrS < END_e);
        ASSERT(GPhase[Machine.CurrS] != NULL);

        Machine.CurrS = GPhase[Machine.CurrS](&Machine);

    }while(Machine.CurrS != END_e);

    ASSERT(GPhase[END_e] != NULL);
    GPhase[END_e](&Machine);
}
#define DT (0.05f)
void Draw_Objects(GEng_t * GE)
{
    ASSERT(GE != NULL);
    //!@TODO: object_create();
    if(GE->Object[0].Pos_y > WIN_HIGH)
    {

        if((rand() % 2 + 1) == 2)
        {
            GE->Object->cannion = (-1);
            GE->Object[0].Pos_x = WIN_WIDTH - 10;
        }
        else
        {
            GE->Object->cannion = (+1);
            GE->Object[0].Pos_x = 10;
        }

        GE->Object[0].Pos_y = CANY;
        GE->Object[0].angle = DEG2RAD(-rand_number(0,45));//-rand() % 85);
        GE->Object[0].vel   = rand_number(10,75);//rand() % 75;

    }
    else
    {
        float VelX = GE->Object[0].vel * cos(GE->Object[0].angle);
        GE->Object[0].Pos_x += GE->Object->cannion*VelX * DT;

        float NewVelY = GE->Object[0].vel * sin((GE->Object[0].angle)) + 9.81*DT;
        GE->Object[0].Pos_y += NewVelY * DT;

        filled_circle(10,  GE->Object[0].Pos_y,    10, WHITE);
        filled_circle(GE->Object[0].Pos_x,  CANY, 10, WHITE);
        filled_circle(GE->Object[0].Pos_x,  GE->Object[0].Pos_y, 10, CYAN);

        GE->Object[0].angle = atan(NewVelY/VelX);
        GE->Object[0].vel = sqrt(pow(NewVelY,2)+pow(VelX,2));
    }
    //!@TODO: object_move();
}

void Stickman_draw(StickMan_t * Man)
{
    ASSERT(Man->color == RED || Man->color == CYAN || Man->color == GREEN || Man->color == WHITE || Man->color == BLUE);
    //Set all lines to be the indicated color.
    setcolor(Man->color);

    if(Man->move_x < 15)
    {
        Man->move_x = 15;
    }
    else if (Man->move_x > WIN_WIDTH-15)
    {
        Man->move_x = WIN_WIDTH-15;
    }
    ASSERT(Man->move_x >= 15 && Man->move_x <= WIN_WIDTH-15);

    //Face
    filled_circle(Man->move_x,    GND-80, 15, Man->color);

    //Body
    line(Man->move_x,  BodyY1,  Man->move_x,    BodyY2, 2);
    //Arms
    line(Man->move_x,   ArmY1,  Man->move_x + ARM2X,    ArmY2,  2);
    line(Man->move_x,   ArmY1,  Man->move_x + ARM1X,    ArmY2,  2);
    //Legs
    line(Man->move_x,   LEGY1,  Man->move_x + LEGX2,    LEGY2,  2);
    line(Man->move_x,   LEGY1,  Man->move_x + LEGX1,    LEGY2,  2);
}

void Draw_BackGround(STATES_t * ST)
{
    char jump = 20;
    setcolor(LIGHTGRAY);
    ASSERT(ST != NULL);
    ASSERT(*ST >= INIT_e && *ST < END_e);
    switch(*ST)
    {
        case INIT_e:
            amio_update_audio();
            outtextxy(WIN_HIGH/2,WIN_HIGH/2-100,"Welcome to the catch game!");
            outtextxy(WIN_HIGH/2,WIN_HIGH/2,"Press xxx to start");
            break;

        case SELCTING_e:
            outtextxy(WIN_HIGH/2,WIN_HIGH/2-100,"Choose you character Color");
            outtextxy(WIN_HIGH/2,WIN_HIGH/2-100+jump,"r - red");
            outtextxy(WIN_HIGH/2,WIN_HIGH/2-100+jump*2,"g - green");
            outtextxy(WIN_HIGH/2,WIN_HIGH/2-100+jump*3,"b - blue");
            outtextxy(WIN_HIGH/2,WIN_HIGH/2-100+jump*4,"w - white");
            break;

        case STARTING_e:
            outtextxy(WIN_WIDTH/4,0,"TO START PRESS THE S BUTTON");
            outtextxy(WIN_WIDTH/4,20,"HOW TO PLAY: ");
            outtextxy(WIN_WIDTH/4,40,"Move around using mouse");
            setcolor(LIGHTGRAY);
            line(0, GND,    WIN_WIDTH,  GND,    3);
            filled_circle(0,        CANY,   CANR,   LIGHTMAGENTA);
            filled_circle(WIN_WIDTH,CANY,   CANR,   LIGHTMAGENTA);
            break;

        case PLAYGND_e:
            outtextxy(0,0,"PlayGround Testing");
            outtextxy(0,20,"Move with arrows < >");
            outtextxy(0,40,"Return to Select with r");
            setcolor(LIGHTGRAY);
            line(0, GND,    WIN_WIDTH,  GND,    3);
            filled_circle(0,        CANY,   CANR,   LIGHTMAGENTA);
            filled_circle(WIN_WIDTH,CANY,   CANR,   LIGHTMAGENTA);
            break;
        default:
            break;
    }
}

STATES_t EventHandler(GEng_t * GE)
{
    ASSERT(GE != NULL);
    if(check_if_event())
    {
        wait_for_event();
        if(event_close_display())
        {
            GE->PrevS = GE->CurrS;
            return END_e;
        }
        else if(event_key_down())
        {
            switch(GE->CurrS)
            {
                case SELCTING_e:
                    if(event_key('j'))
                    {
                        GE->Player->color = CYAN;
                        return PLAYGND_e;
                    }
                    else if(event_key('r'))
                    {
                        GE->Player->color = RED;
                        return STARTING_e;
                    }
                    else if(event_key('g'))
                    {
                        GE->Player->color = GREEN;
                        return STARTING_e;
                    }
                    else if(event_key('b'))
                    {
                        GE->Player->color = BLUE;
                        return STARTING_e;
                    }
                    else if(event_key('w'))
                    {
                        GE->Player->color = WHITE;
                        return STARTING_e;
                    }
                    break;
                case PLAYGND_e:
                    if(event_key('q'))
                    {
                        GE->PrevS = PLAYGND_e;
                        return END_e;
                    }
                    else if(event_key('b'))
                    {
                        GE->nObjects++;
                        dprintf("%d \n",GE->nObjects);
                    }
                    break;
                case INIT_e:
                    GE->PrevS = GE->CurrS;
                    return SELCTING_e;
                    break;
                default:
                    break;
            }
        }
        else if(event_mouse_position_changed())
        {
            get_mouse_coordinates();
            GE->Player->move_x = XMOUSE;
        }
    }
    return GE->CurrS;
}
