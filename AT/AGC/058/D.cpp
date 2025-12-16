#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 3e6 + 5;
const int mod = 998244353;
int a, b, c;
ll jc[N], ny[N];
ll er[N];
ll ksm(ll x, int y = mod - 2) {
    ll an = 1;
    while (y) {
        if (y & 1)an = an * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return an;
}
void init(int n) {
    jc[0] = 1;
    for (int i = 1;i <= n;++i)jc[i] = jc[i - 1] * i % mod;
    ny[n] = ksm(jc[n]);
    for (int i = n;i;--i)ny[i - 1] = ny[i] * i % mod;
    er[0] = 1;
    for (int i = 1;i <= n;++i) {
        er[i] = er[i - 1] * (mod - 2) % mod;
    }
}
ll C(int a, int b, int c, int d) {
    if (min({ a,b,c,d }) < 0)return 0;
    return jc[a + b + c + d] * ny[a] % mod * ny[b] % mod * ny[c] % mod * ny[d] % mod;
}
int main() {
    cin >> a >> b >> c;
    init(a + b + c);
    ll ans = 0;
    const int lm = min({ a,b,c });
    for (int i = 0;i <= lm;++i) {
        ans = (ans + (C(a - i, b - i, c - i, i) - C(a - i - 1, b - i - 1, c - i - 1, i) + mod) % mod * er[i]) % mod;
    }
    cout << ans << '\n';
    return 0;
}