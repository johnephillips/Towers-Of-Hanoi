//
// Created by John on 2017-04-23.
//

#include "Setup.h"

int N, WIDTH, HEIGHT, DISKHEIGHT, PEGWIDTH, PEGHEIGHT, count;
ALLEGRO_DISPLAY* display;
ALLEGRO_FONT* font;

bool initialize() {
    count = 0;
    N = 0;
    while (N <= 0) {
        std::cout << "Enter the number of disks desired: ";
        std::cin >> N;
        std::cout << std::endl;
    }
    //Set tentative values for WIDTH and HEIGHT
    /*DISKHEIGHT will be 1/(N+2)th of the window height, leaving 1/HEIGHT of empty peg visible and 1/HEIGHT of black above the pegs
     *Each disk will be 2*N*PEGWIDTH + PEGWIDTH wide (N units on left of peg, N units on right, and then the middle)
     *To satisfy this desired disk width, PEGWIDTH will be calculated as below to leave one black space on the
     * right and left of the biggest disk if the biggest disk were on all three pegs (this never occurs, but the spacing looks appealing)
    */
    WIDTH = 1800, HEIGHT = 1000, DISKHEIGHT = HEIGHT/(N+2), PEGWIDTH = WIDTH/(6*(N-1) + 7), PEGHEIGHT = HEIGHT - DISKHEIGHT;
    //Recalculate based on Peg dimensions to fix integer rounding issues
    WIDTH = PEGWIDTH*(6*(N-1)+7), HEIGHT = DISKHEIGHT*(N+2);

    display = nullptr;
    font = nullptr;

    if (!al_init())
        return 0;

    display = al_create_display(WIDTH, HEIGHT);
    if (!display)
        return 0;

    if (!al_init_primitives_addon())
        return 0;

    if (!al_init_font_addon() || !al_init_ttf_addon())
        return 0;

    font = al_load_ttf_font("DroidSerif-Bold.ttf", DISKHEIGHT/2, 0);

    if (!font)
        return 0;

    return 1;
}
