#include <cstdio>
#include <list>
#include <queue>

using namespace std;

const int SINK = 50001;
const int MAX_N = 50005;
const int INFINITY = 87654321;

int N, M, P;
int pair_g1[MAX_N], pair_g2[MAX_N], dist[MAX_N];
list< int > adj[MAX_N];

bool bfs() {
    queue< int > q; // queue of G1 nodes

    for (int v = 0; v < N; ++v) {
        if (pair_g1[v] == SINK) {
            dist[v] = 0;
            q.push(v);
        }
        else {
            dist[v] = INFINITY;
        }
    }
    dist[SINK] = INFINITY;

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        if (dist[v] < dist[SINK]) {
            for (list< int >::iterator it = adj[v].begin(); it != adj[v].end(); ++it) {
                int u = *it;

                if (dist[pair_g2[u]] == INFINITY) {
                    dist[pair_g2[u]] = dist[v] + 1;
                    q.push(pair_g2[u]);
                }
            }
        }
    }
    return dist[SINK] != INFINITY;
}

bool dfs(int u) {
    // DFS starting at a node u in G1

    if (u == SINK) {
        // we've reached a free node in G2 (i.e. one pointing to SINK)
        return true;
    }

    for (list< int >::iterator it = adj[u].begin(); it != adj[u].end(); ++it) {
        int v = *it;

        if (dist[pair_g2[v]] == dist[u] + 1) {
            if (dfs(pair_g2[v])) {
                pair_g1[u] = v;
                pair_g2[v] = u;
                return true;
            }
        }
    }
    dist[u] = INFINITY;
    return false;
}

int hopcroft_karp() {
    int matching = 0;

    for (int i = 0; i < N; ++i) {
        pair_g1[i] = SINK;
    }
    for (int j = 0; j < M; ++j) {
        pair_g2[j] = SINK;
    }

    while (bfs()) {
        for (int i = 0; i < N; ++i) {
            if (pair_g1[i] == SINK) {
                matching += dfs(i);
            }
        }
    }
    return matching;
}

int main() {
    scanf("%i %i %i", &N, &M, &P);

    for (int i = 0; i < N; ++i) {
        adj[i] = list< int >();
    }

    for (int i = 0; i < P; ++i) {
        int u, v;

        scanf("%i %i", &u, &v);
        --u; --v;
        adj[u].push_back(v);
    }

    printf("%i\n", hopcroft_karp());

    return 0;
}
