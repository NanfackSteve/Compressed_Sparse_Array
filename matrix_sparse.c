#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cs_cr.h"
#include "dcs_cr.h"
#include "graphC2.h"

int nnr(int row, float m[NUM_ROW][NUM_COL]);
void nnz(float m[NUM_ROW][NUM_COL]);

int main(int argc, char *argv[])
{
    // float M[4][4] = {
    //     {0.0, 0.0, 0.0, 0.0},
    //     {5.0, 8.0, 0.0, 0.0},
    //     {0.0, 0.0, 3.0, 0.0},
    //     {0.0, 6.0, 0.0, 0.0}};

    // float M[4][6] = {
    //     {10, 20, 0, 0, 0, 0},
    //     {0, 30, 0, 40, 0, 0},
    //     {0, 0, 50, 60, 70, 0},
    //     {0, 0, 0, 0, 0, 80}};

    float M[6][6] = {
        {0, 0, 0, 0, 0, 0},
        {0, 0.1, 0, 0.2, 0.4, 0},
        {0, 0, 0, 0.3, 0.5, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0.9, 0, 0, 0, 0},
        {0, 0.3, 0, 0, 0.8, 0}};

    NUM_ROW = 6;
    NUM_COL = 6;

    NUM_ROW_D = 6;
    NUM_COL_D = 6;

    NUM_ROW_G = 6;
    NUM_COL_G = 6;

    // Calcul du nbre d'elt Non-nul de M
    nnz(M);

    // Compression de la Matrice
    CSR mycsr = compress_SR(M);
    DCSR mydcsr = doubleCSR(M);
    GaFC2T2 *mygafc2t2 = graphCompress(M);
    CSC mycsc = compress_SC(M);
    DCSC mydcsc = doubleCSC(M);

    // Affichage CSR, DCSR, GaFC2T2, CSC, DCSC
    printCSR(mycsr);
    printDCSR(mydcsr);
    printGaFC2T2(mygafc2t2);
    printCSC(mycsc);
    printDCSC(mydcsc);

    // Liberation des memoires
    freeMemoryCSR(mycsr);
    freeMemoryDCSR(mydcsr);
    free(mygafc2t2);
    freeMemoryCSC(mycsc);
    freeMemoryDCSC(mydcsc);

    return 0;
}

void nnz(float m[NUM_ROW][NUM_COL])
{ // Cette fonction retourne le Nbre d'elt non-nul d'une matrice m

    int i, j, n = 0;

    for (i = 0; i < NUM_ROW; i++)
    {
        for (j = 0; j < NUM_COL; j++)
            if (m[i][j] != 0)
                n++;
    }

    NNZ = n;
    NNZ_D = n;
    NNZ_G = n;
}
