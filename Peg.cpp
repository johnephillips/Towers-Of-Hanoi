//
// Created by John on 2017-04-23.
//

#include "Peg.h"

void Peg::push(int val) {
    node* newNode = new node;
    newNode->num = val;

    if (top) {
        newNode->next = top;
        top = newNode;
    }
    else {
        newNode->next = nullptr;
        top = newNode;
    }

    size++;
}

int Peg::pop() {
    node* oldTop;
    int oldTopNum = -1;
    if (top) {
        oldTop = top;
        oldTopNum = oldTop->num;
        top = oldTop->next;
        delete oldTop;
    }
    //Return invalid disk number if popping nothing
    if (oldTopNum != -1)
        size--;

    return oldTopNum;
}

ALLEGRO_COLOR Peg::getColour() {
    return colour;
}

void Peg::setX(int left, int right) {
    x1 = left;
    x2 = right;
}

int Peg::getSize() {
    return size;
}

int Peg::getLeft() {
    return x1;
}
int Peg::getRight() {
    return x2;
}
int Peg::getTop() {
    return y1;
}
int Peg::getBot() {
    return y2;
}

Peg::~Peg() {
    node* current = top;
    while (current) {
        top = current->next;
        delete current;
        current = top;
    }
}


void loadPegs(Peg peg[]) {
    for (int i = 0; i < 3; i++) {
        peg[i].setX(PEGWIDTH*(i*(2*N) + N), PEGWIDTH*(i*(2*N) + N + 1));
    }

    for (int i = N-1; i >= 0; i--) {
        peg[0].push(i);
    }
}

void drawPegs(Peg peg[]) {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    //Show counter
    char buffer1[30], buffer2[30];
    itoa(count, buffer1, 10);
    strcpy(buffer2, "moves: ");
    strcat(buffer2, buffer1);
    al_draw_textf(font, al_map_rgb(255, 255, 255), 5, 5, 0, buffer2);

    for (int i = 0; i < 3; i++) {
        Peg::node* current = peg[i].top;
        //Draw peg
        al_draw_filled_rectangle(peg[i].getLeft(), peg[i].getTop(), peg[i].getRight(), peg[i].getBot(), peg[i].getColour());
        //Traverse linked list to display disks
        for (int j = 0; j < peg[i].getSize(); j++) {
            int val = current->num;
            int x1, x2, y1, y2;
            x1 = peg[i].getLeft() - val*PEGWIDTH;
            x2 = peg[i].getRight() + val*PEGWIDTH;
            y1 = peg[i].getBot() - (peg[i].getSize()-j)*DISKHEIGHT;
            y2 = y1 + DISKHEIGHT;
            al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(130, 197, 224));
            //Display the disk's number
            itoa(val, buffer1, 10);
            al_draw_text(font, al_map_rgb(17, 72, 94), (x1 + x2)/2.0f, y1 + (y2-y1)/4.0f, ALLEGRO_ALIGN_CENTRE, buffer1);
            current = current->next;
        }
    }
    al_flip_display();
}

void move(Peg peg[], int n, int curr, int temp, int dest) {
    count++;
    //Moving disk 0, simply move
    if (n == 0) {
        peg[dest].push(peg[curr].pop());
        drawPegs(peg);
    }
    else {
        //Move disk on top of disk n to temp using dest as a temp
        move(peg, n-1, curr, dest, temp);
        //Move disk n
        peg[dest].push(peg[curr].pop());
        drawPegs(peg);
        //Move disk n-1 to dest using curr as a temp
        move(peg, n-1, temp, curr, dest);
    }
}
