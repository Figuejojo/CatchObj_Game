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

/** @brief Game Level 1 function.
 *          5 balls to change level
 *          Hazards: None
 *  @param GEng_t ptr. This has the game info.
 *
 *  @return The next state to be executed in the state machine.
 */
STATES_t GameLV1Window(GEng_t * Machine);

/** @brief Game Level 2 function.
 *          7 Balls to change level.
 *          Hazards: Rain Background.
 *  @param GEng_t ptr. This has the game info.
 *
 *  @return The next state to be executed in the state machine.
 */
STATES_t GameLV2Window(GEng_t * Machine);

/** @brief Game Level 3 function.
 *          9 Balls to change level.
 *          Hazards: Mouse Delay.
 *  @param GEng_t ptr. This has the game info.
 *
 *  @return The next state to be executed in the state machine.
 */
STATES_t GameLV3Window(GEng_t * Machine);

/** @brief Game Level 4 function.
 *          13 Balls to change level.
 *          Hazards: Bad objects.
 *  @param GEng_t ptr. This has the game info.
 *
 *  @return The next state to be executed in the state machine.
 */
STATES_t GameLV4Window(GEng_t * Machine);

/** @brief Game Level 5 function.
 *          15 Balls to change level.
 *          Hazards: All.
 *  @param GEng_t ptr. This has the game info.
 *
 *  @return The next state to be executed in the state machine.
 */
STATES_t GameLVFWindow(GEng_t * Machine);

/** @brief End of Attempts.
 *
 *  @param GEng_t ptr. This has the game info.
 *
 *  @return The next state to be executed in the state machine.
 */
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
