#include "common.h"
#include "../Common Techniques/Distinct in Range Queries.cpp"

using namespace std;

int brute_distinct(vector<int>& arr, int l, int r) {
    return (int)set<int>(arr.begin() + l, arr.begin() + r + 1).size();
}

int run_tests() {
    // arr = [1, 2, 3, 2, 1]
    // Queries (0-indexed, inclusive):
    //   (0, 4) → {1,2,3} → 3 distinct
    //   (0, 2) → {1,2,3} → 3 distinct
    //   (1, 3) → {2,3,2} → {2,3} → 2 distinct
    //   (2, 4) → {3,2,1} → 3 distinct
    vector<int> arr = {1, 2, 3, 2, 1};
    vector<pair<int, int>> queries = {{0, 4}, {0, 2}, {1, 3}, {2, 4}};

    vector<int> ans = distinctQueries(5, 4, arr, queries);
    ASSERT_EQ(ans[0], 3);
    ASSERT_EQ(ans[1], 3);
    ASSERT_EQ(ans[2], 2);
    ASSERT_EQ(ans[3], 3);

    // All same elements
    vector<int> arr2 = {5, 5, 5, 5};
    vector<pair<int, int>> queries2 = {{0, 3}, {1, 2}};
    vector<int> ans2 = distinctQueries(4, 2, arr2, queries2);
    ASSERT_EQ(ans2[0], 1);
    ASSERT_EQ(ans2[1], 1);

    // Stress test: n=500, q=200, large random values in [1, 1000000]
    mt19937 rng(42);
    int n = 500, q = 200;
    vector<int> arr3(n);
    for (int& x : arr3) x = rng() % 1000000 + 1;

    vector<pair<int, int>> queries3(q);
    for (auto& [l, r] : queries3) {
        l = rng() % n;
        r = rng() % n;
        if (l > r) swap(l, r);
    }

    vector<int> arr3_copy = arr3;
    vector<int> ans3 = distinctQueries(n, q, arr3_copy, queries3);

    for (int i = 0; i < q; i++)
        ASSERT_EQ(ans3[i], brute_distinct(arr3, queries3[i].first, queries3[i].second));

    TEST_PASS();
}

int main() { return run_tests(); }
