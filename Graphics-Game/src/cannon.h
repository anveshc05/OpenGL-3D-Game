#ifndef CANNON_H
#define CANNON_H

#include "main.h"

class Cannon {
public:
    Cannon() {}
    Cannon(float x, float y, float z, color_t color, float length, float edge, int flag, float scale_val);
    glm::vec3 position;
    float rotation;
    float edge;
    float length;
    float rotation_y;
    float bullet_speed_x;
    float bullet_speed_z;
    float scale_val;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    bounding_box_t bounding_box();
private:
    VAO *object;
};


#endif // CANNON_H

