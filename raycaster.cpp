#include <vector>
#include <stdio.h>
class RayCaster
{
    public:
        RayCaster() : pos{500.0f / 2.0f, 500.0f / 2.0f} 
        {
            for (float a = 0; a < 360; a += 0.01) 
            {
                rays.push_back(Ray(pos.x, pos.y, a * M_PI / 180.0f));
            }
        }

        void set(float x, float y) 
        {
            pos.x = x;
            pos.y = y;
        }

        void move(float dx, float dy) {
            pos.x += dx;
            pos.y += dy;
        }
        
        void look(const std::vector<Line>& walls)
        {
            for (auto& ray : rays) 
            {
                Point closest;
                float record = INFINITY;
		printf("%f",record);
                for (const auto& wall : walls) 
                {
                    Point pt = cast(ray, wall);
		    printf("%f, %f", pt.x, pt.y);
                    //if (pt != null) 
                    //{
                        float d = sqrt(pow(pos.x - pt.x, 2) + pow(pos.y - pt.y, 2));
                        if (d < record) 
                        {
                            record = d;
                            closest = pt;
                        }
                    //}
                }
	    if (record != INFINITY) 
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

        
    Point pos;
};
