
#include <stdio.h>

#include <GL/glut.h>
#include <GL/freeglut.h>

#include "game.cpp"

#include <cmath>
#include <vector>


std::vector<Line> walls;
RayCaster particle;

void setup() 
{
    for (int i = 0; i < 5; i++) 
    {
        float x1 = rand() % 400;
        float x2 = rand() % 400;
        float y1 = rand() % 400;
        float y2 = rand() % 400;
        walls.emplace_back(x1, y1, x2, y2);
    }
    walls.emplace_back(-1, -1, 400, -1);
    walls.emplace_back(400, -1, 400, 400);
    walls.emplace_back(400, 400, -1, 400);
    walls.emplace_back(-1, 400, -1, -1);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    for (const auto& wall : walls) 
    {
        wall.show();
    }
    // You'll need to handle mouse input differently in OpenGL.
    // Replace mouseX and mouseY with appropriate input handling.
    // particle.update(mouseX, mouseY);
    particle.show();
    particle.look(walls);
    glutSwapBuffers();
}

void reshape(int w, int h) 
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, w, h, 0.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


int main(int argc, char** argv) 
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("2D Ray Casting");
    setup();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

