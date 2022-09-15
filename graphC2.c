#include <stdio.h>
#include <stdlib.h>
#include "graphC2.h"

GaFC2T2 *graphCompress(float M[][NUM_COL_G])
{
    // Allocationnde memoire
    GaFC2T2 *grafc2t2;
    grafc2t2 = malloc(sizeof(GaFC2T2) * NNZ_G);

    // Variables de boucles
    int i, j, k = 0;

    // Remplissage de row col et val
    for (i = 0; i < NUM_ROW_G; i++)
    {
        for (j = 0; j < NUM_COL_G; j++)
        {
            if (M[i][j] != 0)
            {
                grafc2t2[k].row = i;
                grafc2t2[k].col = j;
                grafc2t2[k].val = M[i][j];
                k++;
            }
        }
    }

    return grafc2t2;
}

void printGaFC2T2(GaFC2T2 *G)
{
    int i = 0;

    printf("\n--------------------- GaFC2T2 -----------------------\n\n");
    for (i = 0; i < NNZ_G; i++)
        printf("[ %d, %d, %.1f ]  ", G[i].row, G[i].col, G[i].val);

    printf("\n\n");
}