#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5;
const int B = 320;
const int K = 330;
int n;
int a[N];
int cn[K][N];
int q;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin >> n;
    for (int i = 1;i <= n;++i) {
        cin >> a[i];
    }
    for (int k = B;k;--k) {
        for (int i = n;i;--i) {
            int ti = i + a[i] + k;
            if (ti > n)cn[k][i] = 1;
            else cn[k][i] = cn[k][ti] + 1;
        }
    }
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        if (y <= B) {
            cout << cn[y][x] << '\n';
            continue;
        }
        int cn = 0;
        while (x <= n) {
            x += a[x] + y;
            ++cn;
        }
        cout << cn << '\n';
    }
    return 0;
}