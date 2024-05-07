#include <iostream>
#include <cmath>
#include <vector>
#include <GL/glut.h>

class Boundary {
public:
    struct Point {
        float x;
        float y;
        Point(float _x, float _y) : x(_x), y(_y) {}
        Point() : x(0), y(0) {}
    };

    Boundary(float x1, float y1, float x2, float y2) : a(Point(x1, y1)), b(Point(x2, y2)) {}

    void show() const {
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINES);
        glVertex2f(a.x, a.y);
        glVertex2f(b.x, b.y);
        glEnd();
    }

    Point a, b;
};

class Ray {
public:
    struct Point {
        float x;
        float y;
        Point(float _x, float _y) : x(_x), y(_y) {}
        Point() : x(0), y(0) {}
    };

    Ray(float x, float y, float angle) : pos(Point(x, y)) {
        dir.x = cos(angle);
        dir.y = sin(angle);
    }

    void lookAt(float x, float y) {
        dir.x = x - pos.x;
        dir.y = y - pos.y;
        normalize();
    }

    void show() const {
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINES);
        glVertex2f(pos.x, pos.y);
        glVertex2f(pos.x + dir.x * 10, pos.y + dir.y * 10);
        glEnd();
    }

    void normalize() {
        float mag = sqrt(dir.x * dir.x + dir.y * dir.y);
        if (mag != 0) {
            dir.x /= mag;
            dir.y /= mag;
        }
    }

    Point pos, dir;
};

class Particle {
public:
    Particle() : pos{400.0f / 2.0f, 400.0f / 2.0f} {
        for (float a = 0; a < 360; a += 1) {
            rays.push_back(Ray(pos.x, pos.y, a * M_PI / 180.0f));
        }
    }

    void update(float x, float y) {
        pos.x = x;
        pos.y = y;
    }

    void move(float dx, float dy) {
        pos.x += dx;
        pos.y += dy;
    }

    void look(const std::vector<Boundary>& walls) {
        for (auto& ray : rays) {
            Boundary::Point closest;
            float record = INFINITY;
            for (const auto& wall : walls) {
                Boundary::Point pt = cast(ray, wall);
                if (pt.x != -1 && pt.y != -1) {
                    float d = sqrt(pow(pos.x - pt.x, 2) + pow(pos.y - pt.y, 2));
                    if (d < record) {
                        record = d;
                        closest = pt;
                    }
                }
            }
            if (record != INFINITY) {
                glColor3f(1.0, 1.0, 1.0);
                glBegin(GL_LINES);
                glVertex2f(pos.x, pos.y);
                glVertex2f(closest.x, closest.y);
                glEnd();
            }
        }
    }

    void show() const {
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_POINTS);
        glVertex2f(pos.x, pos.y);
        glEnd();
        for (const auto& ray : rays) {
            ray.show();
        }
    }

private:
    std::vector<Ray> rays;

    Boundary::Point cast(const Ray& ray, const Boundary& wall) const {
        float x1 = wall.a.x;
        float y1 = wall.a.y;
        float x2 = wall.b.x;
        float y2 = wall.b.y;

        float x3 = ray.pos.x;
        float y3 = ray.pos.y;
        float x4 = ray.pos.x + ray.dir.x;
        float y4 = ray.pos.y + ray.dir.y;

        float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
        if (den == 0) return {-1, -1};

        float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
        float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;
        if (t > 0 && t < 1 && u > 0) {
            Boundary::Point pt;
            pt.x = x1 + t * (x2 - x1);
            pt.y = y1 + t * (y2 - y1);
            return pt;
        } else {
            return {-1, -1};
        }
    }

    Boundary::Point pos;
};

std::vector<Boundary> walls;
Particle particle;

void setup() {
    for (int i = 0; i < 5; i++) {
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
    for (const auto& wall : walls) {
        wall.show();
    }
    particle.show();
    particle.look(walls);
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, w, h, 0.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            particle.move(0, -5); // Move particle up
            break;
        case 's':
            particle.move(0, 5); // Move particle down
            break;
        case 'a':
            particle.move(-5, 0); // Move particle left
            break;
        case 'd':
            particle.move(5, 0); // Move particle right
            break;
    }
    glutPostRedisplay(); // Request redraw
}

int main(int argc, char** argv) {
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
glutInitWindowSize(400, 400);
glutCreateWindow("2D Ray Casting");
setup();
glutDisplayFunc(display);
glutReshapeFunc(reshape);
glutKeyboardFunc(keyboard); // Register keyboard callback function
glutMainLoop();
return 0;
}

