#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5;
int n, m;
int a[N];
vector<int> e[N];
int ans;
int mx1, mx2;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin >> n >> m;
    for (int i = 1;i <= n;++i)cin >> a[i];
    for (int i = 1;i <= m;++i) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);e[v].push_back(u);
    }
    for (int i = 1;i <= n;++i) {
        if (e[i].size() == 1) {
            if (mx1 < a[i]) {
                mx2 = mx1;
                mx1 = a[i];
            }
            else if (mx2 < a[i])mx2 = a[i];
        }
        else ans = max(ans, a[i]);
    }
    cout << max(ans, mx2) << '\n';
    return 0;
}