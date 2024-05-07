#include <vector>

class RayCaster
{
    public:
        RayCaster() : pos{400.0f / 2.0f, 400.0f / 2.0f} 
        {
            for (float a = 0; a < 360; a += 1) 
            {
                rays.push_back(Ray(pos.x, pos.y, a * M_PI / 180.0f));
            }
        }

        void update(float x, float y) 
        {
            pos.x = x;
            pos.y = y;
        }

        void look(const std::vector<Line>& walls) 
        {
            for (auto& ray : rays) 
            {
                Point closest;
                float record = INFINITY;
                for (const auto& wall : walls) 
                {
                    Point pt = cast(ray, wall);
                    if (pt.x != -1 && pt.y != -1) 
                    {
                        float d = sqrt(pow(pos.x - pt.x, 2) + pow(pos.y - pt.y, 2));
                        if (d < record) 
                        {
                            record = d;
                            closest = pt;
                        }
                    }
                }
                if (record != INFINITY) 
                {
                    glColor3f(1.0, 1.0, 1.0);
                    glBegin(GL_LINES);
                    glVertex2f(pos.x, pos.y);
                    glVertex2f(closest.x, closest.y);
                    glEnd();
                }
            }
        }

        void show() const 
        {
            glColor3f(1.0, 1.0, 1.0);
            glBegin(GL_POINTS);
            glVertex2f(pos.x, pos.y);
            glEnd();
            for (const auto& ray : rays) 
            {
                ray.show();
            }
        }

    private:
        std::vector<Ray> rays;

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
            if (den == 0) return {-1, -1};

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

    Point pos;
};