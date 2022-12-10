/** @file GameTypes.h
 *  @brief DataTpes and definitions used across the Game Files.
 *
 *  @author Y3913624
 */

#ifndef _GAMETYPES_H_
#define _GAMETYPES_H_

/*******************************************************************************
* Includes
*******************************************************************************/
#include <graphics_lib.h>
#include <amio.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <assert.h>

/*******************************************************************************
* Macro Definitions
*******************************************************************************/
#if defined(_DEBUG)
#define ASSERT assert
#define dprintf printf
#else
#define ASSERT //
#define dprintf //
#endif // _DEBUG

/*! Game Definitions */
#define WIN_WIDTH (800)
#define WIN_HIGH  (600)
#define GND       (500)

/*! Player Definitions */
#define IPosX     (WIN_WIDTH/2)
#define IPosY     (GND)
#define HeadY     (GND-100)
#define HeadR     (15)
#define BodyY1    (HeadY+HeadR)
#define BodyY2    (BodyY1+60)

#define LEGY1     (BodyY2)
#define LEGY2     (GND)
#define LEGX1     (-15)
#define LEGX2     (+15)

#define ArmY1     (BodyY1+50)
#define ArmY2     (ArmY1-30)
#define ARM1X     (-15)
#define ARM2X     (+15)

#define HANDRANGE (30)

/*! Cannon */
#define CANY (150)
#define CANR (30)


/*******************************************************************************
* Type definitions
*******************************************************************************/

/*! This enum class named STATES_t containing the GAME STATES */
typedef enum
{
/*@{*/
    ERR_e           = -3,
    DEFAULT_e       = -2,

    BOOT_e          = -1,     /*!< This is a flag used when the program is starting */
    INIT_e          =  0,     /*!< This is the Initial State with value of 0        */
    SELCTING_e          ,     /*!< This is the Selecting State with value of 1      */
    STARTING_e          ,     /*!< This is the Starting State with value of 2       */

    LEVEL1_e            ,     /*!< This is the Level 1 State with value of 2        */
    LEVELF_e            ,     /*!< This is the Final Level State with value of 2    */

    RETRY_= LEVELF_e + 1,     /*!< This is the Retry State with value of 50         */
    PLAYGND_e           ,     /*!< This is the Playground State with value of 250   */
    END_e               ,     /*!< This is the END State with value of 51           */
/*@}*/
}STATES_t;

/*! This struct class named StickMan_t contains the player details */
typedef struct player
{
/*@{*/
    int score;  /*!< This variable saves the player score                   */
    int color;  /*!< This variable saves the character colour               */
    int move_x; /*!< This variable saves the move position of the character */
/*@}*/
}StickMan_t;

#endif // _GAMETYPES_H_
