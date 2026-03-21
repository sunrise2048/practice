#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 998244353;
const int MAXN = 100005;

int n;
vector<int> adj[MAXN];

// 贪心检验是否能将 W 中除去 skip1 和 skip2 的元素两两配对，使得每对之和 <= L
bool can_pair_skip(const vector<int>& W, int L, int skip1, int skip2 = -1) {
    int l = 0, r = (int)W.size() - 1;
    while (l < r) {
        if (l == skip1 || l == skip2) { l++; continue; }
        if (r == skip1 || r == skip2) { r--; continue; }
        if (W[l] + W[r] <= L) {
            l++;
            r--;
        } else {
            return false;
        }
    }
    return true;
}

// 任务二：二分校验的 DP
int dfs2(int u, int p, int L) {
    vector<int> W;
    for (int v : adj[u]) {
        if (v == p) continue;
        int res = dfs2(v, u, L);
        if (res == -1) return -1;
        if (res + 1 > L) return -1;
        W.push_back(res + 1);
    }
    sort(W.begin(), W.end());
    int C = W.size();

    if (p == -1) { // 根节点
        if (C % 2 == 0) {
            if (can_pair_skip(W, L, -1, -1)) return 0;
            return -1;
        } else {
            for (int i = 0; i < C; i++) {
                if (can_pair_skip(W, L, i, -1)) return 0;
            }
            return -1;
        }
    } else {
        if (C % 2 == 0) { // d(u) 为奇数，必须留2个不互相配对（其中1个去跟父边配对，1个成为终点）
            if (can_pair_skip(W, L, -1, -1)) return 0; // 或者0个不配对，父节点成为终点，向上传递长度为0
            for (int i = 0; i < C; i++) {
                for (int j = i + 1; j < C; j++) {
                    // W[i] 是更小的，优先用它向上传递
                    if (can_pair_skip(W, L, i, j)) return W[i];
                }
            }
            return -1;
        } else { // d(u) 为偶数，必须留1个去跟父边配对
            for (int i = 0; i < C; i++) {
                if (can_pair_skip(W, L, i, -1)) return W[i];
            }
            return -1;
        }
    }
}

// 任务三：精确计算合法匹配数量的 DP
vector<pair<int, long long>> dfs3(int u, int p, int L) {
    vector<vector<pair<int, long long>>> W;
    vector<long long> S;
    for (int v : adj[u]) {
        if (v == p) continue;
        auto child_dp = dfs3(v, u, L);
        vector<pair<int, long long>> w_i;
        long long s_i = 0;
        for (auto& state : child_dp) {
            if (state.first + 1 <= L) {
                w_i.push_back({state.first + 1, state.second});
                s_i = (s_i + state.second) % MOD;
            }
        }
        W.push_back(w_i);
        S.push_back(s_i);
    }

    int C = W.size();
    if (C == 0) {
        return {{0, 1}}; // 叶子节点，向上传递长度0的方法有1种
    }

    // 计算 M[i][j]: 孩子 i 和孩子 j 配对且长度 <= L 的方案数
    vector<vector<long long>> M(C, vector<long long>(C, 0));
    for (int i = 0; i < C; i++) {
        for (int j = i + 1; j < C; j++) {
            long long total = 0;
            vector<long long> pref(W[j].size() + 1, 0);
            for (size_t k = 0; k < W[j].size(); k++) {
                pref[k + 1] = (pref[k] + W[j][k].second) % MOD;
            }
            int ptr = (int)W[j].size() - 1;
            for (size_t k = 0; k < W[i].size(); k++) {
                int max_y = L - W[i][k].first;
                while (ptr >= 0 && W[j][ptr].first > max_y) ptr--;
                if (ptr >= 0) {
                    total = (total + W[i][k].second * pref[ptr + 1]) % MOD;
                }
            }
            M[i][j] = total;
            M[j][i] = total;
        }
    }

    // 状态压缩 DP：计算子节点间的配对情况
    vector<unsigned long long> match_dp(1 << C, 0);
    match_dp[0] = 1;
    for (int mask = 1; mask < (1 << C); mask++) {
        int pc = __builtin_popcount(mask);
        if (pc % 2 != 0) continue;
        int i = __builtin_ctz(mask);
        unsigned long long ways = 0;
        int rem = mask ^ (1 << i);
        while (rem) {
            int j = __builtin_ctz(rem);
            ways += (unsigned long long)M[i][j] * match_dp[mask ^ (1 << i) ^ (1 << j)];
            rem &= rem - 1; // 清除最低位的 1
        }
        match_dp[mask] = ways % MOD;
    }

    if (p == -1) { // 根节点，直接结算最终总答案
        long long ans3 = 0;
        if (C % 2 == 0) {
            ans3 = match_dp[(1 << C) - 1];
        } else {
            for (int m = 0; m < C; m++) {
                long long ways = (S[m] * match_dp[((1 << C) - 1) ^ (1 << m)]) % MOD;
                ans3 = (ans3 + ways) % MOD;
            }
        }
        return {{0, ans3}};
    }

    // 非根节点，整合出传给上层的结果
    vector<pair<int, long long>> flat;
    if (C % 2 == 0) {
        flat.push_back({0, match_dp[(1 << C) - 1]});
        for (int k = 0; k < C; k++) {
            long long coeff = 0;
            for (int m = 0; m < C; m++) {
                if (m == k) continue;
                long long ways = (S[m] * match_dp[((1 << C) - 1) ^ (1 << k) ^ (1 << m)]) % MOD;
                coeff = (coeff + ways) % MOD;
            }
            if (coeff > 0) {
                for (auto& a : W[k]) {
                    flat.push_back({a.first, (a.second * coeff) % MOD});
                }
            }
        }
    } else {
        for (int k = 0; k < C; k++) {
            long long coeff = match_dp[((1 << C) - 1) ^ (1 << k)];
            if (coeff > 0) {
                for (auto& a : W[k]) {
                    flat.push_back({a.first, (a.second * coeff) % MOD});
                }
            }
        }
    }

    // 相同向上长度的状态方案数合并（保证按长度去重）
    sort(flat.begin(), flat.end());
    vector<pair<int, long long>> res;
    for (auto& state : flat) {
        if (res.empty() || res.back().first != state.first) {
            res.push_back(state);
        } else {
            res.back().second = (res.back().second + state.second) % MOD;
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n)) return 0;

    if (n == 1) {
        cout << 0 << " " << 0 << " " << 1 << "\n";
        return 0;
    }

    vector<int> degree(n + 1, 0);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        degree[u]++;
        degree[v]++;
    }

    // 任务一：奇数度节点总数的一半
    int odd_count = 0;
    for (int i = 1; i <= n; i++) {
        if (degree[i] % 2 != 0) odd_count++;
    }
    int ans1 = odd_count / 2;

    // 任务二：二分答案，寻找最小的最大路径长度
    int l = 1, r = n - 1, ans2 = n - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (dfs2(1, -1, mid) != -1) {
            ans2 = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    // 任务三：运行计数 DP
    auto root_res = dfs3(1, -1, ans2);
    long long ans3 = root_res[0].second;

    cout << ans1 << " " << ans2 << " " << ans3 << "\n";

    return 0;
}