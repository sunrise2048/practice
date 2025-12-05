#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 105;
const int mod = 1e9 + 7;
int n;
int e[N][N];
ll mt[N][N];
ll gs[N][N];
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
    cin >> n;
    for (int i = 1;i < n;++i) {
        int u, v;
        cin >> u >> v;
        --u;--v;
        e[u][v] = e[v][u] = 1;
    }
    for (int x = 0;x < n;++x) {
        memset(mt, 0, sizeof(mt));
        for (int i = 0;i < n;++i) {
            for (int j = 0;j < n;++j) {
                if (i == j)continue;
                if (e[i][j]) {
                    mt[i][j] = mod - 1;
                    mt[i][i]++;
                }
                else {
                    mt[i][j] = mod - x;
                    mt[i][i] = (mt[i][i] + x) % mod;
                }
            }
        }
        ll sum = 1;
        for (int i = 0;i < n - 1;++i) {
            if (mt[i][i] == 0) {
                for (int j = i + 1;j < n - 1;++j) {
                    if (mt[j][i]) {
                        for (int k = 0;k < n - 1;++k) {
                            swap(mt[i][k], mt[j][k]);
                        }
                        sum = sum * (mod - 1) % mod;
                        break;
                    }
                }
            }
            if (!mt[i][i])continue;
            ll bs = ksm(mt[i][i]);
            for (int j = 0;j < n - 1;++j) {
                if (i == j)continue;
                ll bas = bs * mt[j][i] % mod;
                for (int k = i;k < n - 1;++k) {
                    mt[j][k] = (mt[j][k] - mt[i][k] * bas % mod + mod) % mod;
                }
            }
        }
        for (int i = 0;i < n - 1;++i)sum = sum * mt[i][i] % mod;
        ll ns = 1;
        for (int i = 0;i < n;++i) {
            gs[x][i] = ns;
            ns = ns * x % mod;
        }
        gs[x][n] = sum;
    }
    for (int i = 0;i < n;++i) {
        if (gs[i][i] == 0) {
            for (int j = i + 1;j < n;++j) {
                if (gs[j][i]) {
                    for (int k = 0;k <= n;++k) {
                        swap(gs[i][k], gs[j][k]);
                    }
                    break;
                }
            }
        }
        ll bs = ksm(gs[i][i]);
        for (int j = 0;j < n;++j) {
            if (i == j)continue;
            ll bas = gs[j][i] * bs % mod;
            for (int k = i;k <= n;++k) {
                gs[j][k] = (gs[j][k] - bas * gs[i][k] % mod + mod) % mod;
            }
        }
    }
    for (int i = 0;i < n;++i) {
        cout << gs[n - 1 - i][n] * ksm(gs[n - 1 - i][n - 1 - i]) % mod << ' ';
    }
    return 0;
}