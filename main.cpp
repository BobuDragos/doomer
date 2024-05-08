
#include <stdio.h>

#include <GL/glut.h>
#include <GL/freeglut.h>

#include "game.cpp"

#include <cmath>
#include <vector>


std::vector<Line> walls;
RayCaster caster;

const int WIDTH = 500;
const int HEIGHT = 500;

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
    // walls.push_back(-1, -1, -1,  1);
    // walls.push_back(-1,  1,  1,  1);
    // walls.push_back( 1,  1,  1, -1);
    // walls.push_back( 1, -1, -1, -1);

    walls.push_back(Line(    0,      0, WIDTH,      0));
    walls.push_back(Line(WIDTH,      0, WIDTH, HEIGHT));
    walls.push_back(Line(WIDTH, HEIGHT,     0, HEIGHT));
    walls.push_back(Line(    0, HEIGHT,     0,      0));


    walls.push_back(Line(  WIDTH/4,   HEIGHT/4, 3*WIDTH/4,   HEIGHT/4));
    walls.push_back(Line(3*WIDTH/4,   HEIGHT/4, 3*WIDTH/4, 3*HEIGHT/4));
    walls.push_back(Line(3*WIDTH/4, 3*HEIGHT/4,   WIDTH/4, 3*HEIGHT/4));
    walls.push_back(Line(  WIDTH/4, 3*HEIGHT/4, WIDTH/4, HEIGHT/4));
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    for (const auto& wall : walls) 
    {
      printf("%f, %f, %f, %f \n", wall.a.x, wall.a.y, wall.b.x, wall.b.y);
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
        caster.move(0, -25); // Move particle up
        caster.show();
        break;
    case 's':
        caster.move(0, 25); // Move particle down
        break;
    case 'a':
        caster.move(-25, 0); // Move particle left
        break;
    case 'd':
        caster.move(25, 0); // Move particle right
        break;
  }
  glutPostRedisplay(); // Request redraw
}

void mouse(int button, int state, int x, int y) {
   printf("Call MouseFunc : ati %s butonul %s in pozitia %d %d\n",
      (state == GLUT_DOWN) ? "apasat" : "eliberat",
      (button == GLUT_LEFT_BUTTON) ? 
      "stang" : 
      ((button == GLUT_RIGHT_BUTTON) ? "drept": "mijlociu"),
      x, y);
}

int main(int argc, char** argv) 
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("2D Ray Casting");
    setup();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}

