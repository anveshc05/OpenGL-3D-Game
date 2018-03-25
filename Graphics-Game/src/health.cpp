#include "main.h"
#include "health.h"

Health::Health(float length, float width, int health) {
    this->position = glm::vec3(-7, 6, 0);
    this->value = health;
//    GLfloat vertex_buffer_data[]{
//        0, 0,  0,
//        length, 0, 0,
//        length, -width, 0,

//        0, -width, 0,
//        0, 0, 0,
//        length, -width, 0,
//    };
//    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_GREEN, GL_FILL);
}

void Health::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

