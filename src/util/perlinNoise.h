#ifndef NOISE_H
#define NOISE_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

typedef float vec2[2];

typedef struct {
    vec2 size;
    float* seedArray;
    float* outputArray; 
} PerlinNoise;

void initNoise(PerlinNoise* noise, vec2 size);
void deleteNoise(PerlinNoise* noise);
float getNoise(PerlinNoise* pNoise, int x, int y);

#endif