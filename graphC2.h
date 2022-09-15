#ifndef GRAPHC2_H
#define GRAPHC2_H

typedef struct
{
    int row;
    int col;
    float val;
} GaFC2T2;

int NUM_ROW_G;
int NUM_COL_G;
int NNZ_G;

GaFC2T2 *graphCompress(float M[][NUM_COL_G]);
void printGaFC2T2(GaFC2T2 *G);

#endif