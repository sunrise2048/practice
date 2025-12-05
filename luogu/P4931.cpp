#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e6 + 5;
const int mod = 998244353;
int T;
int n, k;
ll jc[N], ny[N];
ll er[N];
ll f[N];
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
    const int lm = 5e6;
    jc[0] = 1;
    for (int i = 1;i <= lm;++i)jc[i] = jc[i - 1] * i % mod;
    ny[lm] = ksm(jc[lm]);
    for (int i = lm;i;--i)ny[i - 1] = ny[i] * i % mod;
    er[0] = 1;
    for (int i = 1;i <= lm;++i)er[i] = er[i - 1] * 2 % mod;
    f[0] = 1;
    for (int i = 1;i < lm;++i) {
        f[i + 1] = (4ll * i * (i + 1) % mod * f[i] + 8ll * i * i % mod * (i + 1) % mod * f[i - 1]) % mod;
    }
}
ll C(int x, int y) {
    return jc[x] * ny[y] % mod * ny[x - y] % mod;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    init();
    cin >> T;
    while (T--) {
        cin >> n;
        for (int k = 0;k <= n;++k) {
            cout << C(n, k) * C(n, k) % mod * jc[k] % mod * er[k] % mod * f[n - k] % mod << '\n';
        }
    }
    return 0;
}