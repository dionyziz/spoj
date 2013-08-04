#include <cstdio>

using namespace std;

const int MAX_N = 101;
const int MAX_M = 21;

int DP[MAX_M][MAX_N], M, N, A, B;

int main() {
    while (true) {
        scanf("%i %i", &M, &N);
        if (M == 0 && N == 0) {
            break;
        }
        for (int j = 0; j <= N; ++j) {
            DP[0][j] = 0;
        }
        DP[0][0] = 1;
        for (int i = 1; i <= M; ++i) {
            scanf("%i %i", &A, &B);
            for (int j = 0; j <= N; ++j) {
                DP[i][j] = 0;
                for (int k = A; k <= B && k <= j; ++k) {
                    DP[i][j] += DP[i - 1][j - k];
                }
            }
        }
        printf("%i\n", DP[M][N]);
    }
    return 0;
}
