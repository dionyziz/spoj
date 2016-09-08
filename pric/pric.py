from random import randrange
import sys
import time

def is_prime(p):
    if p in (2, 3, 5, 7):
        return True
    if p in (1, 4, 6, 8, 9):
        return False

    phi = p - 1
    d = phi
    r = 0

    while d % 2 == 0:
        d /= 2
        r += 1

    for a in (2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37):
        exp = pow(a, d, p)
        if exp == 1 or exp == p - 1:
            continue
        for j in range(r - 1):
            exp = pow(exp, 2, p)
            if exp == 1:
                return False
            if exp == p - 1:
                break
        else:
            return False
    return True

t = time.time()
N = 10000
TLE = 3.3
a = 1
for i in range(0, N):
    if is_prime(a):
        sys.stdout.write('1')
    else:
        sys.stdout.write('0')
    a = (a + 1234567890) % 2**31
    if i % 10000 == 0:
        tt = time.time()
        if tt - t > TLE:
            break
