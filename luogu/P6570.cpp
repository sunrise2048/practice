#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 18;
const int mod = 1e9 + 7;
int n;
int f[N + 1][1 << N];
ll g[N + 1];
int cn[1 << N];
bool isp[(1 << N) + 5];
int phi[(1 << N) + 5];
ll ny[(1 << N) + 5];
vector<int> pr;
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
    const int n = (1 << ::n);
    phi[1] = 1;
    for (int i = 2;i <= n;++i) {
        if (!isp[i]) {
            phi[i] = i - 1;
            pr.push_back(i);
        }
        for (int p : pr) {
            if (i * p > n)break;
            isp[i * p] = 1;
            if (i % p == 0) {
                phi[i * p] = phi[i] * p;
                break;
            }
            else phi[i * p] = phi[i] * (p - 1);
        }
    }
    ny[0] = ny[1] = 1;
    for (int i = 2;i <= n;++i)ny[i] = ny[mod % i] * (mod - mod / i) % mod;
}
ll bs = 1;
void FWT(int f[], int op) {
    if (op == 1) {
        for (int k = 1;k < (1 << n);k <<= 1) {
            for (int i = 0;i < (1 << n);i += (k << 1)) {
                for (int j = 0;j < k;++j) {
                    f[i + j + k] += f[i + j];
                    f[i + j + k] >= mod ? f[i + j + k] -= mod : 0;
                }
            }
        }
    }
    else {
        for (int k = 1;k < (1 << n);k <<= 1) {
            for (int i = 0;i < (1 << n);i += (k << 1)) {
                for (int j = 0;j < k;++j) {
                    f[i + j + k] -= f[i + j];
                    f[i + j + k] < 0 ? f[i + j + k] += mod : 0;
                }
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin >> n;
    int m = 0;
    for (int i = 1;i <= n;++i) {
        int a;
        cin >> a;
        if (a == 0) {
            bs = bs * 2 % mod;
            continue;
        }
        while ((1 << m) <= a)++m;
        cn[a]++;
    }
    n = m;
    init();
    for (int i = 1;i < (1 << n);++i) {
        int bcn = __builtin_popcount(i);
        f[bcn][i] = cn[i];
    }
    for (int i = 0;i <= n;++i)FWT(f[i], 1);
    for (int i = 0;i < (1 << n);++i) {
        g[0] = 1;
        for (int j = 1;j <= n;++j) {
            f[j][i] = 1ll * f[j][i] * j % mod;
            g[j] = 0;
            for (int k = 0;k < j;++k) {
                g[j] = (g[j] + g[k] * f[j - k][i]) % mod;
            }
            g[j] = g[j] * ny[j] % mod;
        }
        for (int j = 0;j <= n;++j)f[j][i] = g[j];
    }
    for (int i = 0;i <= n;++i)FWT(f[i], -1);
    ll ans = 0;
    for (int i = 0;i < (1 << n);++i) {
        ans = (ans + 1ll * f[__builtin_popcount(i)][i] * phi[i + 1]) % mod;
    }
    ans = ans * bs % mod;
    cout << ans << '\n';
    return 0;
}