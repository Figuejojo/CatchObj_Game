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

/*******************************************************************************
* Macro Definitions
*******************************************************************************/

/*******************************************************************************
* Type definitions
*******************************************************************************/

/**
 * @name Projectile
 * @brief Represent a Projectile
 */
 #if 0
 typedef struct Projectile
{
    /*@{*/
    double TotalVel;    /**< Magnitud of Vel Vector */
    double Angle;       /**< Angle of the Vel Vector */
    double IPos_x;      /**< Initial Position of Proyectile in Y axis */
    double IPos_y;      /**< Initial Position of Proyectile in X axis */
    /*@}*/
}Proy_t;
 #endif

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
