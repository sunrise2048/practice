#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1 << 16;
const int mod = 998244353;
int n, m, k;
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
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin >> m >> k;
    for (int i = 1;i <= k;++i) {
        int a;
        cin >> a;
        f[a] = 1;
    }
    n = N;
    for (int k = 1;k < n;k <<= 1) {
        for (int i = 0;i < n;i += (k << 1)) {
            for (int j = 0;j < k;++j) {
                ll x = f[i + j], y = f[i + j + k];
                f[i + j] = (x + y) % mod;
                f[i + j + k] = (x - y + mod) % mod;
            }
        }
    }
    for (int i = 0;i < n;++i) {
        if (f[i] == 0)continue;
        if (f[i] == 1) {
            f[i] = m;
            continue;
        }
        f[i] = (f[i] - ksm(f[i], m + 1) + mod) % mod * ksm((1 - f[i] + mod) % mod) % mod;
    }
    for (int k = 1;k < n;k <<= 1) {
        for (int i = 0;i < n;i += (k << 1)) {
            for (int j = 0;j < k;++j) {
                ll x = f[i + j], y = f[i + j + k];
                f[i + j] = (x + y) % mod;
                f[i + j + k] = (x - y + mod) % mod;
            }
        }
    }
    ll bs = ksm(n);
    cout << ((k == 1 ? m : (k - ksm(k, m + 1) + mod) % mod * ksm((1 - k + mod) % mod)) - f[0] * bs % mod + mod) % mod << '\n';
    return 0;
}