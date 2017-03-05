#include <cstdio>
#include <vector>
#include <list>
#include <queue>

using namespace std;

// Union-Find data structure
struct UF {
    int parent;
    int rank;
};

typedef long long int lli;

vector< list< pair< lli, int > > > G;
vector< UF > uf;

struct Edge {
    int u;
    int v;
    lli w;
};

bool operator<(Edge a, Edge b) {
    return a.w < b.w;
}

int set_find(int which) {
    if (uf[which].parent != which) {
        // path compression
        uf[which].parent = set_find(uf[which].parent);
    }
    return uf[which].parent;
}

void set_union(int a, int b) {
    int a_parent = set_find(a);
    int b_parent = set_find(b);

    if (uf[a_parent].rank < uf[b_parent].rank) {
        uf[a_parent].parent = b_parent;
    }
    else if (uf[a_parent].rank > uf[b_parent].rank) {
        uf[b_parent].parent = a_parent;
    }
    else {
        uf[a_parent].parent = b_parent;
        ++uf[b_parent].rank;
    }
}

int main() {
    int N, M;
    lli mst = 0;
    priority_queue< Edge > Q;

    scanf("%i %i", &N, &M);

    for (int n = 0; n <= N; ++n) {
        G.push_back(list< pair< lli, int > >());
        uf.push_back((UF){n, 0});
    }

    for (int m = 0; m < M; ++m) {
        int i, j;
        lli k;
        scanf("%i %i %lli", &i, &j, &k);
        G[i].push_back(make_pair(k, j));
        G[j].push_back(make_pair(k, i));
        Q.push((Edge){i, j, -k});
    }

    while (!Q.empty()) {
        Edge e = Q.top();
        Q.pop();
        if (set_find(e.u) != set_find(e.v)) {
            set_union(e.u, e.v);
            mst += e.w;
        }
    }
    printf("%lli\n", -mst);

    return 0;
}
