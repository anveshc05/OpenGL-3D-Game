#include "monster.h"
#include "main.h"

Monster::Monster(float x, float y, float z, int health, float length, float edge, float scale_factor, int flag) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->rotation_y = 0;
    speed = 0.0;
    this->scale_val = scale_factor;
    this->edge = edge;
    this->length = length;
    this->monster_speed_x = 0.0;
    this->monster_speed_z = 0.0;
    this->health = health;
    if (flag) this->scale_val = 6;
    this->flag = flag;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
//        -edge,0.0,-edge, // triangle 1 : begin
//        -edge,0.0, edge, // P714
//        -edge, length, edge, // triangle 1 : end

//        -edge,0.0,-edge,
//        -edge, length, edge, //745
//        -edge, length,-edge,

//        edge, length,-edge, // triangle 2 : begin
//        -edge,0.0,-edge, //P675
//        -edge, length,-edge, // triangle 2 : end

//        edge, length,-edge,
//        edge,0.0,-edge, //P687
//        -edge,0.0,-edge,

//        -edge, length, edge,
//        -edge,0.0, edge, //412
//        edge,0.0, edge,

//        edge, length, edge,
//        -edge, length, edge, //342
//        edge,0.0, edge,

//        edge, length, edge,
//        edge,0.0,-edge, //P386
//        edge, length,-edge,

//        edge,0.0,-edge,
//        edge, length, edge, //832
//        edge,0.0, edge,

        edge,0.0, edge,
        edge,0.0,-edge,
        0.0, length, 0.0,

        edge,0.0, edge,
        -edge,0.0, edge,
        0.0, length, 0.0,

        -edge,0.0, edge,
        -edge,0.0,-edge,
        0.0, length, 0.0,

        -edge,0.0,-edge,
        edge,0.0,-edge,
        0.0, length, 0.0,

        edge,0.0, edge,
        edge,0.0,-edge, //P278
        edge,0.0,-edge,

        edge,0.0, edge,
        -edge,0.0, edge, //217
        edge,0.0,-edge,

//        edge, length, edge,
//        edge, length, -edge,  //365
//        -edge, length, -edge,

//        edge, length, edge,
//        -edge, length, -edge, // 354
//        -edge, length, edge,

    };
    if (!flag){
        color_t colored[3] = {COLOR_YELLOW, COLOR_GREEN_GRASS, COLOR_RED_MAG};
        this->object = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data, colored[this->health], GL_FILL);
    }
    else{
        color_t colored[7] = {COLOR_VIOLET, COLOR_INDIGO, COLOR_BLUE, COLOR_GREEN_R, COLOR_YELLOW, COLOR_ORANGE, COLOR_BLACK};
        this->object = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data, colored[this->health], GL_FILL);
    }

}

void Monster::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotate2    = glm::rotate((float) (this->rotation_y * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 scale    = glm::scale(glm::vec3(this->scale_val, this->scale_val, this->scale_val));

    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate2 * rotate * scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Monster::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Monster::tick() {
//    this->rotation+=1;
     this->position.y += speed;
     this->position.x += monster_speed_x;
     this->position.z += monster_speed_z;
}


bounding_box_t Monster::bounding_box() {
    float x = this->position.x, y = this->position.y;  float z = this->position.z;
    bounding_box_t bbox = { x, y, z, 2 * this->edge * this->scale_val, this->length * this->scale_val, 2 * this->edge * this->scale_val};
    return bbox;
}

