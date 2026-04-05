#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct FastScanner {
    static constexpr int S = 1 << 20;
    int idx = 0, len = 0;
    char buf[S];

    inline char gc() {
        if (idx == len) {
            len = (int)fread(buf, 1, S, stdin);
            idx = 0;
            if (!len) return EOF;
        }
        return buf[idx++];
    }

    template <class T>
    void read(T &x) {
        char c = gc();
        while (c < '0' || c > '9') c = gc();
        x = 0;
        while ('0' <= c && c <= '9') {
            x = x * 10 + (c - '0');
            c = gc();
        }
    }
} in;

static constexpr int MAXN = 100000 + 5;
static constexpr ll INF = (ll)4e18;

int T, n, type_id;
vector<int> gph[MAXN];

int root_centroid;
int parent_[MAXN], depth_[MAXN], sz[MAXN], heavy[MAXN], height_[MAXN];
int sub_median[MAXN], out_median[MAXN];
int sub_border[MAXN], out_border[MAXN];
int pick[MAXN];

ll sub_dist[MAXN], out_dist[MAXN], total_dist[MAXN];
ll sub_cost[MAXN], out_cost[MAXN], ans[MAXN];

ll pool[MAXN * 3], aux[MAXN];
ll *ptr_pool, *down_dp[MAXN], *up_dp[MAXN];

void find_centroid(int u, int p) {
    sz[u] = 1;
    int mx = 0;
    for (int v : gph[u]) if (v != p) {
        find_centroid(v, u);
        sz[u] += sz[v];
        mx = max(mx, sz[v]);
    }
    mx = max(mx, n - sz[u]);
    if (mx * 2 <= n) root_centroid = u;
}

void build_subtree_info(int u, int p) {
    parent_[u] = p;
    depth_[u] = depth_[p] + 1;
    sz[u] = 1;
    heavy[u] = 0;
    sub_dist[u] = 0;

    for (int v : gph[u]) if (v != p) {
        build_subtree_info(v, u);
        sz[u] += sz[v];
        sub_dist[u] += sub_dist[v] + sz[v];
        if (sz[v] > sz[heavy[u]]) heavy[u] = v;
    }

    int s = heavy[u];
    if (sz[s] * 2 <= sz[u]) {
        sub_median[u] = u;
        sub_cost[u] = sub_dist[u];
    } else {
        int x = sub_median[s];
        sub_cost[u] = sub_cost[s]
                    + (sub_dist[u] - sub_dist[s] - sz[s])
                    + 1LL * (depth_[x] - depth_[u]) * (sz[u] - sz[s]);
        while (sz[x] * 2 < sz[u]) {
            sub_cost[u] -= sz[u] - 2LL * sz[x];
            x = parent_[x];
        }
        sub_median[u] = x;
    }
    sub_border[u] = depth_[sub_median[u]] - depth_[u];
}

void build_out_dist(int u, int p) {
    for (int v : gph[u]) if (v != p) {
        out_dist[v] = out_dist[u] + sub_dist[u] - sub_dist[v] - sz[v] + (n - sz[v]);
        build_out_dist(v, u);
    }
}

void build_outside_info(int u, int p) {
    for (int v : gph[u]) if (v != p) build_outside_info(v, u);

    int x = pick[sz[u]];
    out_median[u] = x;
    out_border[u] = depth_[u] + depth_[x];
    out_cost[u] = sub_dist[x] + out_dist[x] - sub_dist[u] - 1LL * sz[u] * out_border[u];
}

void build_height(int u, int p) {
    heavy[u] = 0;
    for (int v : gph[u]) if (v != p) {
        build_height(v, u);
        if (height_[v] > height_[heavy[u]]) heavy[u] = v;
    }
    height_[u] = height_[heavy[u]] + 1;
}

inline void alloc_light(int u) {
    ptr_pool += height_[u];
    down_dp[u] = ptr_pool;
    ptr_pool += height_[u];
    up_dp[u] = ptr_pool + 1;
    ptr_pool += height_[u];
}

