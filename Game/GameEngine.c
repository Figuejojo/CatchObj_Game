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
    setcolor(Man->color);
    filled_circle(WIN_WIDTH/2,GND-80,15,Man->color);
    line(IPosX,BodyY1,IPosX,BodyY2,2);
    line(IPosX,ArmY1,Arm1X,ArmY2,2);
    line(IPosX,ArmY1,Arm2X,ArmY2,2);
    line(IPosX,LEGY1,LEGX1,LEGY2,2);
    line(IPosX,LEGY1,LEGX2,LEGY2,2);
}
