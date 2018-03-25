#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define NBLOCKS 200
#define NMONSTERS 50
#define NLOGS 70

void make_monster(int i, int flag);
void make_barrell(int i);
void helicopter_view(float x,  float z);
struct color_t {
    int r;
    int g;
    int b;
};

void set_cannon_pos(float x, float y);
void cursor_pos_callback(GLFWwindow* window, double xpos, double zpos);
int views_show(int viewval);
// nonedit.cpp
GLFWwindow *initGLFW(int width, int height);
GLuint     LoadShaders(const char *vertex_file_path, const char *fragment_file_path);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat *color_buffer_data, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat red, const GLfloat green, const GLfloat blue, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const color_t color, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const color_t *color, GLenum fill_mode, int flag);
void       draw3DObject(struct VAO *vao);

// input.cpp
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods);
void keyboardChar(GLFWwindow *window, unsigned int key);
void mouseButton(GLFWwindow *window, int button, int action, int mods);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// other_handlers.cpp
void error_callback(int error, const char *description);
void quit(GLFWwindow *window);
void reshapeWindow(GLFWwindow *window, int width, int height);

// Types
struct VAO {
    GLuint VertexArrayID;
    GLuint VertexBuffer;
    GLuint ColorBuffer;

    GLenum PrimitiveMode;
    GLenum FillMode;
    int    NumVertices;
};
typedef struct VAO VAO;

struct GLMatrices {
    glm::mat4 projection;
    glm::mat4 model;
    glm::mat4 view;
    GLuint    MatrixID;
};

extern GLMatrices Matrices;

// ---- Logic ----

enum direction_t { DIR_UP, DIR_RIGHT, DIR_DOWN, DIR_LEFT };

struct bounding_box_t {
    float x;
    float y;
    float z;
    float length;
    float height;
    float width;
};

bool detect_collision(bounding_box_t a, bounding_box_t b);
bool detect_jumper(bounding_box_t a, bounding_box_t b);


extern float screen_zoom, screen_center_x, screen_center_y;
void reset_screen();

// ---- Colors ----
extern const color_t COLOR_RED;
extern const color_t COLOR_RED_MAG;
extern const color_t COLOR_GREEN;
extern const color_t COLOR_YELLOW;
extern const color_t COLOR_BROWN;
extern const color_t COLOR_BLUE;
extern const color_t COLOR_GREEN_GRASS;
extern const color_t COLOR_BACKGROUND;
extern const color_t COLOR_MAROON;
extern const color_t COLOR_WHITE;
extern const color_t COLOR_SILVER;
extern const color_t COLOR_VIOLET;
extern const color_t COLOR_INDIGO;
extern const color_t COLOR_BLUE_R;
extern const color_t COLOR_GREEN_R;
extern const color_t COLOR_ORANGE;
extern const color_t COLOR_BLACK;
extern const color_t COLOR_LOG;
extern const color_t COLOR_PATCHES;

void audio_init();
void audio_play();
void audio_close();

#endif
