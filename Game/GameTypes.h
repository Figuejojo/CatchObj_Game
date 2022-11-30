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

/*******************************************************************************
* Macro Definitions
*******************************************************************************/
#define WIN_WIDTH (800)
#define WIN_HIGH  (600)

/*******************************************************************************
* Type definitions
*******************************************************************************/

/*! This is an enum class containing the GAME STATES */
typedef enum
{
/*@{*/
    ERR_e           = -3,
    DEFAULT_e       = -2,

    BOOT_e          = -1,
    INIT_e          =  0,     /*!< This is the Initial State with value of 0     */
    SELCTING_e          ,     /*!< This is the Selecting State with value of 1   */
    STARTING_e          ,     /*!< This is the Starting State with value of 2    */

    LEVEL1_e            ,     /*!< This is the Level 1 State with value of 2     */
    LEVELF_e            ,     /*!< This is the Final Level State with value of 2 */

    RETRY_= LEVELF_e + 1,     /*!< This is the Retry State with value of 50      */
    PLAYGND_e           ,     /*!< This is the Playground State with value of 250*/
    END_e               ,     /*!< This is the END State with value of 51        */
/*@}*/
}STATES_t;

/*******************************************************************************
* Function Prototypes
*******************************************************************************/

/** @brief Core Game function.
 */
//void Game_Init(void);

/** @brief Modify the x position of player if the left and right arrow keys or return a
 *          '\r' character if ENTER key was pressed.
 *         @TODO: Apply the keyboard functions in graphics lib.
 *
 *  @param [int Ptr] From Player struct we pass only the move_x.
 *
 *  @return Return '\r' if the ENTER key was pressed.
 */
//int getCMD(int * move_x);

#endif // _GAMETYPES_H_
