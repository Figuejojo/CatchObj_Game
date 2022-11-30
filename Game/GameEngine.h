/** @file GameEngine.h
 *  @brief Header file for the Game Engine functions used across the game files.
 *
 *  @author Y3913624
 */

#ifndef _GAMEENGINE_H_
#define _GAMEENGINE_H_

/*******************************************************************************
* Includes
*******************************************************************************/
#include "GameTypes.h"

/*******************************************************************************
* Macro Definitions
*******************************************************************************/

/*******************************************************************************
* Type definitions
*******************************************************************************/

/**
 * @name StateMachine
 * @brief State Machine for the Game Engine.
 */
typedef STATES_t (*GamePhase_t)(STATES_t*);    /**< Function Pointer to the State Machine */

typedef struct GameEngine
{
    GamePhase_t *GamePhase;
    STATES_t CurrS;
    STATES_t NextS;
    STATES_t PrevS;
}GEng_t;

/*******************************************************************************
* Function Prototypes
*******************************************************************************/

/** @brief Modify the x position of player if the left and right arrow keys or return a
  *          '\r' character if ENTER key was pressed.
  *         @TODO: Apply the keyboard functions in graphics lib.  @param [GamePhase *]
  */
void GameEngine(GamePhase_t * GPhase);


#endif // _GAMEENGINE_H_
