#include <cstdio>
#include <vector>

#define NDEBUG

using namespace std;

const int MAXN = 1010;
const int MAXLGN = 12;

int T, N, LGN, M, Q;
int P[MAXN][MAXLGN];
int L[MAXN];

vector<int> children[MAXN];

void preprocess() {
    for (int j = 1; j <= LGN; ++j) {
        for (int n = 1; n <= N; ++n) {
            P[n][j] = P[P[n][j - 1]][j - 1];
#ifndef NDEBUG
            printf("P[%i][%i] = %i\n", n, j, P[n][j]);
#endif
        }
    }
}

int lca(int v, int w) {
    int j;

    if (L[v] > L[w]) {
#ifndef NDEBUG
        printf("Swapping levels\n");
#endif
        return lca(w, v);
    }
    j = LGN;
    while (L[v] != L[w]) {
#ifndef NDEBUG
        printf("%i and %i are not at the same level, equalizing...\n", v, w);
#endif
        if (L[v] <= L[P[w][j]]) {
#ifndef NDEBUG
            printf("Moving %i up to %i\n", w, P[w][j]);
#endif
            w = P[w][j];
        }
        --j;
    }
    j = LGN;
    if (v == w) {
        return v;
    }
    while (P[v][0] != P[w][0]) {
        if (P[v][j] != P[w][j] && P[v][j] && P[w][j]) {
#ifndef NDEBUG
            printf("Moving (v = %i to %i) and (w = %i to %i)\n", v, P[v][j], w, P[w][j]);
#endif
            v = P[v][j];
            w = P[w][j];
        }
        --j;
    }
    return P[v][0];
}

void levels(int node) {
#ifndef NDEBUG
    printf("levels(%i)\n", node);
#endif
    for (vector<int>::iterator child = children[node].begin(); child != children[node].end(); ++child) {
        L[*child] = L[node] + 1;
#ifndef NDEBUG
        printf("L[%i] = %i\n", *child, L[*child]);
#endif
        levels(*child);
    }
}

int main() {
    int v, w, child;

    scanf("%i", &T);
    for (int t = 1; t <= T; ++t) {
        printf("Case %i:\n", t);
        scanf("%i", &N);
#ifndef NDEBUG
        printf("N = %i\n", N);
#endif
        while (1 << LGN < N) {
            ++LGN;
        }
#ifndef NDEBUG
        printf("LGN = %i\n", LGN);
#endif
        for (int n = 1; n <= N; ++n) {
            scanf("%i", &M);
            children[n].clear();
            for (int m = 1; m <= M; ++m) {
                scanf("%i", &child);
                P[child][0] = n;
#ifndef NDEBUG
                printf("P[%i][0] = %i\n", child, n);
#endif
                children[n].push_back(child);
            }
#ifndef NDEBUG
            printf("Children of %i:\n", n);
            for (vector<int>::iterator childi = children[n].begin(); childi != children[n].end(); ++childi) {
                printf("%i ", *childi);
            }
            printf("\n");
#endif
        }
#ifndef NDEBUG
        printf("Levels...\n");
#endif
        for (int n = 1; n < N; ++n) {
            if (P[n][0] == 0) {
                L[n] = 1;
#ifndef NDEBUG
                printf("L[%i] = 1\n", n);
#endif
                levels(n);
                break;
            }
        }
#ifndef NDEBUG
        printf("Preprocessing...\n");
#endif
        preprocess();
        scanf("%i", &Q);
#ifndef NDEBUG
        printf("Q = %i\n", Q);
#endif
        for (int q = 1; q <= Q; ++q) {
            scanf("%i %i", &v, &w);
#ifndef NDEBUG
            printf("LCA(%i, %i) = ?\n", v, w);
#endif
            printf("%i\n", lca(v, w));
        }
    }
    return 0;
}
