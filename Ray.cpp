#include <cmath>

class Ray {
    public:
        Point pos, dir;

        Ray(float x, float y, float angle) : pos(Point(x, y)) 
        {
            dir.x = cos(angle);
            dir.y = sin(angle);
        }

        void lookAt(float x, float y) 
        {
            dir.x = x - pos.x;
            dir.y = y - pos.y;
            normalize();
        }

        void show() const 
        {
            glColor3f(1.0, 1.0, 1.0);
            glBegin(GL_LINES);
            glVertex2f(pos.x, pos.y);
            glVertex2f(pos.x + dir.x * 10, pos.y + dir.y * 10);
            glEnd();
        }

        void normalize() 
        {
            float mag = sqrt(dir.x * dir.x + dir.y * dir.y);
            if (mag != 0) {
                dir.x /= mag;
                dir.y /= mag;
            }
        }
};