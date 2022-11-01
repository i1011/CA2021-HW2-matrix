#define SIZE 128
typedef unsigned long long u64;
typedef unsigned short u16;
void matrix_mul(u16 (*A)[SIZE], u16 (*B)[SIZE], u16 (*C)[SIZE]) {
    u64 BB[SIZE][SIZE / 2], AA[SIZE][SIZE / 2];
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE / 2; ++j) {
            BB[i][j] = (u64)(B[j * 2 + 0][i]) << 27 | B[j * 2 + 1][i];
            AA[i][j] = (u64)(A[i][j * 2 + 0]) << 27 | A[i][j * 2 + 1];
        }
    }

    for (int j = 0; j < SIZE; ++j) {
        for (int i = 0; i < SIZE; ++i) {
            u64 s = 0;
            for (int k = 0; k < SIZE / 2; ++k) {
                s += AA[i][k] * BB[j][k];
            }

            C[i][j] = (s + (s >> 54)) & 1023;
        }
    }
}
