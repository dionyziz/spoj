#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 100005;
const int MAXLGN = 18;

int A[MAXN];
int RMQ[MAXN][MAXLGN];

int log(int i) {
    int ret = 0;

    while ((i = i >> 1)) {
        ++ret;
    }
    return ret;
}

int query(int i, int j) {
    int len = j - i + 1;
    int exponent = log(len);

    return min(
        RMQ[i][exponent],
        RMQ[j + 1 - (1 << exponent)][exponent]
    );
}

int main() {
    int N, Q, i, j, q, exponent;

    scanf("%i", &N);
    for (i = 0; i < N; ++i) {
        scanf("%i", &A[i]);
    }

    for (i = 0; i < N; ++i) {
        RMQ[i][0] = A[i];
    }
    for (exponent = 1; (1 << exponent) < N; ++exponent) {
        for (i = 0; i + (1 << exponent) - 1 < N; ++i) {
            RMQ[i][exponent] = min(
                RMQ[i][exponent - 1],
                RMQ[i + (1 << (exponent - 1))][exponent - 1]
            );
            if (exponent == 1) {
                printf("RMQ[%i][%i] = %i\n", i, exponent, RMQ[i][exponent]);
            }
        }
    }

    scanf("%i", &Q);
    for (q = 0; q < Q; ++q) {
        scanf("%i %i", &i, &j);
        printf("%i\n", query(i, j));
    }

    return 0;
}
