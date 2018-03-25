#include "main.h"
#include "timer.h"
#include "ball.h"
#include "cuboid.h"
#include "cannon.h"
#include "monster.h"
#include "health.h"
#include "gift.h"
#include "mast.h"
#include "barrell.h"
#include "patches.h"
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Cuboid water;
Cannon stones[10000];
Monster monster[1000];
Cannon cannon, stand, bullet;
Cannon bomb;
Health health;
Gift gift[10000];
Mast mast;
Barrell barrell[NLOGS];
Patches patches[55];
float wind[3];
int health_val = 100;
int projection = 1;
int draw_bomb = 0;
int numkills = 0;
int score = 0;
extern double drag_oldx, drag_oldy;
float angle = 0;
float screen_zoom = 1.0, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
int viewval = 0;
int numgifts = 0;
int booster = 0;
float cann_boost = 1.0;
Barrell log_booster[100];
int numboosters = 0;
double theta;
Timer t60(1.0 / 60);
float tim_check = 0.0;

float camera_eye[3], camera_target[3], camera_up[3];

/* Render the scene with openGL .*/
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
//    glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 10, 5*sin(camera_rotation_angle*M_PI/180.0f) );
//    glm::vec3 eye ( ball1.position.x, ball1.position.y + 5, ball1.position.z + 6 );
//    glm::vec3 eye (-5*cos(camera_rotation_angle*M_PI/180.0f),-5*sin(camera_rotation_angle*M_PI/180.0f),8);
//moved    glm::vec3 eye (ball1.position.x,ball1.position.y + 20,ball1.position.z+15);
//    glm::vec3 eye (ball1.position.x,ball1.position.y+0.5,ball1.position.z);
//    glm::vec3 eye (ball1.position.x + 6*sin(ball1.rotation * M_PI/180.0),ball1.position.y+1,ball1.position.z+6*cos(ball1.rotation * M_PI/180.0));
//    glm::vec3 target (ball1.position.x - 5*sin(ball1.rotation * M_PI/180.0), ball1.position.y, ball1.position.z+5*cos(ball1.rotation * M_PI/180.0));

//    //Top view
//    glm::vec3 eye (ball1.position.x, ball1.position.y + 15.0,ball1.position.z);
//    glm::vec3 target (ball1.position.x , ball1.position.y, ball1.position.z );
//    glm::vec3 up (0, 0, -1);


//    //Follow cam view
//    glm::vec3 eye (ball1.position.x + 25*sin(ball1.rotation * M_PI/180.0),15,ball1.position.z+25*cos(ball1.rotation * M_PI/180.0));
//    glm::vec3 target (ball1.position.x , ball1.position.y, ball1.position.z );
//    glm::vec3 up (0, 1,0);

    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    //boat_view
    glm::vec3 eye (camera_eye[0],camera_eye[1],camera_eye[2]);
    glm::vec3 target (camera_target[0], camera_target[1], camera_target[2]);
    glm::vec3 up (camera_up[0], camera_up[1],camera_up[2]);

    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
//    glm::vec3 up (0, 1,0);

    // Compute Camera matrix (view)
    views_show(viewval);
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    for (int i=0;i<NBLOCKS;i++) stones[i].draw(VP);
    for (int i=0;i< NMONSTERS;i++) monster[i].draw(VP);
    ball1.draw(VP);
    cannon.draw(VP);
    stand.draw(VP);
    mast.draw(VP);
    water.draw(VP);
    bullet.draw(VP);
    for (int i=0;i<numgifts ;i++) gift[i].draw(VP);
    for (int i=0;i<NLOGS;i++) barrell[i].draw(VP);
    for (int i=0;i<52;i++) patches[i].draw(VP);
    for (int i=0;i<numboosters;i++){
        if (log_booster[i].position.y < 2.0) log_booster[i].draw(VP);
    }
//    health.draw(VP);
    if (draw_bomb){
        bomb.draw(VP);
        draw_bomb = 0;
    }
}

