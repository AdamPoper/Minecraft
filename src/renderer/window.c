#include "window.h"

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Window* win = (Window*)glfwGetWindowUserPointer(window);
    win->keys[key] = action != GLFW_RELEASE;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    Window* win = (Window*)glfwGetWindowUserPointer(window);
    win->mouseButtons[button] = action != GLFW_RELEASE;
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    Window* win = (Window*)glfwGetWindowUserPointer(window);
    cameraMouseMove(&win->camera, xpos, ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Window* win = (Window*)glfwGetWindowUserPointer(window);
    win->camera.fov -= yoffset;
}

int isKeyPressed(Window* window, uint32_t code)
{
    return window->keys[code];
}

int initWindow(Window* window, vec2 size, const char* title)
{
    if(!glfwInit())
    {
        printf("%s\n", "could not load glfw");
        return 0;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_SAMPLES, 4);
    window->window = glfwCreateWindow(size[0], size[1], title, NULL, NULL);
    window->size[0] = size[0];
    window->size[1] = size[1];
    if(!window->window)
    {
        printf("%s\n", "Window init failed");
        glfwTerminate();
        return 0;
    }
    glfwMakeContextCurrent(window->window);
    glfwSetFramebufferSizeCallback(window->window, framebuffer_size_callback);
    glfwSetWindowUserPointer(window->window, window);
    glfwSetKeyCallback(window->window, key_callback);
    glfwSetMouseButtonCallback(window->window, mouse_button_callback);
    glfwSetCursorPosCallback(window->window, cursor_position_callback);
    glfwSetScrollCallback(window->window, scroll_callback);
    glfwSetInputMode(window->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    initCamera(&window->camera, window->size[0], window->size[1]);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("%s\n", "Did not init glad");
        return 0;
    }
    window->setWindowBackGroundColor = &setGLClearColor;
    glEnable(GL_MULTISAMPLE); 
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, window->size[0], window->size[1]);
    for(int i = 0; i < 131; i++) {
        window->keys[i] = 0;
    }
    return 1;    
}

void setGLClearColor(vec4 color) {
    glClearColor(
        color[0], 
        color[1], 
        color[2], 
        color[3]
    );
}

void updateWindow(Window* window)
{
    glfwSwapBuffers(window->window);
    glfwPollEvents();
}

void destroyWindow(Window* window)
{
    glfwDestroyWindow(window->window);
    glfwTerminate();
}

int isWindowOpen(Window* window)
{
    return !glfwWindowShouldClose(window->window);
}
