#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
const int N = 305;
const ull bas = 19260817;
int n, m;
string s[N];
ull ha1[N][N], ha2[N][N];
ull mi[N];
double er[N], f[N][N];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin >> n >> m;
    for (int i = 1;i <= n;++i) {
        cin >> s[i];
        s[i] = "0" + s[i];
    }
    er[0] = 1;
    for (int i = 1;i <= m;++i)er[i] = er[i - 1] / 2;
    mi[0] = 1;
    for (int i = 1;i <= m;++i)mi[i] = mi[i - 1] * bas;
    for (int i = 1;i <= n;++i) {
        for (int j = 1;j <= m;++j) {
            ha1[i][j] = ha1[i][j - 1] * bas + s[i][j];
        }
        for (int j = m;j;--j) {
            ha2[i][j] = ha2[i][j + 1] + s[i][j] * mi[m - j];
        }
    }
    for (int i = 1;i <= n;++i)f[0][i] = 1;
    f[0][n + 1] = 1;
    for (int i = 1;i <= n;++i) {
        f[i][0] = -er[m];
        for (int j = 1;j <= n;++j) {
            for (int k = 1;k <= m;++k) {
                if (ha1[i][k] == ha2[j][m - k + 1]) {
                    f[i][j] += er[m - k];
                }
            }
        }
    }
    for (int i = 0;i <= n;++i) {
        {
            int j = i;
            for (int k = i + 1;k <= n;++k) {
                if (f[k][i] != 0)j = k;
            }
            if (i != j) {
                for (int k = 0;k <= n + 1;++k)swap(f[i][k], f[j][k]);
            }
        }
        for (int j = 0;j <= n;++j) {
            if (i == j)continue;
            double bs = f[j][i] / f[i][i];
            for (int k = i;k <= n + 1;++k)f[j][k] -= f[i][k] * bs;
        }
    }
    for (int i = 1;i <= n;++i) {
        printf("%.15f\n", f[i][n + 1] / f[i][i]);
    }
    return 0;
}