#ifndef DCSR_H
#define DCSR_H

typedef struct
{
    float *A; // Vecteur des elts non-nuls
    int *IA;  //
    int *JA;  // Vecteur des indices des col non-nulles
    int *IR;
} DCSR;

typedef struct
{
    float *A; // Vecteur des elts non-nuls
    int *IA;  // Vecteur des indices des lignes non-nulles
    int *JA;  //
    int *JC;  //
} DCSC;

int NUM_ROW_D; // Nbre de Lign de M
int NUM_COL_D; // nbre de Col de M
int NNZ_D;     // Nbre d'elt Non-nul de M
int NNRZ;      // Nbre de ligne Non-nulle de M
int NNCZ;      // Nbre de Colones Non-nulle de M

DCSR doubleCSR(float M[][NUM_COL_D]);
int dcsr_nnr(int row, float m[][NUM_COL_D]);
void printDCSR(DCSR csr);
void freeMemoryDCSR(DCSR dcsr);
void nnrz(float M[][NUM_COL_D]);

DCSC doubleCSC(float M[][NUM_COL_D]);
int dcsc_nnc(int col, float m[][NUM_COL_D]);
void printDCSC(DCSC dcsc);
void freeMemoryDCSC(DCSC dcsc);
void nncz(float M[][NUM_ROW_D]);

#endif