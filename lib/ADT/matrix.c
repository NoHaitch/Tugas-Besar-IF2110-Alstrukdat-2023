#include <stdio.h>
#include "limits.h"
#include "matrix.h"
#include "boolean.h"

void createMatrix(int nRows, int nCols, Matrix* m){
    ROW_EFF(*m) = nRows;
    COL_EFF(*m) = nCols;

    int i, j;
    for(i = 0; i < nRows; ++i){
        for(j = 0; j < nCols; ++j){
            ELMT(*m, i, j) = 0;
        }
    }
}

boolean isMatrixIdxValid(int i, int j){
    return (0 <= i && i < ROW_CAP) && (0 <= j && j < COL_CAP);
}

IdxType getLastIdxRow(Matrix m){
    return ROW_EFF(m) - 1;
}

IdxType getLastIdxCol(Matrix m){
    return COL_EFF(m) - 1;
}

boolean isIdxEff(Matrix m, IdxType i, IdxType j){
    return 
        (0 <= i && i <= getLastIdxRow(m)) &&
        (0 <= j && j <= getLastIdxCol(m));
}

ElType getElmtDiagonal(Matrix m, IdxType i){
    return ELMT(m, i, i);
}

void copyMatrix(Matrix mIn, Matrix* mOut){
    createMatrix(ROW_EFF(mIn), COL_EFF(mIn), mOut);
    int i, j;
    for(i = 0; i < ROW_EFF(mIn); ++i){
        for(j = 0; j < COL_EFF(mIn); ++j){
            ELMT(*mOut, i, j) = ELMT(mIn, i, j);
        }
    }
}

void readMatrix(Matrix* m, int nRow, int nCol){
    createMatrix(nRow, nCol, m);
    int i, j;
    for(i = 0; i < nRow; ++i){
        for(j = 0; j < nCol; ++j){
            scanf("%d", &(ELMT(*m, i, j)));
        }
    }
}

void displayMatrix(Matrix m){
    int i, j;
    for(i = 0; i < ROW_EFF(m); ++i){
        for(j = 0; j < COL_EFF(m); ++j){
            printf("%d", ELMT(m, i, j));
            if(j != COL_EFF(m) - 1) printf(" ");
        }
        if(i != ROW_EFF(m) - 1) printf("\n");
    }
}

Matrix addMatrix(Matrix m1, Matrix m2){
    Matrix r;
    createMatrix(ROW_EFF(m1), COL_EFF(m1), &r);
    int i, j;
    for(i = 0; i < ROW_EFF(m1); ++i){
        for(j = 0; j < COL_EFF(m1); ++j){
            ELMT(r, i, j) = ELMT(m1, i, j) + ELMT(m2, i, j);
        }
    }
    return r;
}

Matrix subtractMatrix(Matrix m1, Matrix m2){
    Matrix r;
    createMatrix(ROW_EFF(m1), COL_EFF(m1), &r);
    int i, j;
    for(i = 0; i < ROW_EFF(m1); ++i){
        for(j = 0; j < COL_EFF(m1); ++j){
            ELMT(r, i, j) = ELMT(m1, i, j) - ELMT(m2, i, j);
        }
    }
    return r;
}

Matrix multiplyMatrix(Matrix m1, Matrix m2){
    Matrix r;
    createMatrix(ROW_EFF(m1), COL_EFF(m2), &r);
    int i, j, k;
    for(i = 0; i < ROW_EFF(m1); ++i){
        for(j = 0; j < COL_EFF(m2); ++j){
            ELMT(r, i, j) = 0;
            for(k = 0; k < COL_EFF(m1); ++k){
                ELMT(r, i, j) += (ELMT(m1, i, k) * ELMT(m2, k, j));
            }
        }
    }
    
    return r;
}

Matrix multiplyMatrixWithMod(Matrix m1, Matrix m2, int mod){
    Matrix r;
    createMatrix(ROW_EFF(m1), COL_EFF(m2), &r);
    int i, j, k;
    for(i = 0; i < ROW_EFF(m1); ++i){
        for(j = 0; j < COL_EFF(m2); ++j){
            ELMT(r, i, j) = 0;
            for(k = 0; k < COL_EFF(m1); ++k){
                ELMT(r, i, j) += (ELMT(m1, i, k) * ELMT(m2, k, j));
            }
            if(mod >= 0) ELMT(r, i, j) = ELMT(r, i, j) % mod;
        }
    }
    
    return r;
}

