#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5;
int n;
vector<int> e[N];
int si[N];
int mxd[N];
int mx1[N], mx2[N];
int hz1[N], hz2[N];
int ans[N];
void addh(int id, int x) {
    if (x > hz1[id]) {
        hz2[id] = hz1[id];
        hz1[id] = x;
    }
    else if (x > hz2[id]) {
        hz2[id] = x;
    }
}
void addv(int id, int x) {
    if (x > mx1[id]) {
        mx2[id] = mx1[id];
        mx1[id] = x;
    }
    else if (x > mx2[id]) {
        mx2[id] = x;
    }
}
class SGT {
public:
    struct node {
        int lson, rson;
        int mx;
        int d;
        int lz;
    }t[N * 200];
    int cn;
#define ls(k) t[k].lson
#define rs(k) t[k].rson
#define mid (l+r>>1)
    void pushup(int k) {
        t[k].d = min(t[ls(k)].d, t[rs(k)].d);
    }
    void add(int l, int r, int& k, int d) {
        if (!k) {
            k = ++cn;
            t[k].d = l;
        }
        t[k].d -= d;
        t[k].mx += d;
        t[k].lz += d;
    }
    void add_mx(int l, int r, int& k, int d) {
        if (!k) {
            k = ++cn;
            t[k].d = l;
        }
        t[k].mx = max(t[k].mx, d);
        t[k].d = min(t[k].d, l - d);
    }
    void pushdown(int l, int r, int k) {
        if (l == r)return;
        if (t[k].mx <= t[k].lz)t[k].mx = 0;
        if (t[k].lz) {
            add(l, mid, ls(k), t[k].lz);
            add(mid + 1, r, rs(k), t[k].lz);
            t[k].lz = 0;
        }
        if (t[k].mx) {
            add_mx(l, mid, ls(k), t[k].mx);
            add_mx(mid + 1, r, rs(k), t[k].mx);
            t[k].mx = 0;
        }
    }
    void update_add(int l, int r, int& k, int x, int y) {
        if (!k) {
            k = ++cn;
            t[k].d = l;
        }
        if (x <= l && r <= y) {
            t[k].mx++;
            t[k].lz++;
            t[k].d--;
            return;
        }
        pushdown(l, r, k);
        if (x <= mid)update_add(l, mid, ls(k), x, y);
        if (y > mid)update_add(mid + 1, r, rs(k), x, y);
        pushup(k);
    }
    void update_mx(int l, int r, int& k, int x, int y, int d) {
        if (!k) {
            k = ++cn;
            t[k].d = l;
        }
        if (x <= l && r <= y) {
            if (t[k].d <= max(d, 0)) {
                if (l == r) {
                    ans[l]++;
                    t[k].mx = 0;
                    t[k].d = l;
                    return;
                }
                pushdown(l, r, k);
                update_mx(l, mid, ls(k), x, y, d);
                update_mx(mid + 1, r, rs(k), x, y, d);
                pushup(k);
                return;
            }
            add_mx(l, r, k, d + 1);
            return;
        }
        pushdown(l, r, k);
        if (x <= mid)update_mx(l, mid, ls(k), x, y, d);
        if (y > mid)update_mx(mid + 1, r, rs(k), x, y, d);
        pushup(k);
    }
    void query(int l, int r, int k, int y) {
        if (r <= y) {
            if (l == r) {
                addv(l, t[k].mx);
                return;
            }
            pushdown(l, r, k);
            query(l, mid, ls(k), y);
            query(mid + 1, r, rs(k), y);
            return;
        }
        pushdown(l, r, k);
        query(l, mid, ls(k), y);
        if (y > mid)query(mid + 1, r, rs(k), y);
    }
}sgt;
int rt[N];
int h1, h2;
void add1(int x) {
    if (x > h1) {
        h2 = h1;
        h1 = x;
    }
    else if (x > h2)h2 = x;
}
void dfs(int no, int fa) {
    si[no] = 1;
    mxd[no] = 1;
    int zs = 0;
    for (int to : e[no]) {
        if (to == fa)continue;
        dfs(to, no);
        mxd[no] = max(mxd[no], mxd[to] + 1);
        si[no] += si[to];
        if (si[zs] < si[to])zs = to;
    }
    if (!zs) {
        sgt.update_add(2, n, rt[no], 2, n);
        return;
    }
    rt[no] = rt[zs];
    sgt.update_add(2, n, rt[no], 2, n);
    int tsi = 1;
    h1 = h2 = -1;
    for (int to : e[no]) {
        if (to == fa)continue;
        if (to == zs)continue;
        tsi = max(tsi, si[to]);
        if (si[to] != 1)sgt.query(2, n, rt[to], si[to]);
        addh(si[to] + 1, mxd[to]);
    }
    for (int i = 2;i <= tsi;++i) {
        add1(hz1[i]);add1(hz2[i]);
        hz1[i] = hz2[i] = -1;
        addv(i, h1);addv(i, h2);
        if (mx1[i] + mx2[i] + 1 >= i)sgt.update_mx(2, n, rt[no], i, i, i + 1);
        else sgt.update_mx(2, n, rt[no], i, i, mx1[i]);
        mx1[i] = mx2[i] = -1;
    }
    add1(hz1[tsi + 1]);add1(hz2[tsi + 1]);
    hz1[tsi + 1] = hz2[tsi + 1] = -1;
    if (h1 + h2 + 1 >= tsi + 1) {
        sgt.update_mx(2, n, rt[no], tsi + 1, h1 + h2 + 1, h1 + h2 + 1);
        sgt.update_mx(2, n, rt[no], h1 + h2 + 2, n, h1);
    }
    else sgt.update_mx(2, n, rt[no], tsi + 1, n, h1);
    sgt.update_mx(2, n, rt[no], 2, n, -1);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin >> n;
    for (int i = 1;i <= n;++i) {
        mx1[i] = mx2[i] = hz1[i] = hz2[i] = -1;
    }
    for (int i = 1;i < n;++i) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1, 0);
    ans[1] = n;
    for (int i = 1;i <= n;++i) {
        cout << ans[i] << '\n';
    }
    return 0;
}