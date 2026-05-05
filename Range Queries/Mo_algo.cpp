// O((N+Q)√N) — Mo's Algorithm for offline range queries
// Generic template: define add/rem/save outside and pass them in
// Works for any aggregate that supports incremental element addition/removal
#include <bits/stdc++.h>
using namespace std;

// Sorts queries in Mo's order and drives the [lo, hi] window.
// add(pos): called when arr[pos] enters the window
// rem(pos): called when arr[pos] leaves the window
// save(origIdx): called after window is adjusted to query [l, r]
template<typename AddFn, typename RemFn, typename SaveFn>
void moQuery(int n, vector<pair<int, int>>& queries, AddFn add, RemFn rem, SaveFn save) {
    int q = (int)queries.size();
    const int block = max(1, (int)sqrt(n));

    // Tag queries with original index, then sort by Mo's order
    vector<pair<pair<int, int>, int>> indexed(q);
    for (int i = 0; i < q; i++) indexed[i] = {{queries[i].first, queries[i].second}, i};

    // Sort: primary key = block of l; secondary key = r, alternating direction
    // per block (odd blocks descending) to reduce total pointer movement
    auto moCmp = [&](const auto& a, const auto& b) {
        int ba = a.first.first / block;
        int bb = b.first.first / block;
        if (ba != bb) return ba < bb;
        return (ba & 1) ? a.first.second > b.first.second
                        : a.first.second < b.first.second;
    };
    sort(indexed.begin(), indexed.end(), moCmp);

    int lo = 0, hi = -1;
    for (auto& [range, origIdx] : indexed) {
        auto [l, r] = range;
        while (hi < r) add(++hi);
        while (lo > l) add(--lo);
        while (hi > r) rem(hi--);
        while (lo < l) rem(lo++);
        save(origIdx);
    }
}

// Example: count distinct elements in each query range
// Usage:
//   Coordinate-compress arr if values are large.
//   Define freq, cur, ans outside, then pass add/rem/save to moQuery:
//
//   auto add  = [&](int pos) { if (++freq[arr[pos]] == 1) cur++; };
//   auto rem  = [&](int pos) { if (--freq[arr[pos]] == 0) cur--; };
//   auto save = [&](int idx) { ans[idx] = cur; };
//   moQuery(n, queries, add, rem, save);
