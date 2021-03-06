#include "patches.h"
#include "main.h"

Patches::Patches(float x, float y, float z, color_t color, int flag) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    this->inc = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[8*9*2];
    float ang = M_PI/4.0;
    float curr = ang/2.0;
    int k=0;
    for(int i=1;i<=8;i++){
        vertex_buffer_data[k++] = 1.0*cos(curr);
        vertex_buffer_data[k++] = 0.0;
        vertex_buffer_data[k++] = 1.0*sin(curr);


        vertex_buffer_data[k++] = 0.0;
        vertex_buffer_data[k++] = 0.0;
        vertex_buffer_data[k++] = 0.0;


        vertex_buffer_data[k++] = 1.0*cos(curr+ang);
        vertex_buffer_data[k++] = 0.0;
        vertex_buffer_data[k++] = 1.0*sin(curr+ang);
        curr+=ang;
    }
    ang = M_PI/4.0;
    curr = ang/2.0;
    for(int i=1;i<=8;i++){
        vertex_buffer_data[k++] = 0.5*cos(curr);
        vertex_buffer_data[k++] = 0.01;
        vertex_buffer_data[k++] = 0.5*sin(curr);


        vertex_buffer_data[k++] = 0.0;
        vertex_buffer_data[k++] = 0.01;
        vertex_buffer_data[k++] = 0.0;


        vertex_buffer_data[k++] = 0.5*cos(curr+ang);
        vertex_buffer_data[k++] = 0.01;
        vertex_buffer_data[k++] = 0.5*sin(curr+ang);
        curr+=ang;
    }


    this->object[0] = create3DObject(GL_TRIANGLES, 8*3, vertex_buffer_data, color, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 8*3, vertex_buffer_data+24*3, COLOR_BLUE_R, GL_FILL);

}

void Patches::draw(glm::mat4 VP) {
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

}

void Patches::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Patches::tick() {
    if (inc){
        rotation+=0.05;
//        this->position.y+=0.005;
        if (rotation > 1.5) inc = 0;
    }
    else{
        rotation-=0.05;
//        this->position.y-=0.005;
        if (rotation < -1.5) inc = 1;
    }

//    this->rotation += 1;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

//bounding_box_t Patches::bounding_box() {
//    float x = this->position.x, y = this->position.y;  float z = this->position.z;
//    bounding_box_t bbox = { x, y, z, 0.7, 2*this->0.0, 0.7};
//    return bbox;
//}

//bounding_box_t Patches::jump_bounding_box() {
//    float x = this->position.x, y = this->position.y;  float z = this->position.z;
//    bounding_box_t bbox = { x, y, z, 0.7, 45.0, 0.7};
//    return bbox;
//}
