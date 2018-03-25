#ifndef Monster_H
#define Monster_H

#include "main.h"

class Monster {
public:
    Monster() {}
    Monster(float x, float y, float z, int health, float length, float edge, float scale_val, int flag);
    glm::vec3 position;
    float rotation;
    float edge;
    int flag;
    float length;
    float rotation_y;
    float monster_speed_x;
    float monster_speed_z;
    float scale_val;
    int health;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    bounding_box_t bounding_box();
private:
    VAO *object;
    VAO *object1;
};


#endif // Monster_H

