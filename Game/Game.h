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

/** @brief Game Initial Window.
 */
STATES_t GameInitWindow(STATES_t * PrevState);

STATES_t GameSelWindow(STATES_t * PrevState);

STATES_t GameSRTWindow(STATES_t * PrevState);

STATES_t GameLV1Window(STATES_t * PrevState);

STATES_t GameLVFWindow(STATES_t * PrevState);

STATES_t GameRETWindow(STATES_t * PrevState);

STATES_t GamePGNWindow(STATES_t * PrevState);

STATES_t GameEndWindow(STATES_t * PrevState);


#endif // _GAME_H_
