#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1005;
const int mod = 998244353;
int n, a, b, c, d;
ll jc[N], ny[N];
ll f[4][N];
ll g[2][N];
ll ksm(ll x, int y = mod - 2) {
    ll an = 1;
    while (y) {
        if (y & 1)an = an * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return an;
}
ll C(int x, int y) {
    return jc[x] * ny[y] % mod * ny[x - y] % mod;
}
void add(int op, int id) {
    f[op][id] = ny[id];
    const int top = op / 2;
    for (int i = 0;i + id <= n;++i) {
        g[top][i + id] = (g[top][i + id] + f[op ^ 1][i] * ny[id]) % mod;
    }
}
ll get(int s) {
    ll ans = 0;
    for (int i = 0;i <= s;++i) {
        ans = (ans + g[0][i] * g[1][s - i]) % mod;
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin >> n >> a >> b >> c >> d;
    jc[0] = 1;
    for (int i = 1;i <= n;++i)jc[i] = jc[i - 1] * i % mod;
    ny[n] = ksm(jc[n]);
    for (int i = n;i;--i)ny[i - 1] = ny[i] * i % mod;
    const int lm = 1000;
    ll ans = 0;
    for (int i = lm;i >= 0;--i) {
        if (a >= i)add(0, a - i);
        if (b >= i)add(1, b - i);
        if (c >= i)add(2, c - i);
        if (d >= i)add(3, d - i);
        if (i * 4 > n)continue;
        ll sum = C(n - 3 * i, i) * jc[n - 4 * i] % mod * get(n - 4 * i) % mod;
        if (i & 1)ans = (ans - sum + mod) % mod;
        else ans = (ans + sum) % mod;
    }
    cout << ans << '\n';
    return 0;
}