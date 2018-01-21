/*****************************************************************************
 *	Name:   John Phillips                                                    *
 *	Course: ICS4U                                                            *
 *	Date:   May 5, 2017                                                      *
 *	                                                                         *
 *	Purpose: Solve the towers of hanoi visually with N disks                 *
 *	                                                                         *
 *	Usage: Enter an integer number of disks when prompted. If window         *
 *	       dimensions are not as desired tweak Setup.cpp.                    *
 *	                                                                         *
 *                                                                           *
 *	Revision History:  None                                                  *
 *	                                                                         *
 *	Known Issues: Scale is too small for N>30.                               *
 *	                                                                         *
 ****************************************************************************/

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include "Setup.h"

int main () {
    //Read in number of disks desired and initialize allegro routines and constants
    if (!initialize()) {
        al_destroy_display(display);
        al_destroy_font(font);
        return 1;
    }

    Peg peg[3];
    //Put N disks on peg[0]
    loadPegs(peg);

    //Recursively move the disks to peg[2], showing each state along the way
    drawPegs(peg);
    move(peg, N-1, 0, 1, 2);
    al_rest(10.0);

    return 0;
}

