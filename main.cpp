
#include <stdio.h>

#include <GL/glut.h>
#include <GL/freeglut.h>

#include "game.cpp"

#include <cmath>
#include <vector>


struct Player
{
RayCaster caster;

struct Keybindings
{
  char* moveup    = "w";
  char* movedown  = "s";
  char* moveleft  = "a";
  char* moveright = "d";
 
  char* rotateleft  = "q";
  char* rotateright = "e";
} keys;

}player;

struct Map
{

std::vector<Line> walls;

}map;



const int WIDTH = 500;
const int HEIGHT = 500;

void place_walls() 
{
    map.walls.push_back(Line(    0,      0, WIDTH,      0));
    map.walls.push_back(Line(WIDTH,      0, WIDTH, HEIGHT));
    map.walls.push_back(Line(WIDTH, HEIGHT,     0, HEIGHT));
    map.walls.push_back(Line(    0, HEIGHT,     0,      0));


    map.walls.push_back(Line(  WIDTH/4,   HEIGHT/4, 3*WIDTH/4,   HEIGHT/4));
    map.walls.push_back(Line(3*WIDTH/4,   HEIGHT/4, 3*WIDTH/4, 3*HEIGHT/4));
    map.walls.push_back(Line(3*WIDTH/4, 3*HEIGHT/4,   WIDTH/4, 3*HEIGHT/4));
    map.walls.push_back(Line(  WIDTH/4, 3*HEIGHT/4, WIDTH/4, HEIGHT/4));
}

void place_player()
{
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    for (const auto& wall : map.walls) 
    {
      wall.show();
    }
    // You'll need to handle mouse input differently in OpenGL.
    // Replace mouseX and mouseY with appropriate input handling.
    // caster.update(mouseX, mouseY);
//player.caster.show();
    player.caster.look(map.walls);
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
        player.caster.move(0, -25); // Move particle up
        break;
    case 's':
        player.caster.move(0, 25); // Move particle down
        break;
    case 'a':
        player.caster.move(-25, 0); // Move particle left
        break;
    case 'd':
        player.caster.move(25, 0); // Move particle right
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
    place_walls();
    place_player();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}

