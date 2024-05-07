#include <GL/glut.h>
#include <vector>
#include <cmath>
#include <cstdlib>

#define PI 3.14159265

int sceneW = 400;
int sceneH = 400;

class Boundary {
public:
    Boundary(float x1, float y1, float x2, float y2) {
        this->a[0] = x1;
        this->a[1] = y1;
        this->b[0] = x2;
        this->b[1] = y2;
    }

    void show() {
        glBegin(GL_LINES);
        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(a[0], a[1]);
        glVertex2f(b[0], b[1]);
        glEnd();
    }

    float* getA() {
        return a;
    }

    float* getB() {
        return b;
    }

private:
    float a[2];
    float b[2];
};

class Ray {
public:
    Ray(float pos[2], float angle) {
        this->pos[0] = pos[0];
        this->pos[1] = pos[1];
        this->dir[0] = cos(angle);
        this->dir[1] = sin(angle);
    }

    void setAngle(float angle) {
        this->dir[0] = cos(angle);
        this->dir[1] = sin(angle);
    }

    void lookAt(float x, float y) {
        this->dir[0] = x - this->pos[0];
        this->dir[1] = y - this->pos[1];
        normalize(this->dir);
    }

    void show() {
        glBegin(GL_LINES);
        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(pos[0], pos[1]);
        glVertex2f(pos[0] + dir[0] * 10, pos[1] + dir[1] * 10);
        glEnd();
    }

    std::vector<float> cast(Boundary wall) {
        float x1 = wall.getA()[0];
        float y1 = wall.getA()[1];
        float x2 = wall.getB()[0];
        float y2 = wall.getB()[1];

        float x3 = this->pos[0];
        float y3 = this->pos[1];
        float x4 = this->pos[0] + this->dir[0];
        float y4 = this->pos[1] + this->dir[1];

        float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
        if (den == 0) {
            return {};
        }

        float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
        float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;
        if (t > 0 && t < 1 && u > 0) {
            float pt[2];
            pt[0] = x1 + t * (x2 - x1);
            pt[1] = y1 + t * (y2 - y1);
            std::vector<float> result = {pt[0], pt[1]};
            return result;
        } else {
            return {};
        }
    }

private:
    float pos[2];
    float dir[2];

    void normalize(float vec[2]) {
        float magnitude = sqrt(vec[0] * vec[0] + vec[1] * vec[1]);
        vec[0] /= magnitude;
        vec[1] /= magnitude;
    }
};

class Particle {
public:
    Particle() {
        this->fov = PI / 4;
        this->pos[0] = sceneW / 2;
        this->pos[1] = sceneH / 2;
        this->heading = 0;
        for (float a = -this->fov / 2; a < this->fov / 2; a += 1) {
            this->rays.push_back(Ray(this->pos, a));
        }
    }

    void updateFOV(float fov) {
        this->fov = fov * PI / 180;
        this->rays.clear();
        for (float a = -this->fov / 2; a < this->fov / 2; a += 1) {
            this->rays.push_back(Ray(this->pos, a + this->heading));
        }
    }

    void rotate(float angle) {
        this->heading += angle;
        int index = 0;
        for (float a = -this->fov / 2; a < this->fov / 2; a += 1) {
            this->rays[index].setAngle(a + this->heading);
            index++;
        }
    }

    void move(float amt) {
        this->pos[0] += cos(this->heading) * amt;
        this->pos[1] += sin(this->heading) * amt;
    }

std::vector<float> look(std::vector<Boundary>& walls) {
    std::vector<float> scene;
    for (int i = 0; i < this->rays.size(); i++) {
        Ray ray = this->rays[i];
        float closest = INFINITY;
        std::vector<float> closest_pt;
        for (Boundary& wall : walls) {
            std::vector<float> pt = ray.cast(wall);
            if (!pt.empty()) {
                float d = sqrt(pow(this->pos[0] - pt[0], 2) + pow(this->pos[1] - pt[1], 2));
                float a = atan2(ray.dir[1], ray.dir[0]) - this->heading;
                d *= cos(a);
                if (d < closest) {
                    closest = d;
                    closest_pt = pt;
                }
            }
        }
        if (!closest_pt.empty()) {
            scene.push_back(closest);
            glColor3f(1.0, 1.0, 1.0); // Set color to white
            glBegin(GL_LINES);
            glVertex2f(this->pos[0], this->pos[1]);
            glVertex2f(closest_pt[0], closest_pt[1]);
            glEnd();
        }
        else {
            scene.push_back(0);
        }
    }
    return scene;
}

void show() {
    glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 1.0); // Set color to white
        glVertex2f(this->pos[0], this->pos[1]);
        glEnd();
        for (Ray& ray : this->rays) {
            ray.show();
        }
    }

private:
    float fov;
    float pos[2];
    std::vector<Ray> rays;
    float heading;
};

std::vector<Boundary> walls;
Particle particle;

void initWalls() {
    for (int i = 0; i < 4; i++) {
        float x1 = rand() % sceneW;
        float x2 = rand() % sceneW;
        float y1 = rand() % sceneH;
        float y2 = rand() % sceneH;
        walls.push_back(Boundary(x1, y1, x2, y2));
    }
    walls.push_back(Boundary(0, 0, sceneW, 0));
    walls.push_back(Boundary(sceneW, 0, sceneW, sceneH));
    walls.push_back(Boundary(sceneW, sceneH, 0, sceneH));
    walls.push_back(Boundary(0, sceneH, 0, 0));
}

void changeFOV(int fov) {
    particle.updateFOV(fov);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    for (Boundary& wall : walls) {
        wall.show();
    }
    particle.show();

    std::vector<float> scene = particle.look(walls);
    float w = sceneW / scene.size();
    glPushMatrix();
    glTranslatef(sceneW, 0, 0);
    for (int i = 0; i < scene.size(); i++) {
        float sq = scene[i] * scene[i];
        float wSq = sceneW * sceneW;
        float b = (sq, 0, wSq, 255, 0);
        float h = (scene[i], 0, sceneW, sceneH, 0);
        glColor3f(b, b, b);
        glBegin(GL_QUADS);
        glVertex2f(i * w, sceneH / 2);
        glVertex2f(i * w + w, sceneH / 2);
        glVertex2f(i * w + w, sceneH / 2 - h);
        glVertex2f(i * w, sceneH / 2 - h);
        glEnd();
    }
    glPopMatrix();

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: // ESC key
            exit(0);
            break;
        case 'a':
            particle.rotate(-0.01);
            break;
        case 'd':
            particle.rotate(0.01);
            break;
        case 'w':
            particle.move(1);
            break;
        case 's':
            particle.move(-1);
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 400);
    glutCreateWindow("Ray Casting");
    glClearColor(0, 0, 0, 1);
    gluOrtho2D(0, 800, 400, 0);
    initWalls();
    particle = Particle();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

