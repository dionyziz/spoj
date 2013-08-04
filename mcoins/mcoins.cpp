#include <cstdio>

using namespace std;

const int MAX_N = 1000001;

bool DP[MAX_N];

int main() {
    int K, L, m, N;

    scanf("%i %i %i", &K, &L, &m);

    for (int i = 0; i < m; ++i) {
        scanf("%i", &N);
        DP[0] = false;
        for (int j = 1; j <= N; ++j) {
            DP[j] = (j >= K && !DP[j - K])
                 || (j >= L && !DP[j - L])
                 || !DP[j - 1];
        }
        printf("%c", DP[N]? 'A': 'B');
    }
    printf("\n");

    return 0;
}
