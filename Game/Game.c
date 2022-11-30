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
    GamePhase_t GamePhases[] = {{GameInitWindow},
                                {GameSelWindow },
                                {GameEndWindow }
                               };
    GameEngine(&GamePhases);

}

STATES_t GameInitWindow(STATES_t * PrevState)
{
    printf("Press a any key\n");
    getch();

    PrevState = INIT_e;
    return SELCTING_e;
}


STATES_t GameSelWindow(STATES_t * PrevState)
{
    printf("Select: r,g,b,w\n");
    getch();

    PrevState = SELCTING_e;
    return END_e;
}

STATES_t GameEndWindow(STATES_t * PrevState)
{
    printf("Ending\n");
    return END_e;
}
