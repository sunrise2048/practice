#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 18;
const int mod = 998244353;
int n, m;
bool fl[1 << N];
int f[1 << N];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin >> n >> m;
    for (int i = 1;i <= m;++i) {
        int u, v;
        cin >> u >> v;
        --u;--v;
        for (int j = 0;j < (1 << n);++j) {
            if ((j & (1 << u)) && (j & (1 << v))) {
                fl[j] = 1;
            }
        }
    }
    f[0] = 1;
    for (int i = 1;i < (1 << n);++i) {
        int j = i;
        while (j) {
            if (!fl[j]) {
                if (__builtin_popcount(j) & 1)f[i] = (f[i] + f[i ^ j]) % mod;
                else f[i] = (f[i] - f[i ^ j] + mod) % mod;
            }
            j = (j - 1) & i;
        }
    }
    cout << 1ll * f[(1 << n) - 1] * ((mod + 1) / 2) % mod * m % mod << '\n';
    return 0;
}