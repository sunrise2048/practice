#include <bits/stdc++.h>

using namespace std;

#define lep(i, l, r) for(int i = (l); i <= (r); i ++)
#define rep(i, l, r) for(int i = (l); i >= (r); i --)
#define Lep(i, l, r) for(int i = (l); i <  (r); i ++)
#define Rep(i, l, r) for(int i = (l - 1); i >= (r); i --)
#define pb push_back
#define fi first
#define se second

using i64 = long long;
using uint = unsigned int;
using ui64 = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;

namespace io {
	struct io {
		io() {
            ios :: sync_with_stdio(false); 
            cin.tie(0); cout.tie(0);
        }
	} unname;
    struct read {
        operator int () { int x; cin >> x; return x; }
        operator i64 () { i64 x; cin >> x; return x; }
        operator char () { char x; cin >> x; return x; }
        operator double () { double x; cin >> x; return x; }
        operator string () { string x; cin >> x; return x; }
    } rd;
} ;

using io :: rd;

const int N = 4e5 + 10;

namespace Unique {
    vector<i64> unique(vector<i64> &vec) {
        sort(vec.begin(), vec.end());
        auto end = unique(vec.begin(), vec.end());
        vector<i64> res;
        for (auto it = vec.begin(); it != end; ++ it) res.push_back(* it);
        return res;
    }
} ;

#define lowbit(x) (x & -x)

struct Bit {
    i64 c[N];
    vector<int> bck;
    void upd(int x, i64 y) {
        bck.push_back(x);
        for (; x < N; x += lowbit(x)) c[x] += y;
    }
    i64 qry(int x) {
        i64 ans = 0;
        for (; x; x -= lowbit(x)) ans += c[x];
        return ans;
    }
    i64 qry(int l, int r) { return qry(r) - qry(l - 1); }
    void clr(int x) {
        for (; x < N; x += lowbit(x)) c[x] = 0;
    }
    void clr() {
        for (auto x : bck) clr(x); bck.clear(); //n = 0;
    }
} bt;

#undef lowbit

int n, m, L, C;

inline int reduce(int x, int mod) { return (x % mod + mod) % mod; }

int A[N], B[N];
int p[N];
vector<pair<int, int> > e[N];

int bel[N], tree_number, root[N], sz[N], number, dfn[N], oncir[N], fa[N][20], lg[N];
i64 dep[N], ew[N];

void dfs(int x, int fx) {
    dfn[x] = ++ number; sz[x] = 1; bel[x] = tree_number; fa[x][0] = fx;
    Lep (i, 1, 20) fa[x][i] = fa[fa[x][i - 1]][i - 1];
    for(auto p : e[x]) {
        int y = p.first, w = p.second;
        if(y == root[tree_number]) oncir[y] = 1, oncir[x] = 1;
        else dep[y] = dep[x] + w, dfs(y, x), oncir[x] |= oncir[y], sz[x] += sz[y];
    }
}

i64 Ans[N];
struct Three { i64 a, b, c; } ;
struct Qry {
    int v; i64 t; int id;
} ;
vector<Qry> qrys1, qrys2;

struct Point { i64 x, y; } ;
struct Line { i64 l1, r1, h, id, type; } ;
struct Mat { i64 l1, r1, l2, r2; } ;

/* Two-side count nodes */

namespace Count {
    vector<i64> twoside_count(vector<Mat> &mt, vector<Point> &pt) {
        vector<Line> lns;
        vector<i64> ans(mt.size());
        lep (i, 0, (int) mt.size() - 1) {
            lns.push_back( {mt[i].l1, mt[i].r1, mt[i].l2 - 1, i, -1} );
            lns.push_back( {mt[i].l1, mt[i].r1, mt[i].r2, i, 1} );
        }
        sort(lns.begin(), lns.end(), [] (Line a, Line b) { return a.h == b.h ? a.type < b.type : a.h < b.h; } );
        sort(pt.begin(), pt.end(), [] (Point a, Point b) { return a.y < b.y; } );
        int j = 0;
        bt.clr();
        for (auto p : lns) {
            while (j < pt.size() && pt[j].y <= p.h) {
                bt.upd(pt[j].x, 1); j ++;
            }
            ans[p.id] += p.type * bt.qry(p.l1, p.r1);
        }
        return ans;
    }
} 

