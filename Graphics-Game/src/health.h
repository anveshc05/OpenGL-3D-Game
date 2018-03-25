#ifndef HEALTH_H
#define HEALTH_H

#include "main.h"

class Health {
public:
    Health() {}
    Health(float length, float width, int health);
    glm::vec3 position;
    float value;
    void draw(glm::mat4 VP);
    bounding_box_t bounding_box();
    private:
        VAO *object;
};

#endif // HEALTH_H

