//
// Created by kieran on 22/05/19.
//

#ifndef CITS3003_CALLBACKS_H
#define CITS3003_CALLBACKS_H

void render_scene();

void keyboard(unsigned char key, int x, int y);

void special_keyboard(int key, int x, int y);

void resize(int width, int height);

void mouseClick(int button, int state, int x, int y);

void mouseMove(int x, int y);

void idle();

#endif //CITS3003_CALLBACKS_H
