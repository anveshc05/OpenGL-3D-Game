#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color);
    glm::vec3 position;
    int rotation;
    int inc;
    float rotation_x;
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
    VAO *object1;
    VAO *object2;
    VAO *object3;
};

#endif // BALL_H
