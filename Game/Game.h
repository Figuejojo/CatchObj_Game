/** @file Game.h
 *  @brief Main Gain functions to be used in the for others.
 *
 *  @author Y3913624
 */
#ifndef _GAME_H_
#define _GAME_H_

/*******************************************************************************
* Includes
*******************************************************************************/
#include "GameTypes.h"
#include "GameEngine.h"

/*******************************************************************************
* Macro Definitions
*******************************************************************************/

/*******************************************************************************
* Type definitions
*******************************************************************************/

/*******************************************************************************
* Function Prototypes
*******************************************************************************/

/** @brief Core Game function.
 */
void CatchGame_Init(void);

/** @brief Initialization window for displaying the game name and welcome the player.
 *
 *  @param PrevState ptr. This is the previous state machine State.
 *
 *  @return The next state to be executed in the state machine.
 */
STATES_t GameInitWindow(STATES_t * PrevState);

/** @brief Colour Selection function. It display the available colors for the player to
 *          choose.
 *
 *  @param PrevState ptr. This is the previous state machine State.
 *
 *  @return The next state to be executed in the state machine.
 */
STATES_t GameSelWindow(STATES_t * PrevState);

STATES_t GameSRTWindow(STATES_t * PrevState);

STATES_t GameLV1Window(STATES_t * PrevState);

STATES_t GameLVFWindow(STATES_t * PrevState);

STATES_t GameRETWindow(STATES_t * PrevState);

/** @brief Hidden playground level for the developers to test all the game elements.
 *
 *  @param PrevState ptr. This is the previous state machine State.
 *
 *  @return The next state to be executed in the state machine.
 */
STATES_t GamePGNWindow(STATES_t * PrevState);

/** @brief Last element of the State Machine. It handles the exit of the game depending
 *          of the previous state.
 *
 *  @param PrevState ptr. This is the previous state machine State.
 *
 *  @return The next state to be executed in the state machine.
 */
STATES_t GameEndWindow(STATES_t * PrevState);


#endif // _GAME_H_