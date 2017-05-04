#include <cstdio>
#include <algorithm>
// #include <ctime>

using namespace std;

const int MAX_N = 50007;

struct Node {
    int sum;
    int msum;
    int psum;
    int ssum;
};

int N, M;
int A[MAX_N];
Node T[4 * MAX_N];

inline int geti() {
    int s = 1, x = 0, c = getchar_unlocked();

    while ((c < '0' || c > '9') && c != '-') {
        c = getchar_unlocked();
    }

    if (c == '-') {
        s = -1;
        c = getchar_unlocked();
    }
    while (c >= '0' && c <= '9') {
        x = (x << 1) + (x << 3) + c - '0';
        c = getchar_unlocked();
    }
    return s * x;
}

Node combine(Node a, Node b) {
    Node r;

    r.sum = a.sum + b.sum;
    r.msum = max(
        max(a.msum, b.msum),
        a.ssum + b.psum
    );
    r.psum = max(
        a.psum,
        a.sum + b.psum
    );
    r.ssum = max(
        b.ssum,
        b.sum + a.ssum
    );

    return r;
}

Node query(int qx, int qy, int idx, int x, int y) {
    if (qx == x && qy == y) {
        return T[idx];
    }
    int mid = (x + y) / 2;
    if (qy <= mid) {
        return query(qx, qy, 2 * idx, x, mid);
    }
    if (qx > mid) {
        return query(qx, qy, 2 * idx + 1, mid + 1, y);
    }
    return combine(
        query(qx, mid, 2 * idx, x, mid),
        query(mid + 1, qy, 2 * idx + 1, mid + 1, y)
    );
}

void build(int idx, int x, int y) {
    if (x == y) {
        T[idx].msum = T[idx].psum = T[idx].ssum = T[idx].sum = A[x];
        return;
    }
    int mid = (x + y) / 2;
    build(2 * idx, x, mid);
    build(2 * idx + 1, mid + 1, y);
    T[idx] = combine(T[2 * idx], T[2 * idx + 1]);
}

int main() {
    // clock_t begin, end;

    // begin = clock();
    N = geti();
    for (int i = 1; i <= N; ++i) {
        A[i] = geti();
    }
    // end = clock();
    // fprintf(stderr, "Scanf of array took: %.5fs\n", double(end - begin) / CLOCKS_PER_SEC);

    // begin = clock();
    build(1, 1, N);
    // end = clock();
    // fprintf(stderr, "Build took: %.5fs\n", double(end - begin) / CLOCKS_PER_SEC);

    // scanf("%i", &M);
    M = geti();
    // begin = clock();
    for (int i = 0; i < M; ++i) {
        int x, y;
        x = geti();
        y = geti();
        printf("%i\n", query(x, y, 1, 1, N).msum);
        query(x, y, 1, 1, N);
    }
    // end = clock();
    // fprintf(stderr, "Queries took: %.5fs\n", double(end - begin) / CLOCKS_PER_SEC);
    return 0;
}
