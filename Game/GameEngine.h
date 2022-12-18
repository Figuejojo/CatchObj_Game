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
typedef struct GameEngine
{
/*@{*/
    STATES_t CurrS;         /*!< This is the Current State to be executed       */
    STATES_t PrevS;         /*!< This is the Previous State that was executed   */
    StickMan_t * Player;    /*!< Player's Character Game Characteristics        */
    int nObjects;           /*!< Object with a random effect on the player      */
    int nBadObjects;        /*!< Object to be catch by the player to gain points*/
    proj_t * Object;        /*!< Game Objects                                   */
/*@}*/
}GEng_t;

typedef STATES_t (*GamePhase_t)(GEng_t*);    /**< Typedef of a Function Pointer to window function */

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

/** @brief Draw_Objects Function for handling the object movements and drawing.
  *
  * @param Pointer to GEng_t structure.
  */
void Draw_Objects(GEng_t * GE);

/** @brief Stickman_draw will draw the stickman depending on the movement that is passed through the
  *         parameter Man.
  *
  * @param Pointer to StickMan_t which contains the player characteristics.
  */
void Stickman_draw(StickMan_t * Man);

/** @brief Draw Background will draw the background depending on the STATE characteristics.
  *
  * @param STATES_t Is the enum type of the game engine.
  */
void Draw_BackGround(STATES_t * ST);

/** @brief EventHandler function creates a portable method for using the event functions for
  *         mouse, keyboard and display in a easy way.
  * @param STATES_t Is the enum type of the game engine.
  */
STATES_t EventHandler(GEng_t * GE);
#endif // _GAMEENGINE_H_
