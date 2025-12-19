#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 5;
const int mod = 998244353;
int T;
int n;
int a[N];
bool fl[N];
ll s[N];
ll f[N], g[N];
ll ksm(ll x, int y = mod - 2) {
    ll an = 1;
    while (y) {
        if (y & 1)an = an * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return an;
}
vector<int> tid;
int gc;
ll jc[N], ny[N];
void init() {
    const int n = 1e6;
    jc[0] = 1;
    for (int i = 1;i <= n;++i)jc[i] = jc[i - 1] * i % mod;
    ny[n] = ksm(jc[n]);
    for (int i = n;i;--i)ny[i - 1] = ny[i] * i % mod;
}
void calc(int cn) {
    int len = n / cn;
    if (gc % len)return;
    if (fl[cn])return;
    fl[cn] = 1;
    ll s = jc[cn];
    ll scn = 0, ncn = 0;
    for (int val : tid) {
        s = s * ny[a[val] / len] % mod;
        scn = (scn + ncn * (a[val] / len)) % mod;
        ncn += a[val] / len;
    }
    f[cn] = s;
    g[cn] = s * n % mod * ksm(1ll * cn * (cn - 1) % mod) % mod * scn % mod;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    init();
    cin >> T;
    while (T--) {
        cin >> n;
        memset(fl, 0, sizeof(bool) * (n + 1));
        memset(a, 0, sizeof(int) * (n + 1));
        memset(f, 0, sizeof(ll) * (n + 1));
        memset(g, 0, sizeof(ll) * (n + 1));
        gc = n;
        for (int i = 1;i <= n;++i) {
            int c;
            cin >> c;
            a[c]++;
        }
        tid.clear();
        for (int i = 1;i <= n;++i) {
            if (!a[i])continue;
            tid.push_back(i);
            gc = __gcd(gc, a[i]);
        }
        if (gc == n) {
            cout << "1\n";
            continue;
        }
        ll sf = 0, sg = 0;
        for (int i = 1;i <= n;++i) {
            int ng = __gcd(i, n);
            calc(ng);
            sf = (sf + f[ng]) % mod;
            sg = (sg + g[ng]) % mod;
        }
        cout << sg * ksm(sf) % mod * 2 % mod << '\n';
    }
    return 0;
}