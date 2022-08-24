#ifndef TIME_STEP_H
#define TIME_STEP_H

#include <GLFW/glfw3.h>

#define elapsedTimeMilliseconds(ts) (ts*1000.0f)

typedef struct {
    float time;
    float start;
    float end;
} TimeStep;

void tsStart(TimeStep* ts);
void tsEnd(TimeStep* ts);

#endif