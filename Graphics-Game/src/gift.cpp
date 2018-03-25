#include "gift.h"
#include "main.h"

Gift::Gift(float x, float y, float z, float edge) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    this->edge = edge;
    this->flag = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
        -edge,-edge,-edge, // triangle 1 : begin
        -edge,-edge, edge, // P714
        -edge, edge, edge, // triangle 1 : end

        -edge,-edge,-edge,
        -edge, edge, edge, //745
        -edge, edge,-edge,

        edge, edge,-edge, // triangle 2 : begin
        -edge,-edge,-edge, //P675
        -edge, edge,-edge, // triangle 2 : end

        edge, edge,-edge,
        edge,-edge,-edge, //P687
        -edge,-edge,-edge,

        -edge, edge, edge,
        -edge,-edge, edge, //412
        edge,-edge, edge,

        edge, edge, edge,
        -edge, edge, edge, //342
        edge,-edge, edge,

        edge, edge, edge,
        edge,-edge,-edge, //P386
        edge, edge,-edge,

        edge,-edge,-edge,
        edge, edge, edge, //832
        edge,-edge, edge,

        edge,-edge, edge,
        -edge,-edge,-edge, //P278
        edge,-edge,-edge,

        edge,-edge, edge,
        -edge,-edge, edge, //217
        -edge,-edge,-edge,

        edge, edge, edge,
        edge, edge,-edge,  //365
        -edge, edge,-edge,

        edge, edge, edge,
        -edge, edge,-edge, // 354
        -edge, edge, edge,

    };
    color_t colored[7] = {COLOR_VIOLET, COLOR_INDIGO, COLOR_BLUE, COLOR_GREEN_R, COLOR_YELLOW, COLOR_ORANGE, COLOR_RED_MAG};
    this->object[0] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, colored[0], GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data+18, colored[1], GL_FILL);
    this->object[2] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data+36, colored[2], GL_FILL);
    this->object[3] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data+54, colored[3], GL_FILL);
    this->object[4] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data+72, colored[4], GL_FILL);
    this->object[5] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data+90, colored[6], GL_FILL);

}

void Gift::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate );
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
    draw3DObject(this->object[1]);
    draw3DObject(this->object[2]);
    draw3DObject(this->object[3]);
    draw3DObject(this->object[4]);
    draw3DObject(this->object[5]);

}

void Gift::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Gift::tick() {
//    this->rotation += 1;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

bounding_box_t Gift::bounding_box() {
    float x = this->position.x, y = this->position.y;  float z = this->position.z;
    bounding_box_t bbox = { x, y, z, 2*this->edge, 2*this->edge, 2 * this->edge};
    return bbox;
}

