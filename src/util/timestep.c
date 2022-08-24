#include "timestep.h"

void tsStart(TimeStep* ts) {
    ts->start = (float)glfwGetTime();
}

void tsEnd(TimeStep* ts) {
    ts->end = (float)glfwGetTime();
    ts->time = ts->end - ts->start;
}