#ifndef NOISE_H
#define NOISE_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <cglm/vec2.h>

typedef struct {
    vec2 size;
    float* seedArray;
    float* outputArray; 
} PerlinNoise;

void initNoise(PerlinNoise* noise, vec2 size);
void deleteNoise(PerlinNoise* noise);
float getNoise(PerlinNoise* noise, int x, int y);
void printNoise(PerlinNoise* noise);
#endif