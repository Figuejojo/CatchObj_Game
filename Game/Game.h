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
 *  @param GEng_t ptr. This has the game info.
 *
 *  @return The next state to be executed in the state machine.
 */
STATES_t GameInitWindow(GEng_t * Machine);

/** @brief Colour Selection function. It display the available colors for the player to
 *          choose.
 *
 *  @param GEng_t ptr. This has the game info.
 *
 *  @return The next state to be executed in the state machine.
 */
STATES_t GameSelWindow(GEng_t * Machine);

/** @brief Starting State previous to the main game levels, where the player can get use to
 *          the movements.
 *
 *  @param GEng_t ptr. This has the game info.
 *
 *  @return The next state to be executed in the state machine.
 */
STATES_t GameSRTWindow(GEng_t * Machine);

STATES_t GameLV1Window(GEng_t * Machine);

STATES_t GameLVFWindow(GEng_t * Machine);


STATES_t GameENLWindow(GEng_t * Machine);

/** @brief Hidden playground level for the developers to test all the game elements.
 *
 *  @param GEng_t ptr. This has the game info.
 *
 *  @return The next state to be executed in the state machine.
 */
STATES_t GamePGNWindow(GEng_t * Machine);

/** @brief Last element of the State Machine. It handles the exit of the game depending
 *          of the previous state.
 *
 *  @param GEng_t ptr. This has the game info.
 *
 *  @return The next state to be executed in the state machine.
 */
STATES_t GameEndWindow(GEng_t * Machine);


#endif // _GAME_H_
