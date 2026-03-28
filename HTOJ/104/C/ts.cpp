#include <bits/stdc++.h>
using namespace std;

struct State {
    int d, f, cost; // d: nearest internal tower to anchor, f: farthest uncovered to anchor (-1 means none)
};

static inline bool dom(const State& a, const State& b) {
    // a dominates b
    return a.cost <= b.cost && a.d <= b.d && a.f <= b.f &&
           (a.cost < b.cost || a.d < b.d || a.f < b.f);
}

struct Solver {
    int n, m, k;
    vector<int> U, V;
    vector<vector<pair<int,int>>> g;

    // DFS on original graph
    vector<int> dep, fa, faE, vis;
    vector<int> edgeCycle;                 // 0 = bridge / not in any cycle, >0 cycle id
    vector<vector<int>> cycles;           // 1-based cycle id -> ordered vertices on that cycle
    int cycleCnt = 0;

    // block tree
    int tot;
    vector<vector<int>> tree;             // 1..n are original vertices, n+1..n+cycleCnt are cycle blocks

    // DP frontier on block tree
    vector<vector<State>> frontier;

    Solver(int _n, int _m, int _k): n(_n), m(_m), k(_k) {
        U.resize(m + 1);
        V.resize(m + 1);
        g.assign(n + 1, {});
        dep.assign(n + 1, 0);
        fa.assign(n + 1, 0);
        faE.assign(n + 1, 0);
        vis.assign(n + 1, 0);
        edgeCycle.assign(m + 1, 0);
    }

    void addEdge(int id, int u, int v) {
        U[id] = u;
        V[id] = v;
        g[u].push_back({v, id});
        g[v].push_back({u, id});
    }

    // 在边仙人掌中，DFS 时每条返祖边唯一对应一个简单环
    void dfsCycle(int u, int peid) {
        vis[u] = 1;
        for (auto [v, id] : g[u]) {
            if (id == peid) continue;
            if (!vis[v]) {
                fa[v] = u;
                faE[v] = id;
                dep[v] = dep[u] + 1;
                dfsCycle(v, id);
            } else if (dep[v] < dep[u]) {
                // 返祖边 u -> v
                if (edgeCycle[id]) continue; // 已处理过
                ++cycleCnt;
                vector<int> path;
                int x = u;
                edgeCycle[id] = cycleCnt;
                while (x != v) {
                    path.push_back(x);
                    edgeCycle[faE[x]] = cycleCnt;
                    x = fa[x];
                }
                reverse(path.begin(), path.end());
                vector<int> cyc;
                cyc.push_back(v);
                for (int y : path) cyc.push_back(y);
                cycles.push_back(cyc); // cycles[cycleCnt-1]
            }
        }
    }

    vector<State> prune(vector<State> a) {
        if (a.empty()) return a;

        map<pair<int,int>, int> best;
        for (auto &s : a) {
            auto key = make_pair(s.d, s.f);
            auto it = best.find(key);
            if (it == best.end() || s.cost < it->second) best[key] = s.cost;
        }

        vector<State> b;
        b.reserve(best.size());
        for (auto &it : best) {
            b.push_back({it.first.first, it.first.second, it.second});
        }

        int S = (int)b.size();
        vector<char> dead(S, 0);
        for (int i = 0; i < S; ++i) {
            if (dead[i]) continue;
            for (int j = 0; j < S; ++j) {
                if (i == j || dead[i]) continue;
                if (dom(b[j], b[i])) dead[i] = 1;
            }
        }

        vector<State> c;
        for (int i = 0; i < S; ++i) if (!dead[i]) c.push_back(b[i]);
        return c;
    }

    State normalizeState(State s, bool canPlaceHere) {
        if (s.f != -1 && s.d <= k && s.d + s.f <= k) {
            s.f = -1;
        }
        if (canPlaceHere && s.f == k) {
            ++s.cost;
            s.d = 0;
            s.f = -1;
        }
        return s;
    }

    vector<State> shiftFrontier(const vector<State>& A, int delta) {
        vector<State> B;
        B.reserve(A.size());
        for (auto s : A) {
            if (s.d <= k) s.d = min(k + 1, s.d + delta);
            else s.d = k + 1;
            if (s.f != -1) s.f = min(k, s.f + delta);
            B.push_back(s);
        }
        return prune(B);
    }

    vector<State> mergeFrontier(const vector<State>& A, const vector<State>& B, bool canPlaceHere) {
        vector<State> raw;
        raw.reserve((size_t)A.size() * (size_t)B.size());
        for (auto &x : A) {
            for (auto &y : B) {
                State z;
                z.d = min(x.d, y.d);
                z.f = max(x.f, y.f);
                z.cost = x.cost + y.cost;
                z = normalizeState(z, canPlaceHere);
                raw.push_back(z);
            }
        }
        return prune(raw);
    }

