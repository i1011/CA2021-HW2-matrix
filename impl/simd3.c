#define SIZE 128
#define NN 43
typedef unsigned long long u64;
typedef unsigned short u16;
u64 BB[SIZE][NN], AA[SIZE][NN];
void matrix_mul(u16 (*A)[SIZE], u16 (*B)[SIZE], u16 (*C)[SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < NN - 1; ++j) {
            BB[i][j] = (u64)(B[j * 3 + 0][i]) << 54 | (u64)B[j * 3 + 1][i] << 27 | B[j * 3 + 2][i];
            AA[i][j] = (u64)(A[i][j * 3 + 2]) << 54 | (u64)A[i][j * 3 + 1] << 27 | A[i][j * 3 + 0];
        }
        {
            const int j = NN - 1;
            BB[i][j] = (u64)(B[j * 3 + 0][i]) << 54 | (u64)B[j * 3 + 1][i] << 27;
            AA[i][j] = (u64)A[i][j * 3 + 1] << 27 | A[i][j * 3 + 0];
        }
    }

    for (int j = 0; j < SIZE; ++j) {
        for (int i = 0; i < SIZE; ++i) {
            u64 s = 0;
            for (int k = 0; k < NN; ++k) {
                s += AA[i][k] * BB[j][k];
            }

            C[i][j] = s >> 54;
        }
    }
}