int views_show(int viewval){
    if (viewval == 0){
        camera_eye[0] = ball1.position.x + 25*sin(ball1.rotation * M_PI/180.0);
        camera_eye[1] = 15;
        camera_eye[2] = ball1.position.z+25*cos(ball1.rotation * M_PI/180.0);

        camera_target[0] = ball1.position.x;
        camera_target[1] = ball1.position.y;
        camera_target[2] = ball1.position.z;

        camera_up[0] = 0;
        camera_up[1] = 1;
        camera_up[2] = 0;
    }
    else if (viewval == 1){
        // boat view
        camera_eye[0] = ball1.position.x- 1.75*sin(ball1.rotation * M_PI/180.0);
        camera_eye[1] = ball1.position.y+1;
        camera_eye[2] = ball1.position.z- 1.75*cos(ball1.rotation * M_PI/180.0);

        camera_target[0] = ball1.position.x - 10*sin(ball1.rotation * M_PI/180.0);
        camera_target[1] = ball1.position.y+1;
        camera_target[2] = ball1.position.z - 10*cos(ball1.rotation * M_PI/180.0);

        if (projection == 1) camera_eye[1] = ball1.position.y, camera_target[1] = ball1.position.y-1;
        camera_up[0] = 0;
        camera_up[1] = 1;
        camera_up[2] = 0;
    }
    else if (viewval == 2){
        // top-view
//        if (projection == 1){
        camera_eye[0] = ball1.position.x;
        camera_eye[1] = ball1.position.y + 10;
        camera_eye[2] = ball1.position.z;

        camera_target[0] = ball1.position.x;
        camera_target[1] = ball1.position.y;
        camera_target[2] = ball1.position.z;

        camera_up[0] = 0;
        camera_up[1] = 0;
        camera_up[2] = -1;
    }
    else if (viewval == 3){
        // tower view
//        if (projection == 1){
        camera_eye[0] = ball1.position.x;
        camera_eye[1] = 20;
        camera_eye[2] = ball1.position.z+15;
//        }
//        else{
//            camera_eye[0] = ball1.position.x+75;
//            camera_eye[1] = 20;
//            camera_eye[2] = ball1.position.z+15;
//        }
        camera_target[0] = ball1.position.x;
        camera_target[1] = ball1.position.y;
        camera_target[2] = ball1.position.z;

        camera_up[0] = 0;
        camera_up[1] = 1;
        camera_up[2] = 0;
    }

}

void helicopter_view(float x,  float z){
    if (viewval == 4){
        camera_eye[0] = ball1.position.x;
        camera_eye[1] = 55;
        camera_eye[2] = ball1.position.z+50;

        camera_target[0] = ball1.position.x+ (x-300)/300 * 50;
        camera_target[1] = ball1.position.y;
        camera_target[2] = ball1.position.z+ (z-300)/300 * 50;

        camera_up[0] = 0;
        camera_up[1] = 1;
        camera_up[2] = 0;
    }
}

void set_cannon_pos(float x, float z){
    cannon.rotation_y = ball1.rotation-(x - 300)*180/300;
    cannon.rotation = (z-300) * 90/300;

}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int one = glfwGetKey(window, GLFW_KEY_1);
    int two = glfwGetKey(window, GLFW_KEY_2);
    int three = glfwGetKey(window, GLFW_KEY_3);
    int four = glfwGetKey(window, GLFW_KEY_4);
    int five = glfwGetKey(window, GLFW_KEY_5);
    int F =  glfwGetKey(window, GLFW_KEY_F);
    int P = glfwGetKey(window, GLFW_KEY_P);
    int O = glfwGetKey(window, GLFW_KEY_O);
    if (O) projection = 1, reset_screen();
    if (P) projection = 0, reset_screen();
    if (one) viewval = 0;
    if (two) viewval = 1;
    if (three) viewval = 2;
    if (four) viewval = 3;
    if (five) viewval = 4;
    if (left) {
        ball1.rotation+=2;
        cannon.rotation_y+=2;
//        mast.rotation-=3;
        // Do something
    }
    if (right) {
        ball1.rotation-=2;
        cannon.rotation_y-=2;
//        mast.rotation+=3;
    }
    int val = (180+360+360+ball1.rotation)%360;
//    cerr << val << " " << mast.rotation << "\n";
    int diff = val - mast.rotation;
    if (diff > 0){
        if (diff < (360-diff)) mast.rotation=(mast.rotation+1+360)%360;
        else mast.rotation=(mast.rotation-1+360)%360;
    }
    else if(diff < 0){
        int v = mast.rotation - val;
        if (v < (360-v)) mast.rotation=(mast.rotation-1+360)%360;
        else mast.rotation=(mast.rotation+1+360)%360;
    }

//    if (mast.rotation < val){
//            mast.rotation=(mast.rotation+1+360)%360;
//    }
//    else{
//            mast.rotation=(mast.rotation-1+360)%360;

//    }
//    if (abs(val) != 180){
//        if (val > 0) mast.rotation-=1;
//        else mast.rotation+=1;

