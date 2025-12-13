#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 155;
int n;
ll C[N][N];
ll s;
int cn;
int main() {
    cin >> n;
    if (n == 1) {
        cin >> cn;
        cout << (cn == 0);
        return 0;
    }
    C[0][0] = 1;
    for (int i = 1;i <= n;++i) {
        C[i][0] = 1;
        for (int j = 1;j <= i;++j) {
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
        }
    }
    s = 1;
    for (int i = 1;i <= n;++i) {
        int d;
        cin >> d;
        if (d == 0) {
            s = 0;
            break;
        }
        --d;
        cn += d;
        if (cn > n - 2) {
            s = 0;
            break;
        }
        s *= C[cn][d];
    }
    if (cn != n - 2)s = 0;
    cout << s;
    return 0;
}