#include "cs_cr.h"
#include <stdlib.h>
#include <stdio.h>

CSC compress_SC(float M[][NUM_COL])
{
    // Variables de boucles
    int i, j, k = 0;

    // Allocation de la memoire
    CSC csc;
    csc.A = malloc(sizeof(float) * (NNZ - 1)); // -1 car malloc ajoute +1
    csc.IA = malloc(sizeof(int) * (NNZ - 1));  // -1 car malloc ajoute +1
    csc.JA = malloc(sizeof(int) * (NUM_COL + 1));
    csc.JA[0] = 0;

    // Remplissage de A et IA
    for (j = 0; j < NUM_COL; j++)
    {
        for (i = 0; i < NUM_ROW; i++)
        {
            if (M[i][j] != 0)
            {
                csc.A[k] = M[i][j];
                csc.IA[k] = i;
                k++;
            }
        }
    }

    // Calcul de JA
    for (j = 1; j <= NUM_COL; j++)
    {
        csc.JA[j] = csc.JA[j - 1] + csc_nnc((j - 1), M);
    }

    return csc;
}

int csc_nnc(int col, float m[][NUM_COL])
{ // Cette fonction retourne le nobre d'elt non-nul d'une ligne col

    int i = 0, n = 0;

    // Compte le nbre d'elemnt non-nul de col
    for (i = 0; i < NUM_ROW; i++)
    {
        if (m[i][col] != 0)
            n++;
    }

    return n;
}

void printCSC(CSC csc)
{
    printf("\n------------------- CSC ---------------------\n");

    // Affiche JA
    printf("\nJA = [ ");
    for (int j = 0; j <= NUM_COL; j++)
        printf(" %d ", csc.JA[j]);
    printf(" ]\n\n");

    // Affiche IA
    printf("IA = [ ");
    for (int i = 0; i < NNZ; i++)
        printf(" %d ", csc.IA[i]);
    printf(" ]\n");

    // Affiche VA
    printf("\nVA = [ ");
    for (int i = 0; i < NNZ; i++)
        printf(" %.1f ", csc.A[i]);
    printf(" ]\n\n");
}

void freeMemoryCSC(CSC csc)
{
    free(csc.A);
    free(csc.IA);
    free(csc.JA);
}

//--------------------------- CSR -------------------------------------

CSR compress_SR(float M[][NUM_COL])
{
    // Variables de boucles
    int i, j, k = 0;

    // Allocation de la memoire
    CSR csr;
    csr.A = malloc(sizeof(float) * (NNZ - 1)); // -1 car malloc ajoute +1
    csr.JA = malloc(sizeof(int) * (NNZ - 1));  // -1 car malloc ajoute +1
    csr.IA = malloc(sizeof(int) * (NUM_ROW + 1));
    csr.IA[0] = 0;

    // Remplissage de A et JA
    for (i = 0; i < NUM_ROW; i++)
    {
        for (j = 0; j < NUM_COL; j++)
        {
            if (M[i][j] != 0)
            {
                csr.A[k] = M[i][j];
                csr.JA[k] = j;
                k++;
            }
        }
    }

    // Calcul de IA
    for (i = 1; i <= NUM_ROW; i++)
    {
        csr.IA[i] = csr.IA[i - 1] + csr_nnr(i - 1, M);
    }

    return csr;
}

int csr_nnr(int row, float m[][NUM_COL])
{ // Cette fonction retourne le nobre d'elt non-nul d'une ligne row

    int j = 0, n = 0;

    // Compte le nbre d'elemnt non-nul de row
    for (j = 0; j < NUM_COL; j++)
    {
        if (m[row][j] != 0)
            n++;
    }

    return n;
}

void printCSR(CSR csr)
{
    printf("\n------------------- CSR ---------------------\n");
    int i = 0;

    // Affiche IA
    printf("\nIA = [ ");
    for (i = 0; i <= NUM_ROW; i++)
        printf(" %d ", csr.IA[i]);
    printf(" ]\n\n");

    // Affiche JA
    printf("JA = [ ");
    for (i = 0; i < NNZ; i++)
        printf(" %d ", csr.JA[i]);
    printf(" ]\n");

    // Affiche VA
    printf("\nVA = [ ");
    for (i = 0; i < NNZ; i++)
        printf(" %.1f ", csr.A[i]);
    printf(" ]\n\n");
}

void freeMemoryCSR(CSR csr)
{
    free(csr.A);
    free(csr.IA);
    free(csr.JA);
}