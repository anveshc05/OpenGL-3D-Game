#include "mast.h"
#include "main.h"

Mast::Mast(int num) {
    this->position = glm::vec3(0.0, 0.0, 0.0);
    this->rotation = 0;
    speed = 1;
//    this->edge = edge;
    this->flag = 0;
    this->rotation = 180.0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
        -0.1,0.75,-1.75, // triangle 1 : begin
        -0.1,0.75, 0.0, // P714
        -0.1, 2.5, 0.0, // triangle 1 : end

        -0.1,0.75,-1.75,
        -0.1, 2.5, 0.0, //745
        -0.1, 1.75,-1.75,

        0.1, 1.75,-1.75, // triangle 2 : begin
        -0.1,0.75,-1.75, //P675
        -0.1, 1.75,-1.75, // triangle 2 : end

        0.1, 1.75,-1.75,
        0.1,0.75,-1.75, //P687
        -0.1,0.75,-1.75,

        -0.1, 2.5, 0.0,
        -0.1,0.75, 0.0, //412
        0.1,0.75, 0.0,

        0.1, 1.75, 0.0,
        -0.1, 2.5, 0.0, //342
        0.1,0.75, 0.0,

        0.1, 1.75, 0.0,
        0.1,0.75,-1.75, //P386
        0.1, 1.75,-1.75,

        0.1,0.75,-1.75,
        0.1, 1.75, 0.0, //832
        0.1,0.75, 0.0,

        0.1,0.75, 0.0,
        -0.1,0.75,-1.75, //P278
        0.1,0.75,-1.75,

        0.1,0.75, 0.0,
        -0.1,0.75, 0.0, //217
        -0.1,0.75,-1.75,

        0.1, 1.75, 0.0,
        0.1, 1.75,-1.75,  //365
        -0.1, 1.75,-1.75,
        
        0.1, 1.75, 0.0,
        -0.1, 1.75,-1.75, // 354
        -0.1, 2.5, 0.0,

    };
//    color_t colored[7] = {COLOR_VIOLET, COLOR_INDIGO, COLOR_BLUE, COLOR_GREEN_R, COLOR_YELLOW, COLOR_ORANGE, COLOR_RED_MAG};
    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_WHITE, GL_FILL);

}

void Mast::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate );
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);

}

void Mast::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Mast::tick() {
//    this->rotation += 1;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

// bounding_box_t Mast::bounding_box() {
//     float x = this->position.x, y = this->position.y;  float z = this->position.z;
//     bounding_box_t bbox = { x, y, z, 2*this->1.75, 2*this->1.75, 2 * this->1.75};
//     return bbox;
// }


