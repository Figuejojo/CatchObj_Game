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

typedef STATES_t (*GamePhase_t)(STATES_t*);    /**< Typedef of a Function Pointer to window function */

/**
 * @name StateMachine
 * @brief State Machine for the Game Engine.
 */
typedef struct GameEngine
{
/*@{*/
    STATES_t CurrS;         /*!< This is the Current State to be executed       */
    STATES_t PrevS;         /*!< This is the Previous State that was executed   */
/*@}*/
}GEng_t;

/*******************************************************************************
* Function Prototypes
*******************************************************************************/

/** @brief GameEngine of the game. By using a state machine it can change from level to level
  *         creating a better game management throughout the different game level windows.
  *
  * @param Pointer to GamePhase_t type. This parameter points to an array of function pointer to
  *         the different function of each program window (Levels, Init windows, others).
  */
void GameEngine(GamePhase_t * GPhase);

void StickMan();
#endif // _GAMEENGINE_H_
