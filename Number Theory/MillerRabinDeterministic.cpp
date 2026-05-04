// O(log²N) — Deterministic Miller-Rabin primality test
// MillerRabin(n) returns true if n is prime, false otherwise.
#include <bits/stdc++.h>
using namespace std;

long long _mr_pow(long long a, long long b, long long mod) {
    long long res = 1;
    for (a %= mod; b > 0; b >>= 1) {
        if (b & 1) res = (__int128)res * a % mod;
        a = (__int128)a * a % mod;
    }
    return res;
}

bool _mr_composite(long long n, long long a, long long d, int s) {
    long long x = _mr_pow(a, d, n);
    if (x == 1 || x == n - 1) return false;
    for (int r = 1; r < s; r++) {
        x = (__int128)x * x % n;
        if (x == n - 1) return false;
    }
    return true;
}

bool MillerRabin(long long n) {
    if (n < 2) return false;
    long long d = n - 1;
    int s = 0;
    while ((d & 1) == 0) { d >>= 1; s++; }
    // These 12 witnesses make the test deterministic for all n < 3.317 × 10^24 (cp-algorithms.com)
    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a) return true;
        if (_mr_composite(n, a, d, s)) return false;
    }
    return true;
}
