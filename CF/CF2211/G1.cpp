#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using i128 = __int128_t;

bool solve_case() {
    int n;
    cin >> n;

    vector<int64> a(n + 1);
    int64 total_sum = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        total_sum += a[i];
    }

    int64 prefix_sum = 0;
    bool prev_equal = true;          // 仅用于和当前切分点组成相邻对
    bool has_bad_adjacent = false;   // 是否出现过连续两个“不相等”切分点

    for (int i = 1; i < n; ++i) {
        prefix_sum += a[i];

        i128 left = (i128)prefix_sum * (n - i);
        i128 right = (i128)(total_sum - prefix_sum) * i;

        if (left < right) {
            return true;
        }

        bool cur_equal = (left == right);
        if (i > 1 && !prev_equal && !cur_equal) {
            has_bad_adjacent = true;
        }
        prev_equal = cur_equal;
    }

    return !has_bad_adjacent;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        cout << (solve_case() ? "Yes" : "No") << '\n';
    }

    return 0;
}