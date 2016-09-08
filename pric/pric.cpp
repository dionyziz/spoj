#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef unsigned long long int lli;

// const int N = 10000;
const int N = 33333333;
const int K = 2;
const lli witnesses[] = {336781006125, 9639812373923155};
const lli primes[] = {2, 3, 5, 7, 11, 17, 19, 23, 29, 31, 37, 41, 43, 47,
                      53, 59, 61, 67, 71, 73, 79, 83, 89};
const int N_PRIMES = 23;
const int MOD = 1 << 31;
const double TLE = 3.45;
const int BUFFER_LEN = 10000;

inline lli pow(lli b, lli e, lli m) {
    lli prod = 1;

    while (e) {
        if (e & 1) {
            prod = (prod * b) % m;
        }
        b = (b * b) % m;
        e >>= 1;
    }

    return prod;
}

inline bool is_prime(lli p) {
    if (p == 1) {
        return false;
    }
    for (int i = 0; i < N_PRIMES; ++i) {
        if (p == primes[i]) {
            return true;
        }
        if (p % primes[i] == 0) {
            return false;
        }
    }

    lli d = p - 1;
    lli r = 0;

    while (d % 2 == 0) {
        d >>= 1;
        ++r;
    }

    for (lli i = 0; i < K; ++i) {
        lli a = witnesses[i];
        a = a % p;
        if (a == 0) {
            return true;
        }
        lli exp = pow(a, d, p);
        if (exp == 1 || exp == p - 1) {
            continue;
        }
        bool broken = false;
        for (lli j = 0; j < r - 1; ++j) {
            exp = (exp * exp) % p;
            if (exp == 1) {
                return false;
            }
            if (exp == p - 1) {
                broken = true;
                break;
            }
        }
        if (!broken) {
            return false;
        }
    }

    return true;
}

int main() {
    long long int a = 1;
    clock_t begin = clock();
    char A[BUFFER_LEN + 1];
    int c = 0;

    for (int i = 0; i < N; ++i) {
        if (is_prime(a)) {
            A[i % BUFFER_LEN] = '1';
            ++c;
        }
        else {
            A[i % BUFFER_LEN] = '0';
        }
        a = (a + 1234567890) % MOD;
        if (i % BUFFER_LEN == BUFFER_LEN - 1) {
            A[BUFFER_LEN] = 0;
            printf("%s", A);

            clock_t end = clock();
            double secs = double(end - begin) / CLOCKS_PER_SEC;

            if (secs > TLE) {
                // printf("c = %i, i = %i\n", c, i);
                return 0;
            }
        }
    }

    return 0;
}
