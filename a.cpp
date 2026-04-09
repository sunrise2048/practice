#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct BIT {
    int n;
    vector<int> t;
    BIT() {}
    BIT(int n_) { init(n_); }
    void init(int n_) {
        n = n_;
        t.assign(n + 1, 0);
    }
    void add(int x, int v) {
        for (; x <= n; x += x & -x) t[x] += v;
    }
    int sum(int x) const {
        int r = 0;
        for (; x > 0; x -= x & -x) r += t[x];
        return r;
    }
    int rangeSum(int l, int r) const {
        if (l > r) return 0;
        return sum(r) - sum(l - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> p(n);
        for (int i = 0; i < n; ++i) cin >> p[i];

        vector<int> up, dn;   // up 递增, dn 递减
        BIT bitUp(n), bitDn(n);

        ll ans = 0;
        vector<ll> out;
        out.reserve(n);

        for (int x : p) {
            int li = lower_bound(up.begin(), up.end(), x) - up.begin();
            int di = lower_bound(dn.begin(), dn.end(), x, greater<int>()) - dn.begin();

            // 1) 删除旧 up[li]
            if (li < (int)up.size()) {
                int old = up[li];
                ans -= bitDn.sum(old - 1);   // 旧 up 对答案的贡献
                bitUp.add(old, -1);
            }

            // 2) 删除旧 dn[di]
            if (di < (int)dn.size()) {
                int old = dn[di];
                ans -= bitUp.rangeSum(old + 1, n); // 旧 dn 对答案的贡献
                bitDn.add(old, -1);
            }

            // 3) 加入新 up = x
            if (li < (int)up.size()) up[li] = x;
            else up.push_back(x);
            bitUp.add(x, +1);
            ans += bitDn.sum(x - 1);

            // 4) 加入新 dn = x
            if (di < (int)dn.size()) dn[di] = x;
            else dn.push_back(x);
            ans += bitUp.rangeSum(x + 1, n);
            bitDn.add(x, +1);

            out.push_back(ans);
        }

        for (int i = 0; i < n; ++i) {
            if (i) cout << ' ';
            cout << out[i];
        }
        cout << '\n';
    }

    return 0;
}