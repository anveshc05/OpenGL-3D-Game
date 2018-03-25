#include "main.h"

#ifndef Gift_H
#define Gift_H


class Gift {
public:
    Gift() {}
    Gift(float x, float y, float z, float edge);
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
private:
    VAO *object[6];
};

#endif // Gift_H
