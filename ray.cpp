#include <cmath>

class Ray {
    public:
        Point pos, dir;

        Ray(float x, float y, float angle) : pos(Point(x, y)) 
        {
            dir.x = cos(angle);
            dir.y = sin(angle);
        }

        void show() const 
        {
            glColor3f(1.0, 1.0, 1.0);
            glBegin(GL_LINES);
              glVertex2f(pos.x, pos.y);
              glVertex2f(pos.x + dir.x * 1000, pos.y + dir.y * 1000);
            glEnd();
        }
	Point cast(const Ray& ray, const Line& wall) const 
		{
		    float x1 = wall.a.x;
		    float y1 = wall.a.y;
		    float x2 = wall.b.x;
		    float y2 = wall.b.y;

		    float x3 = ray.pos.x;
		    float y3 = ray.pos.y;
		    float x4 = ray.pos.x + ray.dir.x;
		    float y4 = ray.pos.y + ray.dir.y;

		    float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
		    if (den == 0) return {0, 0};

		    float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
		    float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;
		    if (t > 0 && t < 1 && u > 0) 
		    {
			Point pt;
			pt.x = x1 + t * (x2 - x1);
			pt.y = y1 + t * (y2 - y1);
			return pt;
		    } 
		    else 
		    {
			return {-1, -1};
		    }
		}

};
