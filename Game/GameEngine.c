/** @file GameEngine.c
 *  @brief Function Implementations for the GameEngine.
 *
 *  @author Y3913624
 */

/*******************************************************************************
* Includes
*******************************************************************************/
#include "GameEngine.h"

/*******************************************************************************
* Static Global Variables
*******************************************************************************/

/*******************************************************************************
* Function Implementation
*******************************************************************************/

void GameEngine(GamePhase_t * GPhase)
{
    ASSERT(GPhase != NULL); //Check for GPhase to be different from NULL.

    dprintf("Game Engine - Debug print and ASSERTS ON\n");
    GEng_t Machine;
    StickMan_t Player1 = {0,0,WIN_WIDTH/2};
    Machine.CurrS  = INIT_e;
    Machine.PrevS  = BOOT_e;
    Machine.Player = &Player1;
    Machine.Object = NULL;

    Machine.Bckgnd = load_bitmap("./data/rain.png");

    do  //Execution of the State Machine
    {
        cleardevice();

        ASSERT(Machine.CurrS >= BOOT_e && Machine.CurrS < END_e);   // Check for the States to exist
        ASSERT(GPhase[Machine.CurrS] != NULL);  // GamePhase pointer to current state must Exist.

        Machine.CurrS = GPhase[Machine.CurrS](&Machine);    //Execution of current state.

    }while(Machine.CurrS != END_e);

    ASSERT(GPhase[END_e] != NULL);  // Check if the end state exists.
    GPhase[END_e](&Machine);
}

void Get_Score(GEng_t * GE)
{
    ASSERT(GE != NULL); // Check for GE to not be NULL.
    ASSERT(GE->Object != NULL); //Check for Objects to not be null.
    ASSERT(GE->nTObjs > 0); // Check for the number of Thrown Objects to be greater than zero.

    for(int nObjts = 0; nObjts < GE->nTObjs; nObjts++)
    {
        // Check the Position of the Ball if its in the catch area or not.
        if( (GE->Object[nObjts].Pos_x < GE->Player->move_x + ARM2X)&&
            (GE->Object[nObjts].Pos_x > GE->Player->move_x + ARM1X)&&
            (GE->Object[nObjts].Pos_y < ArmY1)&&(GE->Object[nObjts].Pos_y > ArmY2))
        {
            //Reset Ball
            GE->Object[nObjts].Pos_y = WIN_HIGH;
            if(GE->CurrS != STARTING_e) // Check if is not the starting trial for count points.
            {
                if(nObjts == 0)
                {
                    // Cyan/Good Objects
                    amio_add_sample_instance("ctch",PLAY_ONCE,0.5);
                    amio_update_audio();
                    GE->Player->Score += GE->CurrS;
                }
                else if(nObjts == 1)
                {
                    // Red/Bad1 Objects
                    amio_add_sample_instance("bad",PLAY_ONCE,0.5);
                    amio_update_audio();
                    GE->Player->Score -= GE->CurrS;
                }
                else if(nObjts == 2)
                {
                    // White/Bad2 Objects
                    amio_add_sample_instance("bad",PLAY_ONCE,0.5);
                    amio_update_audio();
                    GE->Player->lives--;
                }
            }
            else if(GE->CurrS == STARTING_e)
            {
                // For the trial window catch sound.
                amio_add_sample_instance("ctch",PLAY_ONCE,0.5);
                amio_update_audio();
            }
        }

        if(GE->Object[nObjts].Pos_y > GND && GE->Object[nObjts].Pos_y < WIN_HIGH)
        {
            // If the ball fall to the ground.
            if(GE->CurrS != STARTING_e && nObjts == 0)
            {
                GE->Player->lives--;
            }
            //Reset the ball
            GE->Object[nObjts].Pos_y = WIN_HIGH;
        }
    }
}