Matrix multiplyByConst(Matrix m, ElType x){
    Matrix r;
    copyMatrix(m, &r);
    pMultiplyByConst(&r, x);
    return r;
}

void pMultiplyByConst(Matrix* m, ElType x){
    int i, j;
    for(i = 0; i < ROW_EFF(*m); ++i){
        for(j = 0; j < COL_EFF(*m); ++j){
            ELMT(*m, i, j) *= x;
        }
    }
}

boolean isMatrixEqual(Matrix m1, Matrix m2){
    if(!isMatrixSizeEqual(m1, m2)) return false;

    int i, j;
    for(i = 0; i < ROW_EFF(m1); ++i){
        for(j = 0; j < COL_EFF(m1); ++j){
            if(ELMT(m1, i, j) != ELMT(m2, i, j)){
                return false;
            }
        }
    }
    return true;
}

boolean isMatrixNotEqual(Matrix m1, Matrix m2){
    return !isMatrixEqual(m1, m2);
}

boolean isMatrixSizeEqual(Matrix m1, Matrix m2){
    return (ROW_EFF(m1) == ROW_EFF(m2)) && (COL_EFF(m1) == COL_EFF(m2));
}

int countElmt(Matrix m){
    return ROW_EFF(m) * COL_EFF(m);
}

boolean isSquare(Matrix m){
    return ROW_EFF(m) == COL_EFF(m);
}

boolean isSymmetric(Matrix m){
    if(!isSquare(m)) return false;

    int i, j;
    for(i = 0; i < ROW_EFF(m); ++i){
        for(j = 0; j < COL_EFF(m); ++j){
            if(ELMT(m, i, j) != ELMT(m, j, i)){
                return false;
            }
        }
    }
    return true;
}

boolean isIdentity(Matrix m){
    if(!isSquare(m)) return false;

    int i, j;
    for(i = 0; i < ROW_EFF(m); ++i){
        for(j = 0; j < COL_EFF(m); ++j){
            if(i == j && ELMT(m, i, j) != 1) return false;
            else if(i != j && ELMT(m, i, j) != 0) return false;
        }
    }

    return true;
}

boolean isSparse(Matrix m){
    int count = 0, i, j;
    for(i = 0; i < ROW_EFF(m); ++i){
        for(j = 0; j < COL_EFF(m); ++j){
            if(ELMT(m, i, j) != 0){
                ++count;
            }
        }
    }

    return (count * 100) <= (5 * countElmt(m));
}

Matrix negation(Matrix m){
    return multiplyByConst(m, -1);
}

void pNegation(Matrix* m){
    pMultiplyByConst(m, -1);
}

Matrix cofactor(Matrix m, int r, int c){
    Matrix C;
    createMatrix(ROW_EFF(m) - 1, COL_EFF(m) - 1, &C);

    int i, j, ci = 0, cj = 0;
    for(i = 0; i < ROW_EFF(m); ++i){
        if(i == r) continue;
        cj = 0;
        for(j = 0; j < COL_EFF(m); ++j){
            if(j == c) continue;
            ELMT(C, ci, cj) = ELMT(m, i, j);
            ++cj;
        }
        ++ci;
    }

    return C;
}

float determinant(Matrix m){
    if(ROW_EFF(m) == 1) return ELMT(m, 0, 0);
    
    int i, r = 0;
    for(i = 0; i < COL_EFF(m); ++i){
        int c = ELMT(m, 0, i) * determinant(cofactor(m, 0, i));
        if(i % 2 == 1) c *= -1;
        r += c;
    }

    return (float) r;
}

Matrix transpose(Matrix m){
    Matrix n;
    createMatrix(COL_EFF(m), ROW_EFF(m), &n);

    int i, j;
    for(i = 0; i < ROW_EFF(m); ++i){
        for(j = 0; j < COL_EFF(m); ++j){
            ELMT(n, j, i) = ELMT(m, i, j);
        }
    }

    return n;
}

void pTranspose(Matrix *m){
    Matrix t = transpose(*m);
    copyMatrix(t, m);
}