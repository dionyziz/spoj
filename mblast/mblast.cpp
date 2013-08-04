#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;

const int INF = 87654321;
const int MAX_LEN = 2013;

char A[MAX_LEN], B[MAX_LEN];
int DP[MAX_LEN][MAX_LEN], K;

int main() {
    int a, b;

    scanf("%s %s %i", A, B, &K);

    a = strlen(A);
    b = strlen(B);
    
    for (int i = 0; i <= a; ++i) {
        DP[i][0] = K * i;
    }
    for (int j = 0; j <= b; ++j) {
        DP[0][j] = K * j;
    }
    for (int i = 1; i <= a; ++i) {
        for (int j = 1; j <= b; ++j) {
            DP[i][j] = min(DP[i - 1][j - 1] + (int)abs((double)(A[i - 1] - B[j - 1])),
                           min(DP[i - 1][j], DP[i][j - 1]) + K);
        }
    }

    printf("%i\n", DP[a][b]);

    return 0;
}
