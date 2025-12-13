#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e3 + 5;
int T;
int n, m;
int a[N][N];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1;i <= n;++i) {
            for (int j = 1;j <= m;++j) {
                char c;
                cin >> c;
                a[i][j] = c - '0';
            }
        }
        int cn1 = 0, cn2 = 0;
        for (int i = 1;i <= n;++i) {
            int s = 0;
            for (int j = 1;j <= m;++j) {
                s ^= a[i][j];
            }
            cn1 += s;
        }
        for (int j = 1;j <= m;++j) {
            int s = 0;
            for (int i = 1;i <= n;++i) {
                s ^= a[i][j];
            }
            cn2 += s;
        }
        cout << max(cn1, cn2) << '\n';
    }
    return 0;
}