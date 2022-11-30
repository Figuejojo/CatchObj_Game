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

/*! This is an enum class */
typedef enum
{
/*@{*/
    INIT_e      = 0,     /*!< This is the Initial State with value of 0     */
    SELCTING_e,          /*!< This is the Selecting State with value of 1   */
    STARTING_e,          /*!< This is the Starting State with value of 2    */

    LEVEL_1     = 10,    /*!< This is the Level 1 State with value of 2     */
    LEVEL_F,             /*!< This is the Final Level State with value of 2 */

    RETRY_e     = 50,    /*!< This is the Retry State with value of 50      */
    END_e,               /*!< This is the END State with value of 51        */
    PLAYGND_e   = 250,   /*!< This is the Playground State with value of 250*/
/*@}*/
}STATES_t;

/**
 * @name StateMachine
 * @brief State Machine for the Game Engine.
 */
 typedef struct StateMachine
{
    /*@{*/
    void (*funct)(void * args);    /**< Function Pointer to the State Machine */
    STATES_t CurrState;       /**< Current State ENUM    */
    STATES_t NextState;       /**< Next State ENUM       */
    STATES_t PrevState;       /**< Prev State ENUM       */
    /*@}*/
}Engine_t;

/*******************************************************************************
* Function Prototypes
*******************************************************************************/

/** @brief Core Game function.
 */
void GameEngine_Init(void);

/** @brief Modify the x position of player if the left and right arrow keys or return a
 *          '\r' character if ENTER key was pressed.
 *         @TODO: Apply the keyboard functions in graphics lib.
 *
 *  @param [int Ptr] From Player struct we pass only the move_x.
 *
 *  @return Return '\r' if the ENTER key was pressed.
 */
//int getCMD(int * move_x);

#endif // _GAMEENGINE_H_
