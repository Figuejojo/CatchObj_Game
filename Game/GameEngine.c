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
    dprintf("Game Engine\n");
    GEng_t Machine;
    StickMan_t Player1 = {0,0,0};
    Machine.CurrS = INIT_e;
    Machine.PrevS = BOOT_e;
    Machine.Player = &Player1;

    do
    {
        cleardevice();
        Machine.CurrS = GPhase[Machine.CurrS](&Machine);
    }while(Machine.CurrS != END_e);
    GPhase[END_e](&Machine);
}

void Stickman_draw(StickMan_t * Man)
{
    //Set all lines to be the indicated color.
    setcolor(Man->color);

    //Face
    filled_circle(WIN_WIDTH/2 + Man->move_x,    GND-80, 15, Man->color);

    //Body
    line(IPosX + Man->move_x,  BodyY1,  IPosX + Man->move_x,    BodyY2, 2);
    //Arms
    line(IPosX + Man->move_x,   ArmY1,  Arm1X + Man->move_x,    ArmY2,  2);
    line(IPosX + Man->move_x,   ArmY1,  Arm2X + Man->move_x,    ArmY2,  2);
    //Legs
    line(IPosX + Man->move_x,   LEGY1,  LEGX1 + Man->move_x,    LEGY2,  2);
    line(IPosX + Man->move_x,   LEGY1,  LEGX2 + Man->move_x,    LEGY2,  2);
}

void Draw_BackGround(STATES_t * ST)
{
    char jump = 20;
    setcolor(LIGHTGRAY);
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
            outtextxy(WIN_HIGH/2,WIN_HIGH/2-100+jump*2,"g - red");
            outtextxy(WIN_HIGH/2,WIN_HIGH/2-100+jump*3,"b - blue");
            outtextxy(WIN_HIGH/2,WIN_HIGH/2-100+jump*4,"w - white");
            break;

        case STARTING_e:
            outtextxy(WIN_WIDTH/4,0,"TO START PRESS THE S BUTTON");
            outtextxy(WIN_WIDTH/4,20,"HOW TO PLAY: ");
            outtextxy(WIN_WIDTH/4,40,"Move around using the <- and -> keys");
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
