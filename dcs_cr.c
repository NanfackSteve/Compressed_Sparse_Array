#include "dcs_cr.h"
#include <stdlib.h>
#include <stdio.h>

//------------------ Double Compressed Sparse Column ----------------------

DCSC doubleCSC(float M[][NUM_COL_D])
{
    //  Variables de boucles
    int i, j, k = 0, l = 1;
    // // Nbre de colones non-nulle de M
    nncz(M);

    // // Allocation de la memoire
    DCSC dcsc;
    dcsc.A = malloc(sizeof(float) * NNZ_D);
    dcsc.IA = malloc(sizeof(int) * NNZ_D);
    dcsc.JA = malloc(sizeof(int) * (NNCZ + 1));
    dcsc.JC = malloc(sizeof(int) * (NNCZ - 1)); // -1 car malloc ajoute +1
    dcsc.JA[0] = 0;

    // Remplissage de A et IA
    for (j = 0; j < NUM_COL_D; j++)
    {
        for (i = 0; i < NUM_ROW_D; i++)
        {
            if (M[i][j] != 0)
            {
                dcsc.A[k] = M[i][j];
                dcsc.IA[k] = i;
                k++;
            }
        }
    }

    // Calcul de JA et JC
    k = 0;
    for (j = 1; j <= NUM_COL_D; j++)
    {
        if (dcsc_nnc(j - 1, M) != 0)
        {
            dcsc.JA[l] = dcsc.JA[l - 1] + dcsc_nnc((j - 1), M);
            dcsc.JC[k] = j - 1;
            k++;
            l++;
        }
    }

    return dcsc;
}

int dcsc_nnc(int col, float m[][NUM_COL_D])
{ // Cette fonction retourne le nobre d'elt non-nul d'une colone - col

    int i = 0, n = 0;

    // Compte le nbre d'elemnt non-nul de row
    for (i = 0; i < NUM_ROW_D; i++)
    {
        if (m[i][col] != 0)
            n++;
    }

    return n;
}

void printDCSC(DCSC dcsc)
{
    printf("\n------------------- DCSC ---------------------\n");

    // Affichage de JC
    printf("\nJC = [ ");
    for (int i = 0; i < NNCZ; i++)
        printf(" %d ", dcsc.JC[i]);
    printf(" ]\n");

    // Affiche JA
    printf("\nJA = [ ");
    for (int j = 0; j <= NNCZ; j++)
        printf(" %d ", dcsc.JA[j]);
    printf(" ]\n\n");

    // Affiche IA
    printf("IA = [ ");
    for (int i = 0; i < NNZ_D; i++)
        printf(" %d ", dcsc.IA[i]);
    printf(" ]\n");

    // Affiche VA
    printf("\nVA = [ ");
    for (int i = 0; i < NNZ_D; i++)
        printf(" %.1f ", dcsc.A[i]);
    printf(" ]\n\n");
}

void freeMemoryDCSC(DCSC dcsc)
{
    free(dcsc.A);
    free(dcsc.IA);
    free(dcsc.JA);
    free(dcsc.JC);
}

void nncz(float M[][NUM_COL_D])
{ // Cette fonction donne le nbre de colones non-nulles
    int j, m = 0;

    for (j = 0; j < NUM_COL_D; j++)
        if (dcsc_nnc(j, M) != 0)
            m++;

    NNCZ = m;
}

//------------------ Double Compressed Sparse Row ----------------------

DCSR doubleCSR(float M[][NUM_COL_D])
{
    //  Variables de boucles
    int i, j, k = 0, l = 1;
    // // Nbre de ligne non-nulle de M
    nnrz(M);

    // // Allocation de la memoire
    DCSR dcsr;
    dcsr.A = malloc(sizeof(float) * NNZ_D);
    dcsr.JA = malloc(sizeof(int) * NNZ_D);
    dcsr.IR = malloc(sizeof(int) * (NNRZ - 1)); // -1 car malloc ajoute +1
    dcsr.IA = malloc(sizeof(int) * (NNRZ + 1));
    dcsr.IA[0] = 0;

    // // Remplissage de A et JA
    for (i = 0; i < NUM_ROW_D; i++)
    {
        for (j = 0; j < NUM_COL_D; j++)
        {
            if (M[i][j] != 0)
            {
                dcsr.A[k] = M[i][j];
                dcsr.JA[k] = j;
                k++;
            }
        }
    }

    // Calcul de IA et IR
    k = 0;
    for (i = 1; i <= NUM_ROW_D; i++)
    {
        if (dcsr_nnr(i - 1, M) != 0)
        {
            dcsr.IA[l] = dcsr.IA[l - 1] + dcsr_nnr((i - 1), M);
            dcsr.IR[k] = i - 1;
            k++;
            l++;
        }
    }

    return dcsr;
}

int dcsr_nnr(int row, float m[][NUM_COL_D])
{ // Cette fonction retourne le nobre d'elt non-nul d'une ligne - row

    int j = 0, n = 0;

    // Compte le nbre d'elemnt non-nul de row
    for (j = 0; j < NUM_COL_D; j++)
    {
        if (m[row][j] != 0)
            n++;
    }

    return n;
}

void printDCSR(DCSR dcsr)
{
    int i = 0;

    printf("\n---------------- Double CSR ------------------\n");

    // Affichage de IR
    printf("\nIR = [ ");
    for (int i = 0; i < NNRZ; i++)
        printf(" %d ", dcsr.IR[i]);
    printf(" ]\n");

    // Affiche IA
    printf("\nIA = [ ");
    for (int i = 0; i <= NNRZ; i++)
        printf(" %d ", dcsr.IA[i]);
    printf(" ]\n");

    // Affiche JA
    printf("\nJA = [ ");
    for (int i = 0; i < NNZ_D; i++)
        printf(" %d ", dcsr.JA[i]);
    printf(" ]\n");

    // Affiche VA
    printf("\nVA = [ ");
    for (int i = 0; i < NNZ_D; i++)
        printf(" %.1f ", dcsr.A[i]);
    printf(" ]\n\n");
}

void freeMemoryDCSR(DCSR dcsr)
{
    free(dcsr.A);
    free(dcsr.IA);
    free(dcsr.JA);
    free(dcsr.IR);
}

void nnrz(float M[][NUM_COL_D])
{ // Cette fonction donne le nbre de ligne non-nulles
    int i, m = 0;

    for (i = 0; i < NUM_ROW_D; i++)
        if (dcsr_nnr(i, M) != 0)
            m++;

    NNRZ = m;
}
