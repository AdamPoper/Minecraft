#include "perlinNoise.h"

void genNoise(PerlinNoise* noise);

float* createSeedArray(vec2 size) {
    float* seedArray = (float*)malloc(sizeof(float) * size[0] * size[1]);
    time_t t;
    srand((unsigned)time(&t));
    for(int i = 0; i < size[0] * size[1]; i++) {
        float value = (float)(rand() % 1000);
        value /= 1000;
        seedArray[i] = value;
    }
    return seedArray;
}

void initNoise(PerlinNoise* noise, vec2 size) {
    noise->seedArray = createSeedArray(size);
    noise->outputArray = (float*)malloc(sizeof(float) * size[0] * size[1]);
    noise->size[0] = size[0];
    noise->size[1] = size[1];
    genNoise(noise);
}

void genNoise(PerlinNoise* pNoise) {
    int width =  (int)pNoise->size[0];
    int height = (int)pNoise->size[1];
    int octaves = 5;
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            float noise = 0.0f;
            float scale = 1.0f;
            float scaleAcc = 0.0f;            
            for (int o = 0; o < octaves; o++) {
                int pitch = width >> o;
                int sampleX1 = (x / pitch) * pitch;
                int sampleY1 = (y / pitch) * pitch;
                int sampleX2 = (sampleX1 + pitch) % width;
                int sampleY2 = (sampleY1 + pitch) % width;                
                float blendX = (float)(x - sampleX1) / (float)pitch;
                float blendY = (float)(y - sampleY1) / (float)pitch;                
                float linIntSampleT = (1.0f - blendX) * pNoise->seedArray[sampleY1 * width + sampleX1] + blendX * pNoise->seedArray[sampleY1 * width + sampleX2];
                float linIntSampleB = (1.0f - blendX) * pNoise->seedArray[sampleY2 * width + sampleX1] + blendX * pNoise->seedArray[sampleY2 * width + sampleX2];                
                noise += (blendY * (linIntSampleB - linIntSampleT) + linIntSampleT) * scale;                
                scaleAcc += scale;
                scale /= 0.8f;             
            }            
            pNoise->outputArray[y * width + x] = noise / scaleAcc;
        }
    }
}

void deleteNoise(PerlinNoise* pNoise) {
    free(pNoise->seedArray);
    free(pNoise->outputArray);
}

float getNoise(PerlinNoise* pNoise, int x, int y) {
    return pNoise->outputArray[
        y * (int)pNoise->size[0] + x
    ];
}

void printNoise(PerlinNoise* noise) {
    for(int x = 0; x < noise->size[0]; x++) {
        for(int y = 0; y < noise->size[1]; y++) {
            printf("%.2f ", getNoise(noise, x, y));
        }
        printf("\n");
    }
}