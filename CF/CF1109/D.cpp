#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 5;
const int mod = 1e9 + 7;
int n, m, a, b;
ll jc[N], ny[N];
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
    const int n = 1e6 + 1;
    jc[0] = 1;
    for (int i = 1;i <= n;++i)jc[i] = jc[i - 1] * i % mod;
    ny[n] = ksm(jc[n]);
    for (int i = n;i;--i)ny[i - 1] = ny[i] * i % mod;
}
ll C(int x, int y) {
    if (x < y || y < 0)return 0;
    return jc[x] * ny[y] % mod * ny[x - y] % mod;
}
int main() {
    cin >> n >> m >> a >> b;
    init();
    ll ans = 0;
    for (int i = 1;i < n;++i) {
        ll bs = C(m - 1, i - 1) * ksm(m, n - i - 1) % mod;
        bs = bs * C(n - 2, i - 1) % mod * jc[i - 1] % mod;
        int nn = n - i - 1;
        if (nn) {
            bs = bs * (i + 1) % mod * ksm(n, nn - 1) % mod;
        }
        ans = (ans + bs) % mod;
    }
    cout << ans << '\n';
    return 0;
}