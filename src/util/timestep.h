#include <GLFW/glfw3.h>

#define elapsedTimeMilliseconds(ts) (ts*1000.0f)

typedef struct
{
    float time;
    float start;
    float end;
} TimeStep;

void tsStart(TimeStep* ts)
{
    ts->start = (float)glfwGetTime();
}

void tsEnd(TimeStep* ts)
{
    ts->end = (float)glfwGetTime();
    ts->time = ts->end - ts->start;
}