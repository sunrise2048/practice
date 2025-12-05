#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N = 105;
const int K = 1005;
int n, k;
int p[N];
double f[K][N][N];
double sum_j[N][N],sum_i[N][N];
double sum_d[N][N];
double get_s(int x){
    return x * (x + 1) / 2;
}
int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> p[i];
    }
    k=min(k,1000);
    for (int i = 1; i <=n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            f[0][i][j] = (p[i] > p[j]);
            f[0][j][i] = (p[i] < p[j]);
        }
    }
    for (int nd = 1; nd <= k; ++nd) {
        memset(sum_j, 0, sizeof(sum_j));
        memset(sum_i, 0, sizeof(sum_i));
        memset(sum_d, 0, sizeof(sum_d));
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                sum_i[i][j] = sum_i[i - 1][j] + f[nd - 1][i][j];
                sum_j[i][j] = sum_j[i][j - 1] + f[nd - 1][i][j];
            }
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j < i; ++j) {
                sum_d[i - j][i] = f[nd - 1][i][j]; 
            }
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                sum_d[i][j] += sum_d[i][j - 1];
                sum_i[i][j] += sum_i[i - 1][j];
                sum_j[i][j] += sum_j[i][j - 1];
                sum_d[i][j] += sum_d[i][j - 1];
            }
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                f[nd][i][j] = f[nd - 1][i][j] * (get_s(i - 1) + get_s(j - i - 1) + get_s(n - j));
                f[nd][i][j] += sum_i[j - 1][j] - sum_i[j - i - 1][j] - sum_i[i - 1][j];
                f[nd][i][j] += sum_j[i][n] - sum_j[i][n + i - j] - sum_j[i][j - 1] + sum_j[i][i - 1];
                f[nd][i][j] += sum_d[j - i][n] - sum_d[j - i][n - i] - sum_d[j - i][j - 1];
                f[nd][i][j] /= get_s(n);
                f[nd][j][i] = 1 - f[nd][i][j];
            }
        }
    }
    double ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            ans += f[k][i][j];
        }
    }
    printf("%.15f", ans);
    return 0;
}