void Draw_Objects(GEng_t * GE)
{
    ASSERT(GE != NULL); // Check for GE to not be NULL.
    ASSERT(GE->nTObjs > 0 );    // Check for the number of Thrown Objects to be greater than zero.
    for(int nObjts = 0; nObjts < GE->nTObjs; nObjts++)
    {
    // Iterate for the number of in game balls
        if(GE->Object[nObjts].Pos_y >= WIN_HIGH)
        {
            //Ball at starting point.
            if(GE->nObjects > 0)
            {
                if(nObjts == 0)
                {
                    GE->nObjects--;
                }

                amio_add_sample_instance("shoot",PLAY_ONCE, 1);
                amio_update_audio();

                if((rand() % 2 + 1) == 2)
                {
                    GE->Object[nObjts].cannion = (-1);
                    GE->Object[nObjts].Pos_x = WIN_WIDTH - 10;
                }
                else
                {
                    GE->Object[nObjts].cannion = (+1);
                    GE->Object[nObjts].Pos_x = 10;
                }

                GE->Object[nObjts].Pos_y = CANY;
                GE->Object[nObjts].angle = DEG2RAD(-rand_number(0,45));//-rand() % 85);
                GE->Object[nObjts].vel   = rand_number(10,70);//rand() % 75;

            }
        }
        else
        {
            //Falling motions mechanics.
            float VelX = GE->Object[nObjts].vel * cos(GE->Object[nObjts].angle);
            GE->Object[nObjts].Pos_x += GE->Object[nObjts].cannion*VelX * DT;

            float NewVelY = GE->Object[nObjts].vel * sin((GE->Object[nObjts].angle)) + GRAV*DT;
            GE->Object[nObjts].Pos_y += NewVelY * DT;
            if(nObjts == 0)
            {
                filled_circle(GE->Object[nObjts].Pos_x,  GE->Object[nObjts].Pos_y, 10, CYAN);
            }
            else if(nObjts == 1)
            {
                filled_circle(GE->Object[nObjts].Pos_x,  GE->Object[nObjts].Pos_y, 10, WHITE);
            }
            else if(nObjts == 2)
            {
                filled_circle(GE->Object[nObjts].Pos_x,  GE->Object[nObjts].Pos_y, 10, RED);
            }

            GE->Object[nObjts].angle = atan(NewVelY/VelX);
            GE->Object[nObjts].vel = sqrt(pow(NewVelY,2)+pow(VelX,2));
        }
    }
}

void Stickman_draw(StickMan_t * Man)
{
    //Check colors to be available ones.
    ASSERT(Man->color == RED || Man->color == CYAN || Man->color == GREEN || Man->color == WHITE || Man->color == BLUE);

    setcolor(Man->color);

    // Limit the movement of the stick man to only inside the game window.
    if(Man->move_x < 15)
    {
        Man->move_x = 15;
    }
    else if (Man->move_x > WIN_WIDTH-15)
    {
        Man->move_x = WIN_WIDTH-15;
    }
    ASSERT(Man->move_x >= 15 && Man->move_x <= WIN_WIDTH-15);

    //Face
    filled_circle(Man->move_x,    GND-80, 15, Man->color);

    //Body
    line(Man->move_x,  BodyY1,  Man->move_x,    BodyY2, 2);
    //Arms
    line(Man->move_x,   ArmY1,  Man->move_x + ARM2X,    ArmY2,  2);
    line(Man->move_x,   ArmY1,  Man->move_x + ARM1X,    ArmY2,  2);
    //Legs
    line(Man->move_x,   LEGY1,  Man->move_x + LEGX2,    LEGY2,  2);
    line(Man->move_x,   LEGY1,  Man->move_x + LEGX1,    LEGY2,  2);
}

