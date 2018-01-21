//
// Created by John on 2017-04-23.
//

#ifndef TOWERSOFHANOI_PEG_H
#define TOWERSOFHANOI_PEG_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "Constants.h"
#include <cstring>

class Peg {
    //The left and right x coordinates
    int x1, x2;
    //The top and bottom y coordinates
    //height: the number of disks on the peg
    int y1 = HEIGHT - PEGHEIGHT, y2 = HEIGHT, size = 0;
    ALLEGRO_COLOR colour = al_map_rgb(255, 165, 79);
public:
    //The disk linked list stack structure
    struct node {
        int num;
        node* next;
    };
    node* top = nullptr;
    //Add a disk of number val
    void push(int val);
    //Pop off the top disk and returns its number
    int pop();
    ALLEGRO_COLOR getColour();
    //Set x1 and x2
    void setX(int left, int right);
    int getSize();
    int getLeft();
    int getRight();
    int getTop();
    int getBot();
    ~Peg();
};

void loadPegs(Peg peg[]);
void drawPegs(Peg peg[]);
void move(Peg peg[], int n, int curr, int temp, int dest);

#endif //TOWERSOFHANOI_PEG_H
