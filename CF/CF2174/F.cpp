#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e4 + 5;
const int mod = 1e9 + 7;
const int p = 1e4;
int T;
int n, m;
int t[N];
int op[N];
ll jc[N], ny[N];
ll F[2][N];
ll* f, * g;
ll ksm(ll x, int y = mod - 2) {
    ll an = 1;
    while (y) {
        if (y & 1)an = an * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return an;
}
void init() {
    const int lm = 1e4;
    jc[0] = 1;
    for (int i = 1;i <= lm;++i)jc[i] = jc[i - 1] * i % mod;
    ny[lm] = ksm(jc[lm]);
    for (int i = lm;i;--i)ny[i - 1] = ny[i] * i % mod;
}
void sol1() {
    int ans = 1;
    for (int i = 1;i <= m;++i) {
        int op;
        cin >> op;
        if (op)ans = 0;
    }
    cout << ans << '\n';
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    init();
    cin >> T;
    while (T--) {
        cin >> n >> m;
        memset(t, 0, sizeof(t));
        for (int i = 1;i <= n;++i) {
            int c;
            cin >> c;
            t[c]++;
        }
        if (n == 1) {
            sol1();
            continue;
        }
        memset(F, 0, sizeof(F));
        f = F[0];
        g = F[1];
        g[p] = 1;
        for (int i = 1;i <= m;++i) {
            cin >> op[i];
            op[i] ^= (t[i] & 1);
            if (op[i]) {
                for (int j = -n;j <= n;++j)f[j + p] = 0;
                for (int j = -n;j <= n;++j) {
                    if (g[j + p] == 0)continue;
                    f[j + p + t[i]] = (f[j + p + t[i]] + g[j + p]) % mod;
                    f[j + p - t[i]] = (f[j + p - t[i]] - g[j + p] + mod) % mod;
                }
                swap(f, g);
            }
            else {
                for (int j = -n;j <= n;++j)f[j + p] = 0;
                for (int j = -n;j <= n;++j) {
                    if (g[j + p] == 0)continue;
                    f[j + p + t[i]] = (f[j + p + t[i]] + g[j + p]) % mod;
                    f[j + p - t[i]] = (f[j + p - t[i]] + g[j + p]) % mod;
                }
                swap(f, g);
            }
        }
        ll ans = 0;
        for (int i = -n;i <= n;++i) {
            ans = (ans + g[i + p] * ksm((i + mod) % mod, n - 2)) % mod;
        }
        cout << ans * ksm(ksm(2, m)) % mod << '\n';
    }
    return 0;
}