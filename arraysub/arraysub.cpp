#include <cstdio>
#include <map>

using namespace std;

int main() {
    int A[1000001], n, k;
    map< int, int > s;
    map< int, int >::iterator it;

    scanf("%i", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%i", &A[i]);
        A[i] = -A[i];
    }
    scanf("%i", &k);
    for (int i = 0; i < n; ++i) {
        if (s.find(A[i]) == s.end()) {
            s[A[i]] = 1;
        }
        else {
            ++s[A[i]];
        }
        if (i >= k - 1) {
            it = s.find(A[i - k]);
            if (--it->second == 0) {
                s.erase(it);
            }
            printf("%i", -s.begin()->first);
            if (i != n - 1) {
                printf(" ");
            }
        }
    }
    return 0;
}
