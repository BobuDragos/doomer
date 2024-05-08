
#include <stdio.h>

class Line
{
    public:
        Point a, b;

        Line(float x1, float y1, float x2, float y2) : a(Point(x1, y1)), b(Point(x2, y2)) {}

        void show() const 
        {
            glColor3f(1.0, 1.0, 1.0);
            glBegin(GL_LINES);
              glVertex2f(a.x, a.y);
              glVertex2f(b.x, b.y);
            glEnd();

            // printf("%f, %f, %f, %f", a.x, a.y, b.x, b.y);
        }
};
