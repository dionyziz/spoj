#include <cstdio>
#include <vector>
#include <list>
#include <queue>

using namespace std;

typedef long long int lli;

vector< list< pair< lli, int > > > G;
vector< bool > visited;

int main() {
    int N, M;
    lli mst = 0;
    priority_queue< pair< lli, int > > Q;

    scanf("%i %i", &N, &M);

    for (int n = 0; n <= N; ++n) {
        G.push_back(list< pair< lli, int > >());
        visited.push_back(false);
    }

    for (int m = 0; m < M; ++m) {
        int i, j;
        lli k;
        scanf("%i %i %lli", &i, &j, &k);
        G[i].push_back(make_pair(-k, j));
        G[j].push_back(make_pair(-k, i));
    }

    Q.push(make_pair(0, 1));
    while (!Q.empty()) {
        pair< lli, lli > current_edge = Q.top();
        Q.pop();
        lli weight = current_edge.first;
        lli current_node = current_edge.second;
        if (!visited[current_node]) {
            mst += -weight;
            visited[current_node] = true;

            for (list< pair< lli, int > >::iterator it = G[current_node].begin(); it != G[current_node].end(); ++it) {
                Q.push(*it);
            }
        }
    }

    printf("%lli\n", mst);

    return 0;
}
