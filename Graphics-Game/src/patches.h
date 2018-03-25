#include "main.h"

#ifndef Patches_H
#define Patches_H


class Patches {
public:
    Patches() {}
    Patches(float x, float y, float z, color_t color, int flag);
    glm::vec3 position;
    float rotation;
    float edge;
    int flag;
    int inc;
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
    VAO *object[2];
};

#endif // Patches_H