//    }
//    fprintf(stderr,"ball1: %d  mast: %d\n", (ball1.rotation+360)%360, mast.rotation%360);
    if (up) {
        ball1.position.z-=0.1*cos(ball1.rotation * M_PI/180.0);
        ball1.position.x-=0.1*sin(ball1.rotation * M_PI/180.0);

    }
    if (down) {
        ball1.position.z+=0.1*cos(ball1.rotation * M_PI/180.0);
        ball1.position.x+=0.1*sin(ball1.rotation * M_PI/180.0);
    }
    if (space && ball1.speed_y == 0.0) {
        ball1.speed_y = 0.30;
    }
    if (F && bullet.position.y == ball1.position.y) {
        bullet.speed = 0.2 * cos(cannon.rotation*M_PI/180) ;
        bullet.bullet_speed_x = 0.2 * -sin(cannon.rotation*M_PI/180) * -sin(cannon.rotation_y*M_PI/180) ;
        bullet.bullet_speed_z = 0.2 * sin(cannon.rotation*M_PI/180) * cos(cannon.rotation_y*M_PI/180) ;
    }
    if (bullet.speed != 0){
        bullet.speed-=0.003;
    }
    if (bullet.position.y < -(0.5)){
        bullet.speed = bullet.bullet_speed_x = bullet.bullet_speed_z = 0.0;
        bomb = Cannon(bullet.position.x, -0.5, bullet.position.z, COLOR_RED, 2.5, 2.5, 0, 1);
        draw_bomb = 1;
    }
//    if (this->position.y <= )
    if (wind[2]){
        ball1.position.z-=0.01*cos(theta);
        ball1.position.x-=0.01*sin(theta);
    }
    for(int i=0;i<52;i++){
        if (wind[2]){
            patches[i].position.z-=0.05*cos(theta);
            patches[i].position.x-=0.05*sin(theta);
        }
//        if (patches[i].position.x < -100.0) patches[i].position.x = 100.0;
//        if (patches[i].position.x > 100.0) patches[i].position.x = -100.0;
//        if (patches[i].position.z < -100.0) patches[i].position.y = 100.0;
//        if (patches[i].position.z > 100.0) patches[i].position.y = -100.0;


    }
    for (int i=0;i<numboosters;i++){
        if (log_booster[i].position.y < 2.0){
            if (detect_collision(log_booster[i].bounding_box(), ball1.bounding_box())){
                log_booster[i].position.y = 1000.0;
                score+=1000;
                health_val+=100;
            }
        }
    }
    for (int i=0;i<NBLOCKS;i++){
        if (detect_collision(ball1.bounding_box(), stones[i].bounding_box())){
            health_val-=1;
            if(health_val < 0) exit(0);
            ball1.position.z+=0.35*cos(ball1.rotation * M_PI/180.0);
            ball1.position.x+=0.35*sin(ball1.rotation * M_PI/180.0);
            if (detect_collision(ball1.bounding_box(), stones[i].bounding_box())){
                ball1.position.z-=2*0.35*cos(ball1.rotation * M_PI/180.0);
                ball1.position.x-=2*0.35*sin(ball1.rotation * M_PI/180.0);
            }
//            std::cerr  << "Detected\n" << health_val << "\n";
        }
    }
    for(int i=0;i<numgifts ;i++){
        if (detect_collision(ball1.bounding_box() , gift[i].bounding_box())){
            health_val+=15;
            gift[i].position.y = 10000.0;
            gift[i].flag = 0;
        }
    }
    for(int i=0;i<NLOGS;i++){
        bounding_box_t a = barrell[i].bounding_box();
        bounding_box_t b = ball1.bounding_box();
        bounding_box_t c = barrell[i].jump_bounding_box();
//        if(detect_collision(a,b) || detect_collision(b,c)) std::cerr << detect_collision(a,b) << " " << detect_collision(b,c) << "\n";
        if(!detect_collision(a,b) && detect_collision(b,c)){
            gift[numgifts].flag = 1;
            gift[numgifts++] = Gift(barrell[i].position.x, barrell[i].position.y, barrell[i].position.z, 0.25);
            make_barrell(i);
        }
    }
    for (int i=0;i< NMONSTERS;i++){
        float dis_y = monster[i].position.z - ball1.position.z;
        float dis_x = monster[i].position.x - ball1.position.x;
        int fl1 = 1, fl2 = 1;
        if (dis_x > 0.0) fl1 = -1;
        if (dis_y > 0.0) fl2 = -1;color_t colored[7] = {COLOR_VIOLET, COLOR_INDIGO, COLOR_BLUE_R, COLOR_GREEN_R, COLOR_YELLOW, COLOR_ORANGE, COLOR_RED_MAG};
        if (detect_collision(ball1.bounding_box(), monster[i].bounding_box())){
            score-=50;
            health_val-=3;
            if (health_val < 0) exit(0);
            ball1.position.z+=0.55*cos(ball1.rotation * M_PI/180.0);
            ball1.position.x+=0.5*sin(ball1.rotation * M_PI/180.0);
            if (detect_collision(ball1.bounding_box(), stones[i].bounding_box())){
                ball1.position.z-=2*0.55*cos(ball1.rotation * M_PI/180.0);
                ball1.position.x-=2*0.55*sin(ball1.rotation * M_PI/180.0);
            }

//            std::cerr  << "Detected\n" << health_val << "\n";
        }
        if (draw_bomb && detect_collision(bomb.bounding_box(), monster[i].bounding_box())){
            score+=35;
            monster[i].health--;
            if (cann_boost==2.0) monster[i].health--;
            if (monster[i].health < 0){
                score+=100;
                numkills++;
                if (monster[i].flag==0){
                    gift[numgifts].flag = 1;
                    gift[numgifts++] = Gift(monster[i].position.x, monster[i].position.y, monster[i].position.z, 0.25);
                }
                else {
                    tim_check = 3000;
                    cann_boost = 2.0;
                    log_booster[numboosters++] = Barrell(monster[i].position.x, monster[i].position.y, monster[i].position.z, 0.25, COLOR_INDIGO);
                }
                if (numkills == 5){
                    make_monster(i,1);
                    numkills = 0;
                }
                else make_monster(i,0);
            }
            else monster[i] = Monster(monster[i].position.x, monster[i].position.y, monster[i].position.z, monster[i].health, 0.5, 0.5, monster[i].scale_val, monster[i].flag);
        }
        if(((fabs(dis_x) > 12.0 || fabs(dis_y) > 12.0) && i%12 ==1) || (i%36==1 && (fabs(dis_x) > 5.0 || fabs(dis_y) > 5.0))){
            float  tan = fabs(dis_x)/fabs(dis_y);
            double theta = atan(tan);
            monster[i].monster_speed_z = fl2 * 0.08 * cos(theta);
            monster[i].monster_speed_x = fl1 * 0.08 * sin(theta);
        }
        else{
            int k = rand()%2, r= rand()%2;
            if (!k) k--;
            if (!r) r--;
            monster[i].monster_speed_z = k*(double)rand()/(double)RAND_MAX * 0.04;
            monster[i].monster_speed_x = r*(double)rand()/(double)RAND_MAX * 0.04;
        }
    }


