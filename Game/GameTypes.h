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

/*! Macro Functions*/
#define DEG2RAD(x) (x*PI/180)   ///< Macro Function for Converting between Degrees and Radians

/*! Game Definitions*/
#define ATTEMPTS (800)
#define DT       (0.05f)
#define GRAV     (9.81)
#define LVLS     (5)

/*! Game Definitions */
#define WIN_WIDTH (800)
#define WIN_HIGH  (600)
#define GND       (500)
#define SPACE     (20)

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
    INIT_e          =  0,     /*!< This is the Initial State        */
    SELCTING_e          ,     /*!< This is the Selecting State      */
    STARTING_e          ,     /*!< This is the Starting State       */

    LEVEL1_e            ,     /*!< This is the State for Level 1        */
    LEVEL2_e            ,     /*!< This is the State for Level 2        */
    LEVEL3_e            ,     /*!< This is the State for Level 3        */
    LEVEL4_e            ,     /*!< This is the State for Level 4        */
    LEVELF_e            ,     /*!< This is the State for the Final Level*/

    ENL_e = LEVELF_e + 1,     /*!< This is the Retry State with value of 50         */
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
