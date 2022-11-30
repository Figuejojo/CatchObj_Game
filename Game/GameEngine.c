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
    printf("Game Engine\n");
    GEng_t Machine;
    Machine.CurrS = INIT_e;
    Machine.PrevS = BOOT_e;

    do
    {
        printf("Eng: %d ",Machine.CurrS);
        Machine.CurrS = GPhase[Machine.CurrS](&Machine.PrevS);
    }while(Machine.CurrS != END_e);



}