//    int mouse_clicked = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
//    if (mouse_clicked) {
//        if (drag_oldx == -1 && drag_oldy == -1) {
//            glfwGetCursorPos(window, &drag_oldx, &drag_oldy);
//        }
//        else {
//            int w, h;
//            double new_x, new_y;
//            glfwGetCursorPos(window, &new_x, &new_y);
//            glfwGetWindowSize(window, &w, &h);
//            float pos_x, pos_y;
//            pos_x = 8 * (new_x - drag_oldx) / (w * screen_zoom);
//            if((new_x - drag_oldx > 0)){
//                angle+= (new_x - drag_oldx)*0.05;
//                if (angle > ball1.rotation + 70) angle = ball1.rotation + 70;
//           }
//            else{
//                angle+= (new_x - drag_oldx)*0.05;
//                if (angle < ball1.rotation-70) angle = ball1.rotation-70;
//            }
//            // drag_oldx = new_x;
//            // drag_oldy = new_y;
//        }
//    }
//    views_show(viewval);
    mast.position.x = water.position.x = cannon.position.x = stand.position.x = ball1.position.x;
    mast.position.y = cannon.position.y = stand.position.y = ball1.position.y;
    mast.position.z = water.position.z = cannon.position.z = stand.position.z = ball1.position.z;
    if (bullet.speed == 0.0){
        bullet.position.x = ball1.position.x;
        bullet.position.y = ball1.position.y;
        bullet.position.z = ball1.position.z;
    }
}

void tick_elements() {
    ball1.tick();
    water.tick();
    cannon.tick();
    bullet.tick();
    for(int i=0;i<NMONSTERS;i++) monster[i].tick();
    for(int i=0;i<52;i++) patches[i].tick();
}

