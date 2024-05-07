
#include <stdio.h>

#include <GL/glut.h>
#include <GL/freeglut.h>

#include "game.cpp"

#include <cmath>
#include <vector>


std::vector<Line> walls;
RayCaster caster;

void setup() 
{
    // for (int i = 0; i < 5; i++) 
    // {
    //     float x1 = rand() % 400;
    //     float x2 = rand() % 400;
    //     float y1 = rand() % 400;
    //     float y2 = rand() % 400;
    //     walls.emplace_back(x1, y1, x2, y2);
    // }
    walls.emplace_back(-1, -1, -1,  1);
    walls.emplace_back(-1,  1,  1,  1);
    walls.emplace_back( 1,  1,  1, -1);
    walls.emplace_back( 1, -1, -1, -1);


    walls.emplace_back( 100, 100, -100, -100);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    for (const auto& wall : walls) 
    {
        wall.show();
    }
    // You'll need to handle mouse input differently in OpenGL.
    // Replace mouseX and mouseY with appropriate input handling.
    // caster.update(mouseX, mouseY);
    caster.show();
    caster.look(walls);
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

void keyboard(unsigned char key, int x, int y)
{
  switch (key) 
  {
    case 'w':
        caster.move(0, -50); // Move particle up
        caster.show();
        break;
    case 's':
        caster.move(0, 5); // Move particle down
        break;
    case 'a':
        caster.move(-5, 0); // Move particle left
        break;
    case 'd':
        caster.move(5, 0); // Move particle right
        break;
  }
  glutPostRedisplay(); // Request redraw
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
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