    vector<State> baseVertexFrontier() {
        // 只有自己这个点，允许交给父亲覆盖
        vector<State> a = { {k + 1, 0, 0} };
        return prune(a);
    }

    vector<State> baseCycleAnchorFrontier() {
        // 环块锚点本身不属于这个 child block
        vector<State> a = { {k + 1, -1, 0} };
        return a;
    }

    vector<State> buildChainFrontier(const vector<int>& seq) {
        // seq: 从靠近锚点到远离锚点的顺序
        if (seq.empty()) return {};
        vector<State> cur = frontier[seq.back()];
        for (int i = (int)seq.size() - 2; i >= 0; --i) {
            vector<State> child = shiftFrontier(cur, 1);      // 链边长度 1
            cur = mergeFrontier(frontier[seq[i]], child, true);
        }
        return cur; // anchored at seq[0]
    }

    vector<State> solveCycleBlock(int blockId, int parentVertex) {
        const vector<int>& cyc0 = cycles[blockId - n - 1];
        int c = (int)cyc0.size();

        int pos = -1;
        for (int i = 0; i < c; ++i) {
            if (cyc0[i] == parentVertex) {
                pos = i;
                break;
            }
        }

        vector<int> cyc(c);
        for (int i = 0; i < c; ++i) cyc[i] = cyc0[(pos + i) % c];

        vector<State> all;

        // 枚举断边：cut between cyc[p] and cyc[(p+1)%c]
        // 旋转后锚点是 cyc[0]
        for (int p = 0; p < c; ++p) {
            vector<int> leftSeq, rightSeq;

            // left chain: cyc[1..p]
            for (int i = 1; i <= p; ++i) leftSeq.push_back(cyc[i]);

            // right chain: cyc[c-1 .. p+1]
            for (int i = c - 1; i >= p + 1; --i) rightSeq.push_back(cyc[i]);

            vector<State> cur = baseCycleAnchorFrontier();

            if (!leftSeq.empty()) {
                vector<State> lf = buildChainFrontier(leftSeq);
                lf = shiftFrontier(lf, 1); // merge into anchor
                cur = mergeFrontier(cur, lf, false); // 环块锚点不能在这里决定放塔
            }

            if (!rightSeq.empty()) {
                vector<State> rf = buildChainFrontier(rightSeq);
                rf = shiftFrontier(rf, 1);
                cur = mergeFrontier(cur, rf, false);
            }

            for (auto &s : cur) all.push_back(s);
        }

        return prune(all);
    }

    void dfsBlockTree(int u, int p) {
        for (int v : tree[u]) {
            if (v == p) continue;
            dfsBlockTree(v, u);
        }

        if (u <= n) {
            vector<State> cur = baseVertexFrontier();
            for (int v : tree[u]) {
                if (v == p) continue;
                vector<State> child = frontier[v];
                if (v <= n) child = shiftFrontier(child, 1); // bridge edge
                // cycle block child: anchor is same vertex, no shift
                cur = mergeFrontier(cur, child, true);
            }
            frontier[u] = cur;
        } else {
            frontier[u] = solveCycleBlock(u, p);
        }
    }

    long long solve() {
        cycles.clear();
        cycleCnt = 0;
        dep[1] = 1;
        dfsCycle(1, 0);

        tot = n + cycleCnt;
        tree.assign(tot + 1, {});

        // add cycle blocks
        for (int cid = 1; cid <= cycleCnt; ++cid) {
            int block = n + cid;
            for (int v : cycles[cid - 1]) {
                tree[block].push_back(v);
                tree[v].push_back(block);
            }
        }

        // add bridges
        for (int id = 1; id <= m; ++id) {
            if (edgeCycle[id] == 0) {
                int u = U[id], v = V[id];
                tree[u].push_back(v);
                tree[v].push_back(u);
            }
        }

        frontier.assign(tot + 1, {});
        dfsBlockTree(1, 0);

        long long ans = (1LL << 60);
        for (auto s : frontier[1]) {
            long long val = s.cost + (s.f == -1 ? 0 : 1); // root 没有父亲，若仍有需求只能在 root 放塔
            ans = min(ans, val);
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, m, k;
        cin >> n >> m >> k;
        Solver solver(n, m, k);
        for (int i = 1; i <= m; ++i) {
            int u, v;
            cin >> u >> v;
            solver.addEdge(i, u, v);
        }
        cout << solver.solve() << '\n';
    }
    return 0;
}