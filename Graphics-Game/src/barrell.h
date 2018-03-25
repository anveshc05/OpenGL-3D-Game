#ifndef BARRELL_H
#define BARRELL_H
#include "main.h"


class Barrell {
public:
    Barrell() {}
    Barrell(float x, float y, float z, float edge, color_t color);
    glm::vec3 position;
    float rotation;
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
    bounding_box_t jump_bounding_box();
private:
    VAO *object;
};


#endif // BARRELL_H

