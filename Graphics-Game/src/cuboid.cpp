#include "cuboid.h"
#include "main.h"

Cuboid::Cuboid(float x, float y, float z, color_t color, float length, float edge) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
        edge,edge,-length, // triangle 1 : begin
        edge,edge, length, // P714
        -edge, edge, length, // triangle 1 : end

        edge,edge,-length,
        -edge, edge, length, //745
        -edge, edge,-length,

        edge, edge,-length, // triangle 2 : begin
        edge,edge,-length, //P675
        -edge, edge,-length, // triangle 2 : end

        edge, edge,-length,
        edge,edge,-length, //P687
        edge,edge,-length,

        -edge, edge, length,
        edge,edge, length, //412
        edge,edge, length,

        edge, edge, length,
        -edge, edge, length, //342
        edge,edge, length,

        edge, edge, length,
        edge,edge,-length, //P386
        edge, edge,-length,

        edge,edge,-length,
        edge, edge, length, //832
        edge,edge, length,

        edge,edge, length,
        edge,edge,-length, //P278
        edge,edge,-length,

        edge,edge, length,
        edge,edge, length, //217
        edge,edge,-length,
        edge, edge, length,
        edge, edge,length,  //365
        edge, edge,length,

        edge, edge, length,
        edge, edge,length, // 354
        edge, edge, length,

    };
    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Cuboid::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate );
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Cuboid::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Cuboid::tick() {
//    this->rotation += 1;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

