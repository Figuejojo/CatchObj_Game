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
    switch(*ST)
    {
        case PLAYGND_e:

            outtextxy(0,0,"PlayGround Testing");
            setcolor(LIGHTGRAY);
            line(0, GND,    WIN_WIDTH,  GND,    3);
            filled_circle(0,        CANY,   CANR,   LIGHTMAGENTA);
            filled_circle(WIN_WIDTH,CANY,   CANR,   LIGHTMAGENTA);

            break;

        default:
            break;
    }

}
