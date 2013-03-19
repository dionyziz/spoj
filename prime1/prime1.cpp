#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

typedef unsigned long long int lli;

const int K = 20;
int detrand[3];

lli powmod(lli base, lli exponent, lli mod) {
    lli ret = 1;

    while (exponent) {
        if (exponent & 1) {
            ret *= base;
            ret %= mod;
        }
        base *= base;
        base %= mod;
        exponent >>= 1;
    }

    return ret;
}

inline bool miller_rabin(lli n) {
    if (n == 2) {
        return true;
    }
    if (n % 2 == 0) {
        return false;
    }
    if (n == 1) {
        return false;
    }
    if (n == 3 || n == 7 || n == 61) {
        return true;
    }
    lli m = n - 1;
    lli s = 0;

    while ((m & 1) == 0) {
        ++s;
        m >>= 1;
    }

    for (int i = 0; i < 3; ++i) {
        lli a = detrand[i];
        lli x = powmod(a, m, n);
        if (x == 1 || x == n - 1) {
            continue;
        }
        bool prime = false;
        for (lli j = 0; j < s - 1; ++j) {
            x = (x * x) % n;
            if (x == 1) {
                return false;
            }
            if (x == n - 1) {
                prime = true;
                break;
            }
        }
        if (prime) {
            continue;
        }
        return false;
    }
    return true;
}

int main() {
    int t;

    detrand[0] = 2;
    detrand[1] = 7;
    detrand[2] = 61;

    fscanf(stdin, "%i", &t);

    while (t--) {
        int l, r;
        fscanf(stdin, "%i %i", &l, &r);
        for (int candidate = l; candidate <= r; ++candidate) {
            if (miller_rabin(candidate)) {
                fprintf(stdout, "%i\n", candidate);
            }
        }
        if (t != 0) {
            printf("\n");
        }
    }

    return 0;
}