void pull_dp(int u, int p) {
    if (heavy[u]) {
        down_dp[heavy[u]] = down_dp[u] - 1;
        up_dp[heavy[u]] = up_dp[u] + 1;
        pull_dp(heavy[u], u);
    }

    int mxh = 0;
    vector<int> light_sons;

    for (int v : gph[u]) if (v != p && v != heavy[u]) {
        alloc_light(v);
        pull_dp(v, u);
        light_sons.push_back(v);
        mxh = max(mxh, height_[v]);

        for (int d = 0; d < height_[v]; ++d) {
            up_dp[v][d] = min(up_dp[v][d], down_dp[u][d + 1]);
        }
    }

    for (int i = 0; i < mxh; ++i) aux[i] = INF;
    for (int v : light_sons) {
        for (int d = 0; d < height_[v]; ++d) {
            up_dp[v][d] = min(up_dp[v][d], aux[d]);
        }
        for (int d = 2; d <= height_[v]; ++d) {
            aux[d - 2] = min(aux[d - 2], down_dp[v][d]);
        }
    }

    reverse(light_sons.begin(), light_sons.end());
    for (int i = 0; i < mxh; ++i) aux[i] = INF;
    for (int v : light_sons) {
        for (int d = 0; d < height_[v]; ++d) {
            up_dp[v][d] = min(up_dp[v][d], aux[d]);
        }
        for (int d = 2; d <= height_[v]; ++d) {
            aux[d - 2] = min(aux[d - 2], down_dp[v][d]);
        }
    }

    for (int v : gph[u]) if (v != p && v != heavy[u]) {
        for (int d = 1; d <= height_[v]; ++d) {
            down_dp[u][d - 1] = min(down_dp[u][d - 1], down_dp[v][d]);
        }
    }

    if (heavy[u]) ans[u] = min(ans[u], total_dist[u] + down_dp[u][0]);
    if (!p) return;

    int d = sub_border[u];
    ll base = sub_cost[u] - sub_dist[u];
    if (d) down_dp[u][d] = min(down_dp[u][d], base - 1LL * d * sz[u]);
    down_dp[u][d + 1] = min(down_dp[u][d + 1], base - 1LL * (d + 1) * sz[u]);
}

void push_dp(int u, int p) {
    if (p) {
        int d = out_border[u] - 1;
        ll base = out_cost[u] - out_dist[u];
        if (d > 0 && d - 1 < height_[u]) {
            up_dp[u][d - 1] = min(up_dp[u][d - 1], base - 1LL * (d - 1) * (n - sz[u]));
        }
        if (d < height_[u]) {
            up_dp[u][d] = min(up_dp[u][d], base - 1LL * d * (n - sz[u]));
        }
    }

    ans[u] = min(ans[u], total_dist[u] + up_dp[u][0]);

    for (int v : gph[u]) if (v != p && v != heavy[u]) {
        for (int d = 0; d < height_[v]; ++d) {
            up_dp[v][d] = min(up_dp[v][d], up_dp[u][d + 1]);
        }
    }
    for (int v : gph[u]) if (v != p && v != heavy[u]) {
        for (int d = 2; d <= height_[v]; ++d) {
            up_dp[u][d - 1] = min(up_dp[u][d - 1], down_dp[v][d]);
        }
    }
    for (int v : gph[u]) if (v != p) push_dp(v, u);
}

void solve() {
    in.read(n), in.read(type_id);
    for (int i = 1; i <= n; ++i) gph[i].clear();

    for (int i = 1, u, v; i < n; ++i) {
        in.read(u), in.read(v);
        gph[u].push_back(v);
        gph[v].push_back(u);
    }

    if (n == 1) {
        puts("0");
        return;
    }

    depth_[0] = -1;

    find_centroid(1, 0);

    build_subtree_info(root_centroid, 0);

    out_dist[root_centroid] = 0;
    build_out_dist(root_centroid, 0);

    fill(pick, pick + n + 1, 0);
    pick[0] = root_centroid;
    for (int u = heavy[root_centroid]; u; u = heavy[u]) {
        pick[n - 2 * sz[u]] = u;
    }
    for (int i = 1; i <= n; ++i) {
        if (!pick[i]) pick[i] = pick[i - 1];
    }

    int second_chain = 0;
    for (int v : gph[root_centroid]) if (v != heavy[root_centroid]) {
        build_outside_info(v, root_centroid);
        if (sz[v] > sz[second_chain]) second_chain = v;
    }

    fill(pick, pick + n + 1, 0);
    pick[0] = root_centroid;
    for (int u = second_chain; u; u = heavy[u]) {
        pick[n - 2 * sz[u]] = u;
    }
    for (int i = 1; i <= n; ++i) {
        if (!pick[i]) pick[i] = pick[i - 1];
    }
    build_outside_info(heavy[root_centroid], root_centroid);

    for (int i = 1; i <= n; ++i) {
        total_dist[i] = sub_dist[i] + out_dist[i];
        ans[i] = total_dist[i];
    }

    build_height(root_centroid, 0);

    fill(pool, pool + 3 * n + 5, INF);
    ptr_pool = pool;
    alloc_light(root_centroid);

    pull_dp(root_centroid, 0);
    push_dp(root_centroid, 0);

    if (type_id == 1) {
        ll best = ans[1];
        for (int i = 2; i <= n; ++i) best = min(best, ans[i]);
        printf("%lld\n", best);
    } else if (type_id == 2) {
        printf("%lld\n", ans[1]);
    } else {
        for (int i = 1; i <= n; ++i) {
            printf("%lld%c", ans[i], " \n"[i == n]);
        }
    }
}

int main() {
    in.read(T);
    while (T--) solve();
    return 0;
}