void make_monster(int i, int flag){
    int coord_x = rand()%150;
    int coord_z = rand()%150;
    if (coord_x & 01) coord_x*=(-1);
    if (coord_z & 01) coord_z*=(-1);
    int scale_val = rand()%3+2;
    if (!flag) monster[i] = Monster(coord_x, -0.25, coord_z, scale_val-2, 0.5, 0.5, scale_val, flag);
    else monster[i] = Monster(coord_x, -0.25, coord_z, 6, 0.5, 0.5, scale_val, flag);
}

void make_barrell(int i){
    int coord_x = rand()%150;
    int coord_z = rand()%150;
    if (coord_x & 01) coord_x*=(-1);
    if (coord_z & 01) coord_z*=(-1);
    barrell[i] = Barrell(coord_x, 0, coord_z, 1, COLOR_LOG);
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    water       = Cuboid(0, -300.6, 0.0, COLOR_BLUE_R, 300.0, 300.0);
    int k=0;
//    for (int i=-100.0;i<=100;i+=8){
//        for (int j=(-100);j<=100;j+=8){
//            stones[k++] = Cannon(i, -0.25, j, COLOR_BROWN, 0.5, 0.5, 0, .0);
//        }
//    }
    for (int i=0;i<NBLOCKS;i++){
        int coord_x = rand()%150;
        int coord_z = rand()%150;
        if (coord_x & 01) coord_x*=(-1);
        if (coord_z & 01) coord_z*=(-1);
        int scale_val = rand()%3 + 3;
        stones[k++] = Cannon(coord_x, -0.25, coord_z, COLOR_BROWN, 0.25, 0.25, 0, scale_val);
    }
    k=0;
    for (int i=0;i<NMONSTERS;i++){
        make_monster(i, 0);
    }
    for(int i=0;i<NLOGS;i++){
        make_barrell(i);
    }
    for (int i=0;i < 52;i++){
        int coord_x = rand()%150;
        int coord_z = rand()%150;
        if (coord_x & 01) coord_x*=(-1);
        if (coord_z & 01) coord_z*=(-1);
        patches[i] = Patches(coord_x, -0.52, coord_z, COLOR_PATCHES, 0);
    }
    ball1       = Ball(0, 0, COLOR_RED);
    cannon    = Cannon(-2.5,0,-1.25, COLOR_GREEN_GRASS, 1.2, 0.05,  1, 1.0);
    stand    = Cannon(-2.5,0,-1.25, COLOR_MAROON, 2.5, 0.03, 0, 1.0);
    bullet = Cannon(-2.5,0,1.25, COLOR_SILVER, 0.2, 0.05, 0, 1.0);
    health = Health(5,2,health_val);
    mast = Mast(1);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);
    char outsc[1000]={'\0'};
    int counter = 400;
    int fl;
    /* Draw in loop */
	//audio_init();
    while (!glfwWindowShouldClose(window)) {
        // Process timers
        //audio_play();
        if (t60.processTick()) {
            // 60 fps
//            for(int i=0;i<15;i++) outsc[i++] = '\0';
            sprintf(outsc,"health: %d score: %d time_cannon_booster: %f", health_val, score, tim_check);
            glfwSetWindowTitle(window,outsc);
            counter--;
            if (counter == 0){
                wind[0] = (double)rand()/RAND_MAX;
                wind[1] = (double)rand()/RAND_MAX;
                theta = atan(wind[0]/wind[1]);
                wind[2] = 1;
                fl = rand()%2;
                if (!fl) fl--;
                theta*=fl;
            }
            if (wind[2]==1){
                mast.rotation = theta * 180.0/ M_PI;
//                std::cerr << ball1.rotation*M_PI/180.0 << " " << theta << "\n";
            }
            if (counter == (-200)){
                counter = rand()%300 + 200;
                wind[2] = 0;
            }
            if (tim_check > 0.0){
                tim_check--;
            }
            if (tim_check==0.0) cann_boost = 1.0;
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.length + b.length)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height)) &&
           (abs(a.z - b.z) * 2 < (a.width + b.width));
}

bool detect_jumper(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.length + b.length)) &&
           (abs(a.z - b.z) * 2 < (a.width + b.width));
}

void reset_screen() {
    float top    = screen_center_y + 10 / screen_zoom;
    float bottom = screen_center_y - 10 / screen_zoom;
    float left   = screen_center_x - 10 / screen_zoom;
    float right  = screen_center_x + 10 / screen_zoom;
    if (projection) Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
    else Matrices.projection = glm::perspective(45.0f,1.0f,2.0f, 500.0f);

}
