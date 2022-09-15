#ifndef CSR_H
#define CSR_H

typedef struct
{
    float *A; // Vecteur des elts non-nuls
    int *IA;  //
    int *JA;  // Vecteur des indices des col non-nulles
} CSR;

typedef struct
{
    float *A; // Vecteur des elts non-nuls
    int *IA;  // Vecteur des indices des lignes non-nulles
    int *JA;  //
} CSC;

int NUM_ROW; // Nbre de Lign de M
int NUM_COL; // nbre de Col de M
int NNZ;     // Nbre d'elt Non-nul de M

CSR compress_SR(float M[][NUM_COL]);
int csr_nnr(int row, float m[][NUM_COL]);
void printCSR(CSR csr);
void freeMemoryCSR(CSR csr);

CSC compress_SC(float M[][NUM_COL]);
int csc_nnc(int col, float m[][NUM_COL]);
void printCSC(CSC csc);
void freeMemoryCSC(CSC csc);

#endif