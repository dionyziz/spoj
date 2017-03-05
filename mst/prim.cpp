#include <cstdio>
#include <vector>
#include <list>
#include <queue>

using namespace std;

vector< list< pair< int, int > > > G;
vector< bool > visited;

int main() {
    int N, M;
    int mst = 0;
    priority_queue< pair< int, int > > Q;

    scanf("%i %i", &N, &M);

    for (int n = 0; n <= N; ++n) {
        G.push_back(list< pair< int, int > >());
        visited.push_back(false);
    }

    for (int m = 0; m < M; ++m) {
        int i, j, k;
        scanf("%i %i %i", &i, &j, &k);
        G[i].push_back(make_pair(-k, j));
        G[j].push_back(make_pair(-k, i));
    }

    Q.push(make_pair(0, 1));
    while (!Q.empty()) {
        pair< int, int > current_edge = Q.top();
        Q.pop();
        int weight = current_edge.first;
        int current_node = current_edge.second;
        if (!visited[current_node]) {
            mst += -weight;
            visited[current_node] = true;

            for (list< pair< int, int > >::iterator it = G[current_node].begin(); it != G[current_node].end(); ++it) {
                Q.push(*it);
            }
        }
    }

    printf("%i\n", mst);

    return 0;
}