signed main() {
#ifdef FILEIN
    freopen("1.in", "r", stdin);
#endif
    n = rd; m = rd; L = rd; C = rd;
    lep (i, 1, n) A[i] = rd;
    lep (i, 1, m) B[i] = rd;
    /* Build Tree */
    lep (i, 1, n) {
        auto it = upper_bound(A + 1, A + 1 + n, reduce(A[i] - C, L)) - A - 1;
        if(! it) it = n;
        p[i] = it;
        int w = (C + L - reduce(A[i] - A[p[i]], L) - 1) / L * L + reduce(A[i] - A[p[i]], L);
        e[p[i]].push_back( {i, w} );
        ew[i] = w;
    }
    lep (i, 2, n) lg[i] = lg[i >> 1] + 1;
    lep (i, 1, n) if (! bel[i]) {
        ++ tree_number;
        int j = i;
        while(! bel[j]) { bel[j] = tree_number; j = p[j]; }
        root[tree_number] = j;
        dfs(j, 0);
    } 
    int q = rd;
    lep (i, 1, q) {
        int v = rd; i64 t = rd;
        if(! oncir[v]) qrys1.push_back( {v, t, i} );
        else qrys2.push_back( {v, t, i} );
    }
    /* Not on circle */
    vector<pair<int, i64> > pairs;
    lep (i, 1, m) {
        auto it = upper_bound(A + 1, A + 1 + n, B[i]) - A;
        if (it == 1) it = n; else it --;
        int v0 = it, t0 = reduce(B[i] - A[it], L);
        pairs.push_back( {v0, t0} );
    }
    vector<Mat> mat;
    vector<Point> pnt;
    vector<i64> values, record;
    for (auto p : pairs) pnt.push_back( {dfn[p.first], p.second + dep[p.first]} ), values.push_back(p.second + dep[p.first]);
    for (auto p : qrys1) {
        mat.push_back( {dfn[p.v], dfn[p.v] + sz[p.v] - 1, 1, dep[p.v] + p.t} ), values.push_back(dep[p.v] + p.t);
    }
    values.push_back(1);
    values = Unique :: unique(values);
    for (auto &p : pnt) p.y = lower_bound(values.begin(), values.end(), p.y) - values.begin() + 1;
    for (auto &p : mat) 
        p.l2 = lower_bound(values.begin(), values.end(), p.l2) - values.begin() + 1, 
        p.r2 = lower_bound(values.begin(), values.end(), p.r2) - values.begin() + 1;
    record = Count :: twoside_count(mat, pnt); 
    int cnt = 0;
    for (auto &p : qrys1) Ans[p.id] = record[cnt], cnt ++;

    /* Is on circle */
    for (auto &p : pairs) {
        int &v0 = p.first;
        i64 &t0 = p.second;
        if (! oncir[v0]) {
            rep (i, 19, 0) if (fa[v0][i] && ! oncir[fa[v0][i]]) {
                t0 += dep[v0] - dep[fa[v0][i]];
                v0 = fa[v0][i];
            }
            t0 += ew[v0];
            v0 = fa[v0][0];
        }
    }
    static int vis[N], loc[N];
    memset(dep, 0, sizeof(dep));
    static vector<Qry> link_qry[N];
    static vector<pair<i64, i64> > link_pair[N];
    for (auto p : qrys2) link_qry[bel[p.v]].push_back(p);
    for (auto p : pairs) link_pair[bel[p.first]].push_back(p);
    lep (now, 1, tree_number) {
        int rt = root[now];
        int i = rt;
        vector<int> cir;
        while (! vis[i]) {
            cir.push_back(i);
            vis[i] = 1;
            i = p[i];
        }    
        cir.push_back(cir[0]);
        reverse(cir.begin(), cir.end());
        dep[cir[0]] = 0;
        lep (i, 1, (int) cir.size() - 1) dep[cir[i]] = dep[cir[i - 1]] + ew[cir[i]];
        lep (i, 0, (int) cir.size() - 2) loc[cir[i]] = i;
        i64 P = dep[cir[0]];dep[cir[0]] = 0;
        vector<pair<i64, i64> > tree_node;
        vector<Three> people_node;
        for (auto p : link_pair[now]) tree_node.push_back( {(p.second + dep[p.first]) / P, (p.second + dep[p.first]) % P} );
        for (auto p : link_qry[now]) {
            i64 delta = p.t + dep[p.v];
            people_node.push_back( {delta / P, delta % P, p.id} );
        }
        sort(tree_node.begin(), tree_node.end(), [] (pair<i64, i64> a, pair<i64, i64> b) { return a.first < b.first; } );
        sort(people_node.begin(), people_node.end(), [] (Three a, Three b) { return a.a < b.a; } );
        values.clear();
        for (auto p : tree_node) values.push_back(p.second);
        for (auto p : people_node) values.push_back(p.b);
        values = Unique :: unique(values);
        for (auto &p : tree_node) p.second = lower_bound(values.begin(), values.end(), p.second) - values.begin() + 1;
        for (auto &p : people_node) p.b = lower_bound(values.begin(), values.end(), p.b) - values.begin() + 1;
        bt.clr();
        i64 sum = 0; i = 0;
        for (auto p : people_node) {
            i64 qy = p.a, ry = p.b, id = p.c;
            while (i < tree_node.size() && tree_node[i].first <= qy) {
                sum += tree_node[i].first; 
                bt.upd(tree_node[i].second, 1);
                i ++;
            }
            Ans[id] += 1ll * i * qy - sum + bt.qry(ry);
        }
        tree_node.clear();
        people_node.clear();
        for (auto p : link_pair[now]) tree_node.push_back( {loc[p.first], p.second + dep[p.first]} );
        for (auto p : link_qry[now]) {
            i64 delta = p.t + dep[p.v];
            people_node.push_back( {loc[p.v], p.t + dep[p.v], p.id} );
        }
        values.clear();
        for (auto p : tree_node) values.push_back(p.second);
        for (auto p : people_node) values.push_back(p.b);
        values = Unique :: unique(values);
        for (auto &p : tree_node) p.second = lower_bound(values.begin(), values.end(), p.second) - values.begin() + 1;
        for (auto &p : people_node) p.b = lower_bound(values.begin(), values.end(), p.b) - values.begin() + 1;
        sort(tree_node.begin(), tree_node.end(), [] (pair<i64, i64> a, pair<i64, i64> b) { return a.first < b.first; } );
        sort(people_node.begin(), people_node.end(), [] (Three a, Three b) { return a.a < b.a; } );
        bt.clr(); i = 0;
        for (auto p : people_node) {
            i64 cj = p.a, vj = p.b, id = p.c;
            while (i < tree_node.size() && tree_node[i].first < cj) {
                bt.upd(tree_node[i].second, 1);
                i ++;
            }
            Ans[id] -= bt.qry(vj);
        }
    }

    lep (i, 1, q) printf("%lld\n", Ans[i]);
	return 0;
} 
