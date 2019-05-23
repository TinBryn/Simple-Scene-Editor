//
// Created by kieran on 22/05/19.
//

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "init.h"
#include "callbacks.h"
#include "state.h"

void init(int argc, char **argv)
{
    State::window_height = 768;
    State::window_width = 1024;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(State::window_width, State::window_height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    glewInit();
    glutDisplayFunc(render_scene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special_keyboard);
    glutIdleFunc(idle);
    glClearColor(0.2, 0.3, 0.4, 1.0);
    glEnable(GL_DEPTH_TEST);

    State::program.attachShader({GL_VERTEX_SHADER, "../src/shaders/vert.glsl", 0});
    State::program.attachShader({GL_FRAGMENT_SHADER, "../src/shaders/frag.glsl", 0});
    State::program.reload();
//    State::shader = initShader("../src/shaders/vert.glsl", "../src/shaders/frag.glsl");
//    glUseProgram(State::shader);

    State::models.push_back(createModel(State::program.id));
}

void loop()
{
    glutMainLoop();
}
