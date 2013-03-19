#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_N = 12345;

int dfs(char** s) {
    if (*((*s)++) == 'l') {
        return 0;
    }
    return max(dfs(s), dfs(s)) + 1;
}

int main() {
    int T;
    char* s = (char*)malloc(MAX_N);

    scanf("%i", &T);
    for (int i = 0; i < T; ++i) {
        scanf("%s", s);
        printf("%i\n", dfs(&s));
    }

    return 0;
}
