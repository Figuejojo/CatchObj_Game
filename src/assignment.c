#include <graphics_lib.h>
#include <amio.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

void audio_once_main(void){

    amio_init_audio();

    // load a sample and give it a name.

    amio_load_sample("vocal", "./samples/vocals.wav");

    // we can choose to add an instance of the sample. We can either play it once or on a loop. Also we can change the volume (between 0 and 1).

    amio_add_sample_instance("vocal", PLAY_ONCE, 0.9);

    // update audio for changes to take effect.

    amio_update_audio();

    // audio is not affected by pausing the main thread.

    pausefor(1000);

    // we can play multiple instances of the same sample at the same time

    amio_add_sample_instance("vocal", PLAY_ONCE, 0.9);

    amio_update_audio();

    pausefor(4000);

    // Destroy audio when exiting the program.

    amio_destroy_audio();
}

void audio_loop_main(void){

    amio_init_audio();

    amio_load_sample("vocal", "./samples/vocals.wav");

    amio_add_sample_instance("vocal", PLAY_LOOP, 0.9);

    amio_update_audio();

    pausefor(5000);

    amio_destroy_audio();
}

int main(void)
{
    /* Declare two variables for the x and y positions */
    int x_position, y_position;

	/* Open a graphics window */
	/* Make it 640 pixels wide by 480 pixels high */
	initwindow(640, 480);

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

    printf("\nNow running audio_once_main\n");
    audio_once_main();

    printf("\nNow running audio_loop_main\n");
    audio_loop_main();

    /* remove the display */
    closegraph();

    return 0;
}

