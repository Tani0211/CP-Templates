#pragma once
#include <vector>
#include <set>
#include <climits>
#include <algorithm>

// Brute-force range queries — include this in any range-query test file
// to verify algorithm output against a trivially correct reference.

inline long long brute_sum(std::vector<long long>& a, int l, int r) {
    long long res = 0;
    for (int i = l; i <= r; i++) res += a[i];
    return res;
}

inline long long brute_xor(std::vector<long long>& a, int l, int r) {
    long long res = 0;
    for (int i = l; i <= r; i++) res ^= a[i];
    return res;
}

inline long long brute_min(std::vector<long long>& a, int l, int r) {
    long long res = LLONG_MAX;
    for (int i = l; i <= r; i++) res = std::min(res, a[i]);
    return res;
}

inline long long brute_max(std::vector<long long>& a, int l, int r) {
    long long res = LLONG_MIN;
    for (int i = l; i <= r; i++) res = std::max(res, a[i]);
    return res;
}

inline int brute_distinct(std::vector<int>& arr, int l, int r) {
    std::set<int> s(arr.begin() + l, arr.begin() + r + 1);
    return (int)s.size();
}

// Apply a range assign to a reference array alongside a LazySGT update
// so both stay in sync and brute_sum can verify queries.
inline void range_assign(std::vector<long long>& a, int l, int r, long long val) {
    for (int i = l; i <= r; i++) a[i] = val;
}
