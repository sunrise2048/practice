#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int mod = 1e4 + 7;
ll ksm(ll x, int y = mod - 2) {
    ll an = 1;
    while (y) {
        if (y & 1)an = an * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return an;
}
ll jc[mod], ny[mod];
void init() {
    const int n = mod - 1;
    jc[0] = 1;
    for (int i = 1;i <= n;++i)jc[i] = jc[i - 1] * i % mod;
    ny[n] = ksm(jc[n]);
    for (int i = n;i;--i)ny[i - 1] = ny[i] * i % mod;
}
ll C(int x, int y) {
    if (x < y || y < 0)return 0;
    if (x < mod)return jc[x] * ny[y] % mod * ny[x - y] % mod;
    return C(x % mod, y % mod) * C(x / mod, y / mod) % mod;
}
int main() {
    int n, m;
    cin >> n >> m;
    init();
    cout << C(n * m, n - 1) * ksm(n) % mod;
    return 0;
}