#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "cglm/vec2.h"
#include "camera.h"

#define MAX_KEYS 512
#define MAX_MOUSE_BUTTONS 32

typedef struct {
    GLFWwindow* window;
    const char* title;
    vec2 size;
    vec2 mousePos;
    Camera camera;
    int keys[MAX_KEYS];
    int mouseButtons[MAX_MOUSE_BUTTONS];
    void (*setWindowBackGroundColor)();
} Window;

int initWindow(Window* window, vec2 size, const char* title);
void updateWindow(Window* window);
void destroyWindow(Window* window);
int isWindowOpen(Window* window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow*  window, int button, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
int isMouseButtonPressed(uint32_t buttcode);
int isKeyPressed(Window* window, uint32_t keycode); 
void setGLClearColor(vec4 color);

#endif