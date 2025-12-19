#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int mod = 1e9 + 7;
int T;
int n;
vector<int> pr;
vector<int> cs;
void get_pr() {
    int m = n;
    for (int i = 2;i * i <= m;++i) {
        if (m % i == 0) {
            cs.push_back(0);
            pr.push_back(i);
            while (m % i == 0) {
                m /= i;
                cs.back()++;
            }
        }
    }
    if (m != 1) {
        pr.push_back(m);
        cs.push_back(1);
    }
}
ll ans;
ll ksm(ll x, int y = mod - 2) {
    ll an = 1;
    while (y) {
        if (y & 1)an = an * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return an;
}
void dfs(int no, int val, int phi) {
    if (no == pr.size()) {
        ans = (ans + ksm(n, val) * phi) % mod;
        return;
    }
    for (int i = 1;i <= cs[no];++i)val = val * pr[no];
    for (int i = 0;i <= cs[no];++i) {
        dfs(no + 1, val, phi);
        val = val / pr[no];
        if (i == 0)phi *= (pr[no] - 1);
        else phi *= pr[no];
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin >> T;
    while (T--) {
        cin >> n;
        pr.clear();
        cs.clear();
        get_pr();
        ans = 0;
        dfs(0, 1, 1);
        cout << ans * ksm(n) % mod << '\n';
    }
    return 0;
}