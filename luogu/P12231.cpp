#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 20;
const int mod = 998244353;
int n;
ll f[N + 1][1 << N];
ll g[N + 1];
ll ny[N + 1];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin >> n;
    for (int i = 0;i < (1 << n);++i) {
        cin >> f[__builtin_popcount(i)][i];
    }
    for (int t = 0;t <= n;++t) {
        for (int k = 1;k < (1 << n);k <<= 1) {
            for (int i = 0;i < (1 << n);i += (k << 1)) {
                for (int j = 0;j < k;++j) {
                    f[t][i + j + k] = (f[t][i + j + k] + f[t][i + j]) % mod;
                }
            }
        }
    }
    ny[0] = ny[1] = 1;
    for (int i = 2;i <= n;++i)ny[i] = ny[mod % i] * (mod - mod / i) % mod;
    for (int i = 0;i < (1 << n);++i) {
        g[0] = 0;
        for (int j = 1;j <= n;++j) {
            g[j] = 0;
            for (int k = 0;k < j;++k) {
                g[j] = (g[j] + f[j - k][i] * g[k] % mod * k) % mod;
            }
            g[j] = (f[j][i] - g[j] * ny[j] % mod + mod) % mod;
        }
        for (int j = 0;j <= n;++j)f[j][i] = g[j];
    }
    for (int t = 0;t <= n;++t) {
        for (int k = 1;k < (1 << n);k <<= 1) {
            for (int i = 0;i < (1 << n);i += (k << 1)) {
                for (int j = 0;j < k;++j) {
                    f[t][i + j + k] = (f[t][i + j + k] - f[t][i + j] + mod) % mod;
                }
            }
        }
    }
    for (int i = 0;i < (1 << n);++i) {
        cout << f[__builtin_popcount(i)][i] << ' ';
    }cout << '\n';
    return 0;
}