void Draw_BackGround(const GEng_t * GE)
{
    char att_str[30];
    setcolor(LIGHTGRAY);
    // States must be withing the valid states.
    ASSERT(GE->CurrS >= INIT_e && GE->CurrS < END_e);
    switch(GE->CurrS)   // Each state has its own texts, and background elements.
    {
        case INIT_e:
            outtextxy(WIN_HIGH/2,WIN_HIGH/2-100,"Welcome to the catch game!");
            outtextxy(WIN_HIGH/2,WIN_HIGH/2    ,"Press any key to start");
            break;

        case SELCTING_e:
            outtextxy(WIN_HIGH/2,WIN_HIGH/2-100,"Choose you character Color");
            outtextxy(WIN_HIGH/2,WIN_HIGH/2-100+SPACE,   "r - red");
            outtextxy(WIN_HIGH/2,WIN_HIGH/2-100+SPACE*2, "g - green");
            outtextxy(WIN_HIGH/2,WIN_HIGH/2-100+SPACE*3, "b - blue");
            outtextxy(WIN_HIGH/2,WIN_HIGH/2-100+SPACE*4, "w - white");
            break;

        case STARTING_e:
            outtextxy(WIN_WIDTH/4,0,"TO START PRESS THE 'S' KEY");
            outtextxy(WIN_WIDTH/4,SPACE,"HOW TO PLAY: ");
            outtextxy(WIN_WIDTH/4,SPACE*2,"Move around using mouse");
            outtextxy(WIN_WIDTH/4,SPACE*3,"Practice shooting balls with the 'b' key ");
            outtextxy(WIN_WIDTH/4,SPACE*4,"Remember to only collect the objects with this object color");

            setcolor(LIGHTGRAY);
            line(0, GND,    WIN_WIDTH,  GND,    3);
            filled_circle(0,        CANY,   CANR,   LIGHTMAGENTA);
            filled_circle(WIN_WIDTH,CANY,   CANR,   LIGHTMAGENTA);
            break;

        case PLAYGND_e:

            outtextxy(0,0,"PlayGround Testing");
            outtextxy(0,20,"Move around using the mouse");
            outtextxy(WIN_WIDTH/4,40,"Practice shooting balls with the 'b' key ");
            sprintf(att_str,"Lives: %d/%d",ATTEMPTS, GE->Player->lives);
            outtextxy(WIN_WIDTH/4,GND+40,att_str);

            sprintf(att_str,"Score: %d",GE->Player->Score);
            outtextxy((WIN_WIDTH/4)*2,GND+40,att_str);

            draw_bitmap(GE->Bckgnd, (int)WIN_WIDTH/2, (int)WIN_HIGH/2);

            setcolor(LIGHTGRAY);
            line(0, GND,    WIN_WIDTH,  GND,    3);
            filled_circle(0,        CANY,   CANR,   LIGHTMAGENTA);
            filled_circle(WIN_WIDTH,CANY,   CANR,   LIGHTMAGENTA);
            break;

        case LEVEL1_e:
            outtextxy(WIN_WIDTH/4,0,"LEVEL 1");
            outtextxy(WIN_WIDTH/4,20,"Hazard: None");
            sprintf(att_str,"Lives: %d/%d",ATTEMPTS, GE->Player->lives);
            outtextxy(WIN_WIDTH/4,GND+40,att_str);

            sprintf(att_str,"Score: %d",GE->Player->Score);
            outtextxy((WIN_WIDTH/4)*2,GND+40,att_str);

            setcolor(LIGHTGRAY);
            line(0, GND,    WIN_WIDTH,  GND,    3);
            filled_circle(0,        CANY,   CANR,   LIGHTMAGENTA);
            filled_circle(WIN_WIDTH,CANY,   CANR,   LIGHTMAGENTA);
            break;

        case LEVEL2_e:
            draw_bitmap(GE->Bckgnd, (int)WIN_WIDTH/2, (int)WIN_HIGH/2);
            outtextxy(WIN_WIDTH/4,0,"LEVEL 2");
            outtextxy(WIN_WIDTH/4,20,"Hazard: Rain");

            sprintf(att_str,"Lives: %d/%d",ATTEMPTS, GE->Player->lives);
            outtextxy(WIN_WIDTH/4,GND+40,att_str);

            sprintf(att_str,"Score: %d",GE->Player->Score);
            outtextxy((WIN_WIDTH/4)*2,GND+40,att_str);

            setcolor(LIGHTGRAY);
            line(0, GND,    WIN_WIDTH,  GND,    3);
            filled_circle(0,        CANY,   CANR,   LIGHTMAGENTA);
            filled_circle(WIN_WIDTH,CANY,   CANR,   LIGHTMAGENTA);
            break;

        case LEVEL3_e:
            outtextxy(WIN_WIDTH/4,0,"LEVEL 3");
            outtextxy(WIN_WIDTH/4,20,"Hazard: Slippery Floor");

            sprintf(att_str,"Lives: %d/%d",ATTEMPTS, GE->Player->lives);
            outtextxy(WIN_WIDTH/4,GND+40,att_str);

            sprintf(att_str,"Score: %d",GE->Player->Score);
            outtextxy((WIN_WIDTH/4)*2,GND+40,att_str);

            setcolor(CYAN);
            line(0, GND,    WIN_WIDTH,  GND,    3);
            setcolor(LIGHTGRAY);
            filled_circle(0,        CANY,   CANR,   LIGHTMAGENTA);
            filled_circle(WIN_WIDTH,CANY,   CANR,   LIGHTMAGENTA);
            break;

        case LEVEL4_e:
            outtextxy(WIN_WIDTH/4,0,"LEVEL 4");
            outtextxy(WIN_WIDTH/4,20,"Hazard: Strange Objects");
            sprintf(att_str,"Lives: %d/%d",ATTEMPTS, GE->Player->lives);
            outtextxy(WIN_WIDTH/4,GND+40,att_str);

            sprintf(att_str,"Score: %d",GE->Player->Score);
            outtextxy((WIN_WIDTH/4)*2,GND+40,att_str);

            setcolor(LIGHTGRAY);
            line(0, GND,    WIN_WIDTH,  GND,    3);
            filled_circle(0,        CANY,   CANR,   LIGHTMAGENTA);
            filled_circle(WIN_WIDTH,CANY,   CANR,   LIGHTMAGENTA);
            break;

        case LEVELF_e:
            draw_bitmap(GE->Bckgnd, (int)WIN_WIDTH/2, (int)WIN_HIGH/2);

            outtextxy(WIN_WIDTH/4,0,"LEVEL Last");
            outtextxy(WIN_WIDTH/4,20,"Hazard: All");

            sprintf(att_str,"Lives: %d/%d",ATTEMPTS, GE->Player->lives);
            outtextxy(WIN_WIDTH/4,GND+40,att_str);

            sprintf(att_str,"Score: %d",GE->Player->Score);
            outtextxy((WIN_WIDTH/4)*2,GND+40,att_str);

            setcolor(CYAN);
            line(0, GND,    WIN_WIDTH,  GND,    3);
            setcolor(LIGHTGRAY);
            filled_circle(0,        CANY,   CANR,   LIGHTMAGENTA);
            filled_circle(WIN_WIDTH,CANY,   CANR,   LIGHTMAGENTA);
            break;

        case ENF_e:
            sprintf(att_str,"Your Score:     %d",GE->Player->Score);
            outtextxy(WIN_WIDTH/4,WIN_HIGH/4+20,att_str);
            sprintf(att_str,"Live left score: %d",GE->Player->lives*20);
            outtextxy(WIN_WIDTH/4,WIN_HIGH/4+40,att_str);

            sprintf(att_str,"Final score:    %d",GE->Player->lives*20 + GE->Player->Score);
            outtextxy(WIN_WIDTH/4,WIN_HIGH/4+60,att_str);

            outtextxy(WIN_WIDTH/4,WIN_HIGH/4+100,"THANKS FOR PLAYING");
            break;

        case ENL_e:
            outtextxy(WIN_WIDTH/4,WIN_HIGH/4,"You Ran out of lifes");
            sprintf(att_str,"Final Score: %d",GE->Player->Score);
            outtextxy(WIN_WIDTH/4,WIN_HIGH/4+20,att_str);
            outtextxy(WIN_WIDTH/4,WIN_HIGH/4+40,"THANKS FOR PLAYING");
            break;

        default:
            break;
    }
}

