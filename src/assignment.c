#include "../Game/Game.h"


int main(void)
{
    dprintf("GameInit\n");
    CatchGame_Init();

    return 0;
}


#if 0


    /* Declare two variables for the x and y positions */
    int x_position, y_position;
    CatchGame_Init();


	/* Set up some coordinates */
	x_position = 100;
	y_position = 340;

    /* choose red pen colour */
	setcolor(RED);

    /* draw a circle on the screen buffer
     at x_position, y_position
     with radius 10 and line thickness 2 */
    circle(x_position, y_position, 10, 2);

    /* move the contents of the screen buffer to the display */
    update_display();

	/* Wait for a key press */
	printf("Press a key to continue\n");
    getch();






#endif // 0


#if 0

void audio_once_main(void){







    // audio is not affected by pausing the main thread.

    pausefor(5000);


}

#endif // 0
