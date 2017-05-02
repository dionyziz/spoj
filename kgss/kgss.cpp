#include <cstdio>
#include <algorithm>
#include <cassert>

using namespace std;

typedef pair<int, int> maxinfo;

const int MAX_N = 100007;
int A[MAX_N];
int N;
maxinfo T[4 * MAX_N];

maxinfo constructParent(maxinfo left, maxinfo right) {
    return make_pair(
        max(left.first, right.first),
        max(
            max(left.second, right.second),
            left.first + right.first
        )
    );
}

maxinfo query(int lo, int hi, int idx, int l, int r) {
    if (lo == l && hi == r) {
        return T[idx];
    }
    int mid = (l + r) / 2;
    if (hi <= mid) {
        return query(lo, hi, 2 * idx, l, mid);
    }
    if (lo > mid) {
        return query(lo, hi, 2 * idx + 1, mid + 1, r);
    }
    maxinfo left = query(lo, mid, 2 * idx, l, mid),
            right = query(mid + 1, hi, 2 * idx + 1, mid + 1, r);

    return constructParent(left, right);
}

void update(int i, int x, int idx, int l, int r) {
    if (l == r) {
        T[idx].first = x;
        T[idx].second = -1;
        return;
    }

    int mid = (l + r) / 2;

    if (i <= mid) {
        update(i, x, 2 * idx, l, mid);
    }
    else {
        update(i, x, 2 * idx + 1, mid + 1, r);
    }

    maxinfo left = T[2 * idx],
            right = T[2 * idx + 1];

    T[idx] = constructParent(left, right);
}

void build(int idx, int l, int r) {
    if (l == r) {
        T[idx].first = A[l];
        T[idx].second = -1;
        return;
    }

    int mid = (l + r) / 2;

    build(2 * idx, l, mid);
    build(2 * idx + 1, mid + 1, r);

    maxinfo left = T[2 * idx],
            right = T[2 * idx + 1];

    T[idx] = constructParent(left, right);
}

int main() {
    int Q;
    char op;
    int x, y;

    scanf("%i", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%i", &A[i]);
    }
    build(1, 0, N - 1);
    scanf("%i", &Q);
    for (int i = 0; i < Q; ++i) {
        scanf("\n%c %i %i", &op, &x, &y);
        switch (op) {
            case 'U':
                --x;
                update(x, y, 1, 0, N - 1);
                break;
            case 'Q':
                --x; --y;
                printf("%i\n", query(x, y, 1, 0, N - 1).second);
                break;
            default:
                assert(false);
        }
    }
    return 0;
}
