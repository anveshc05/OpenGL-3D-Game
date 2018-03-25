#include "main.h"

#ifndef Mast_H
#define Mast_H


class Mast {
public:
    Mast() {};
    Mast(int num);
    glm::vec3 position;
    int rotation;
    float edge;
    int flag;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    double speed_y;
    double acc_y;
    double acc_z;
    double acc_x;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // Mast_H

