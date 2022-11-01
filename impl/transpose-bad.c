#define SIZE 128
typedef unsigned long long u64;
typedef unsigned short u16;
u16 BT[SIZE][SIZE];
void matrix_mul(u16 (*A)[SIZE], u16 (*B)[SIZE], u16 (*C)[SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            // BT[i][j] = B[j][i];
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < SIZE; ++k) {
                C[i][j] += A[i][k] * BT[j][k];
            }
            C[i][j] &= 1023;
        }
    }
}
