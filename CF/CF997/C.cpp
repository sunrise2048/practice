#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int mod = 998244353;
ll ksm(ll x, ll y) {
    y %= (mod - 1);
    y = (y + mod - 1) % (mod - 1);
    ll an = 1;
    while (y) {
        if (y & 1)an = an * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return an;
}
ll n;
ll calc0() {
    ll bs = ksm(3, n * n);
    return (bs + 2 * bs % mod * (ksm((1 - ksm(3, 1 - n) + mod) % mod, n) - 1 + mod)) % mod;
}
const int N = 1e6 + 5;
ll jc[N], ny[N];
ll C(int x, int y) { return jc[x] * ny[y] % mod * ny[x - y] % mod; }
int main() {
    cin >> n;
    jc[0] = 1;
    for (int i = 1;i <= n;++i)jc[i] = jc[i - 1] * i % mod;
    ny[n] = ksm(jc[n], mod - 2);
    for (int i = n;i;--i)ny[i - 1] = ny[i] * i % mod;
    ll ans = (ksm(3, n * n) - calc0() + mod) % mod;
    ll bs = ksm(3, n * n + 1);
    for (int i = 1;i <= n;++i) {
        ans = (ans - bs * C(n, i) % mod * ((i & 1) ? mod - 1 : 1) % mod * ksm(3, -i * n) % mod * (ksm((1 - ksm(3, i - n) + mod) % mod, n) - 1 + mod) % mod + mod) % mod;
    }
    cout << ans << '\n';
    return 0;
}