STATES_t EventHandler(GEng_t * GE)
{
    ASSERT(GE != NULL); // Check for GE to not be NULL.
    if(check_if_event())    // Check if any new event is taken.
    {
        wait_for_event();
        if(event_close_display())   // Close display for all states.
        {
            GE->PrevS = GE->CurrS;
            return END_e;
        }
        else if(event_key_down())   //  Check for key press.
        {
            switch(GE->CurrS)   // Validate specific keys for specific states.
            {
                case SELCTING_e:
                    if(event_key('j'))
                    {
                        GE->Player->color = CYAN;
                        return PLAYGND_e;
                    }
                    else if(event_key('r'))
                    {
                        GE->Player->color = RED;
                        return STARTING_e;
                    }
                    else if(event_key('g'))
                    {
                        GE->Player->color = GREEN;
                        return STARTING_e;
                    }
                    else if(event_key('b'))
                    {
                        GE->Player->color = BLUE;
                        return STARTING_e;
                    }
                    else if(event_key('w'))
                    {
                        GE->Player->color = WHITE;
                        return STARTING_e;
                    }
                    break;
                case PLAYGND_e:
                    if(event_key('q'))
                    {
                        GE->PrevS = PLAYGND_e;
                        return END_e;
                    }
                    else if(event_key('b'))
                    {
                        GE->nObjects++;
                    }
                    break;
                case STARTING_e:
                    if(event_key('b'))
                    {
                        GE->nObjects++;
                    }
                    else if(event_key('s'))
                    {
                        return LEVEL1_e;
                    }
                    break;
                case INIT_e:
                    GE->PrevS = GE->CurrS;
                    return SELCTING_e;
                    break;

                case LEVEL1_e:
                case LEVEL2_e:
                case LEVEL3_e:
                case LEVEL4_e:
                case LEVELF_e:
                    break;
                case ENF_e:
                case ENL_e:
                case END_e:
                    return END_e;
                    break;
                default:
                    break;
            }
        }
        else if(event_mouse_position_changed()) // Mouse change
        {
            get_mouse_coordinates();
            GE->Player->move_x = XMOUSE;
        }
    }
    return GE->CurrS;
}
