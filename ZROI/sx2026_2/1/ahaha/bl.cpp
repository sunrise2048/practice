#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int N = 100005;
const int S = 10000;

int n;
int a[6][N], b[N];
long long f[N], s[N], S_in[N];

// Bitset 模拟与实现简化（实际中可使用手动封装的 uint64_t 数组来代替 std::bitset，方便做 byte 强转）
struct FastBitset {
    vector<uint64_t> data;
    FastBitset() {}
    FastBitset(int sz) { data.assign((sz + 63) / 64, 0); }
    void set(int p) { data[p / 64] |= (1ULL << (p % 64)); }
    bool test(int p) const { return (data[p / 64] >> (p % 64)) & 1; }
    void AND(const FastBitset& o) {
        for (size_t i = 0; i < data.size(); ++i) data[i] &= o.data[i];
    }
};

int pre_f[N / 8 + 2][256];
int pre_s[N / 8 + 2][256];

int main() {
    freopen("ex_ahaha2.in","r",stdin);
    freopen("ahaha.ans","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 1. 输入数据
    cin >> n;
    for(int i=0;i<n;++i){
        for(int j=0;j<6;++j)cin>>a[j][i];
    }
    for (int i = 0; i < n; ++i) cin >> b[i];

    for (int i = 0; i < n; ++i) {
        f[i] = 1;
        S_in[i] = 0;
    }

    // 2. 分块处理
    for (int L = 0; L * S < n; ++L) {
        int V_start = L * S;
        int V_end = min(n, V_start + S);
        int cur_S = V_end - V_start;
        if (V_start == 0) { goto INTERNAL_DP; }

        // --- 外部贡献计算 ---
        {
            // 预处理 8-bit chunk 查表
            int num_bytes = V_start / 8;
            for (int i = 0; i < num_bytes; ++i) {
                for (int mask = 0; mask < 256; ++mask) {
                    long long sum_f = 0, sum_s = 0;
                    for (int bit = 0; bit < 8; ++bit) {
                        if ((mask >> bit) & 1) {
                            int u = i * 8 + bit;
                            sum_f = (sum_f + f[u]);
                            if (sum_f >= MOD) sum_f -= MOD;
                            sum_s = (sum_s + s[u]);
                            if (sum_s >= MOD) sum_s -= MOD;
                        }
                    }
                    pre_f[i][mask] = sum_f;
                    pre_s[i][mask] = sum_s;
                }
            }

            vector<FastBitset> res(cur_S, FastBitset(V_start));
            for (int v = 0; v < cur_S; ++v) {
                for(auto& val : res[v].data) val = ~0ULL;
            }

            for (int j = 0; j < 6; ++j) {
                vector<int> V_idx(cur_S), U_idx(V_start);
                iota(V_idx.begin(), V_idx.end(), V_start);
                iota(U_idx.begin(), U_idx.end(), 0);
                
                auto cmp = [&](int x, int y) { return a[j][x] < a[j][y]; };
                sort(V_idx.begin(), V_idx.end(), cmp);
                sort(U_idx.begin(), U_idx.end(), cmp);

                FastBitset cur(V_start);
                int p = 0;
                for (int v : V_idx) {
                    while (p < V_start && a[j][U_idx[p]] < a[j][v]) {
                        cur.set(U_idx[p]);
                        p++;
                    }
                    res[v - V_start].AND(cur);
                }
            }

            // 查表累加
            for (int v = V_start; v < V_end; ++v) {
                uint8_t* byte_ptr = (uint8_t*)res[v - V_start].data.data();
                long long cur_f = 0, cur_s = 0;
                for (int i = 0; i < num_bytes; ++i) {
                    cur_f = (cur_f + pre_f[i][byte_ptr[i]]) % MOD;
                    cur_s = (cur_s + pre_s[i][byte_ptr[i]]) % MOD;
                }
                f[v] = (f[v] + cur_f) % MOD;
                S_in[v] = (S_in[v] + cur_s) % MOD;
            }
        }

        INTERNAL_DP:
        // --- 内部 DP 计算 ---
        vector<FastBitset> valid(cur_S, FastBitset(cur_S));
        for (int v = 0; v < cur_S; ++v) {
            for(auto& val : valid[v].data) val = ~0ULL;
        }

        for (int j = 0; j < 6; ++j) {
            vector<int> V_idx(cur_S);
            iota(V_idx.begin(), V_idx.end(), 0);
            sort(V_idx.begin(), V_idx.end(), [&](int x, int y) { 
                return a[j][x + V_start] < a[j][y + V_start]; 
            });

            FastBitset cur(cur_S);
            for (int v : V_idx) {
                valid[v].AND(cur);
                cur.set(v);
            }
        }

        for (int v = 0; v < cur_S; ++v) {
            int real_v = v + V_start;
            for (int u = 0; u < v; ++u) {
                if (valid[v].test(u)) {
                    int real_u = u + V_start;
                    f[real_v] = (f[real_v] + f[real_u]) % MOD;
                    S_in[real_v] = (S_in[real_v] + s[real_u]) % MOD;
                }
            }
            s[real_v] = (b[real_v] * f[real_v] % MOD + S_in[real_v]) % MOD;
        }
    }

    // 3. 汇总答案
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = (ans + s[i]) % MOD;
    }
    cout << ans << "\n";
    return 0;
}