#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.05;
    acc_y = -0.01;
    acc_x = -0.002;
    acc_z = -0.002;
    speed_y = 0.0;
    inc = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
        -0.5, -0.5, -1.0,
        0.5, -0.5, -1.0,
        0.0, 0.5, -1.75,

        1.0, 0.5, -1.25,
        0.0, 0.5, -1.75,
        0.5, -0.5, -1.0,

        -1.0f, 0.5f,-1.25f,
        0.0, 0.5, -1.75,
        -0.5, -0.5, -1.0,

        -0.5f,-0.5f,-1.0f, // triangle 1 : begin
        -0.5f,-0.5f, 1.0f, // P714
        -0.75f, 0.25f, 1.25f, // triangle 1 : end

        -0.5f,-0.5f,-1.0f,
        -0.75f, 0.25f, 1.25f, //745
        -1.0f, 0.5f,-1.25f,
//        0.0, 0.5, -1.5,

//        0.75f, 0.5f,-1.25f, // triangle 2 : begin
//        -0.5f,-0.5f,-1.0f, //P675
//        -0.75f, 0.5f,-1.25f, // triangle 2 : end

//        0.75f, 0.5f,-1.25f,
//        0.5f,-0.5f,-1.0f, //P687
//        -0.5f,-0.5f,-1.0f,


        -0.75f, 0.25f, 1.25f,
        -0.5f,-0.5f, 1.0f, //412
        0.5f,-0.5f, 1.0f,

        0.75f, 0.25f, 1.25f,
        -0.75f, 0.25f, 1.25f, //342
        0.5f,-0.5f, 1.0f,

        0.75f, 0.25f, 1.25f,
        0.5f,-0.5f,-1.0f, //P386
        1.0f, 0.5f,-1.25f,
//        0.0, 0.5, -1.5,


        0.5f,-0.5f,-1.0f,
        0.75f, 0.25f, 1.25f, //832
        0.5f,-0.5f, 1.0f,

        0.5f,-0.5f, 1.0f,
        -0.5f,-0.5f,-1.0f, //P278
        0.5f,-0.5f,-1.0f,

        0.5f,-0.5f, 1.0f,
        -0.5f,-0.5f, 1.0f, //217
        -0.5f,-0.5f,-1.0f,
//        0.5f, 0.5f, 0.5f,
//        0.5f, 0.5f,-0.5f,  //365
//        -0.5f, 0.5f,-0.5f,

//        0.5f, 0.5f, 0.5f,
//        -0.5f, 0.5f,-0.5f, // 354
//        -0.5f, 0.5f, 0.5f,

    };
    color_t colored[2] = {COLOR_GREEN, COLOR_BLACK};
    this->object3 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data, COLOR_INDIGO, GL_FILL);
    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data+9, COLOR_ORANGE, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data+9*3, COLOR_GREEN, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data+27*3, COLOR_BLACK, GL_FILL);

}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate2    = glm::rotate((float) (this->rotation_x * M_PI / 180.0f), glm::vec3(1, 0, 0));

    //    rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));

    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate * rotate2);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);


}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    position.y += speed_y;
    if (inc){
        rotation_x+=0.05;
//        this->position.y+=0.005;
        if (rotation_x > 1.5) inc = 0;
    }
    else{
        rotation_x-=0.05;
//        this->position.y-=0.005;
        if (rotation_x < -1.5) inc = 1;
    }
//    if (rotation_x > 0.05)
    if (speed_y != 0.0){
        speed_y+=acc_y;
    }
    if (position.y < 0.0){
        speed_y = 0.0;
        position.y = 0.0;
    }
//    std::cout << position.y << '\n';
//    this->rotation += 1;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

bounding_box_t Ball::bounding_box() {
    float x = this->position.x, y = this->position.y, z = this->position.z;
    bounding_box_t bbox = { x, y, z, 2*1.0 , 2*0.5, 2*1.75};
    return bbox;
}

