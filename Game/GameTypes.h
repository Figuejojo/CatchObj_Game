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
#include <time.h>

/*******************************************************************************
* Macro Definitions
*******************************************************************************/
/*! Version */
#define GAME_VERSION     (1)    ///< A - Game Release version
#define GAME_SUB_VERSION (0)    ///< B - Game Feature implementations
#define GAME_WIP_VERSION (2)    ///< C - Minor changes or BugFixes

/*! Macro Flags*/
#if defined(_DEBUG)             ///!< Macro enabled in with the debug_asssignment build target

#define ASSERT assert           ///< Re-definition for the assertions
#define dprintf printf          ///< Re-definition for the printf

#else
#define ASSERT  //              ///< Redefinition for disabling the ASSERT
#define dprintf //              ///< Redefinition for disabling the dprintf
#endif // _DEBUG

/*! Macro Functions*/
#define DEG2RAD(x) (x*PI/180)   ///< Macro Function for Converting between Degrees and Radians

/*! Game Definitions*/
#define ATTEMPTS (10)           ///< Player Attempts or Lives
#define DT       (0.05f)        ///< Delta Time used for the parabola equations
#define GRAV     (9.81)         ///< Gravity Used for the parabola equations.
#define LVLS     (5)            ///< In game levels. (Must match with the Game.c prototypes)

/*! Game Definitions */
#define WIN_WIDTH (800)         ///< Windows Width
#define WIN_HIGH  (600)         ///< Windows High
#define GND       (500)         ///< Floor for the player to stand on
#define SPACE     (20)          ///< Space used between text lines

/*! Player Definitions */
#define IPosX     (WIN_WIDTH/2) ///< Player Initial Position in X axis
#define IPosY     (GND)         ///< Player Initial Position in Y axis
#define HeadY     (GND-100)     ///< Player head position in Y axis
#define HeadR     (15)          ///< Head radius
#define BodyY1    (HeadY+HeadR) ///< Position 1 in the Y axis for the Body
#define BodyY2    (BodyY1+60)   ///< Position 2 in the Y axis for the Body

#define LEGY1     (BodyY2)      ///< Leg1 end position in y axis
#define LEGY2     (GND)         ///< Leg2 end position in y axis
#define LEGX1     (-15)         ///< Leg1 end position in x axis
#define LEGX2     (+15)         ///< Leg2 end position in w axis

#define ArmY1     (BodyY1+50)   ///< Arms Position 1 for the Y axis
#define ArmY2     (ArmY1-30)    ///< Amrs Position 2 for the Y axis
#define ARM1X     (-15)         ///< Amr1 X axis position
#define ARM2X     (+15)         ///< Amr2 X axis position

#define HANDRANGE (30)          ///< Hand Range for catching objects (x position)

/*! Cannon */
#define CANY (150)              ///< Cannon size in the y axis
#define CANR (30)               ///< Cannon radius


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
    INIT_e          =  0,     /*!< This is the Initial State        */
    SELCTING_e          ,     /*!< This is the Selecting State      */
    STARTING_e          ,     /*!< This is the Starting State       */

    LEVEL1_e            ,     /*!< This is the State for Level 1        */
    LEVEL2_e            ,     /*!< This is the State for Level 2        */
    LEVEL3_e            ,     /*!< This is the State for Level 3        */
    LEVEL4_e            ,     /*!< This is the State for Level 4        */
    LEVELF_e            ,     /*!< This is the State for the Final Level*/

    ENL_e = LEVELF_e + 1,     /*!< This is the Retry State with value of 50         */
    ENF_e               ,     /*!< This is the Final State if the game was completed*/
    PLAYGND_e           ,     /*!< This is the Playground State with value of 250   */
    END_e               ,     /*!< This is the END State with value of 51           */
/*@}*/
}STATES_t;

/*! This struct class named StickMan_t contains the player details */
typedef struct player
{
/*@{*/
    int color;  /*!< This variable saves the character colour               */
    int Score;  /*!< This variable saves the player score                   */
    int lives;  /*!< This variable saves the player attempts left           */
    int move_x; /*!< This variable saves the move position of the character */
/*@}*/
}StickMan_t;


/*! This struct class named Projectile contains the objects information     */
typedef struct projectile
{
/*@{*/
    int   cannion; /*!< This variable indicates if the obj was shoot from R or L cannon */
    float Pos_x;   /*!< This variable saves Current Position in X of the Projectile     */
    float Pos_y;   /*!< This variable saves Current Position in Y of the Projectile     */
    float vel;     /*!< This is the total Projectile velocity                           */
    float angle;   /*!< This variable saves the angle of the shooting Projectile        */
/*@}*/
}proj_t;

#endif // _GAMETYPES_H_
