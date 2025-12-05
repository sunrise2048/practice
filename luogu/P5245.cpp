#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int mod = 998244353;
constexpr int N = 1 << 18;
ll ksm(ll x, ll y = mod - 2) {
    ll an = 1;
    while (y) {
        if (y & 1) an = an * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return an;
}
int rev[N];
ll gp[N + 1], gip[N + 1];
ll iinv[N + 1];
void bit_reverse(ll* f, int n) {
    for (int i = 1; i < n; ++i) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * (n >> 1));
        if (rev[i] < i) swap(f[i], f[rev[i]]);
    }
}
void NTT(ll* f, int n, int op) {
    bit_reverse(f, n);
    for (int k = 1; k < n; k <<= 1) {
        ll w = (op == 1 ? gp[k << 1] : gip[k << 1]);
        for (int i = 0; i < n; i += (k << 1)) {
            ll W = 1;
            for (int j = 0; j < k; ++j) {
                ll x = f[i + j], y = f[i + j + k] * W % mod;
                f[i + j] = (x + y) % mod;
                f[i + j + k] = (x - y + mod) % mod;
                W = W * w % mod;
            }
        }
    }
    if (op == -1) {
        ll ny = iinv[n];
        for (int i = 0; i < n; ++i) {
            f[i] = f[i] * ny % mod;
        }
    }
}
int n;
class Poly {
public:
    static constexpr int g = 3;
    static constexpr int gi = (mod + 1) / g;
    vector<ll> f;
    void read(int n) {
        f.resize(n);
        for (int i = 0;i < n;++i) {
            cin >> f[i];
        }
    }
    Poly Dvt() {
        Poly A;A.f = f;
        for (int i = 1;i < f.size();++i)A.f[i - 1] = A.f[i] * i % mod;
        A.f.pop_back();
        return A;
    }
    Poly Its() {
        Poly A;A.f = f;A.f.push_back(0);
        for (int i = f.size();i;--i) {
            A.f[i] = A.f[i - 1] * iinv[i] % mod;
        }
        A.f[0] = 0;
        return A;
    }
    Poly operator + (const Poly& B)const {
        Poly C = B;
        C.f.resize(max(f.size(), B.f.size()));
        for (int i = 0; i < f.size(); ++i) {
            C.f[i] = (C.f[i] + f[i]) % mod;
        }
        return C;
    }
    Poly operator - (const Poly& B)const {
        Poly C = B;
        C.f.resize(max(f.size(), B.f.size()));
        for (int i = 0; i < f.size(); ++i) {
            C.f[i] = (f[i] - C.f[i] + mod) % mod;
        }
        for (int i = f.size();i < B.f.size();++i) {
            C.f[i] = (mod - C.f[i]) % mod;
        }
        return C;
    }
    Poly operator*(const ll& c)const {
        Poly C;
        C.f = f;
        for (int i = 0;i < f.size();++i)C.f[i] = C.f[i] * c % mod;
        return C;
    }
    static ll A[N], B[N], C[N];
    static void init() {
        memset(A, 0, sizeof(A));memset(B, 0, sizeof(B));memset(C, 0, sizeof(C));
        for (int i = 1; i <= N; i <<= 1) {
            gp[i] = ksm(g, (mod - 1) / i);
            gip[i] = ksm(gi, (mod - 1) / i);
        }
        iinv[0] = 1;
        for (int i = 1;i <= N;++i)iinv[i] = iinv[i - 1] * i % mod;
        iinv[N] = ksm(iinv[N]);
        for (int i = N;i;--i) {
            ll la = iinv[i - 1];
            iinv[i - 1] = iinv[i] * i % mod;
            iinv[i] = iinv[i] * la % mod;
        }
    }
    void cpy(ll* F)const {
        for (int i = 0;i < f.size();++i)F[i] = f[i];
    }
    void clr(ll* f, int n)const { memset(f, 0, sizeof(ll) * n); }
    Poly operator * (const Poly& y) const {
        cpy(A);y.cpy(B);
        int n = 1, m = f.size() + y.f.size() - 1;
        while (n < m)n <<= 1;
        NTT(A, n, 1);NTT(B, n, 1);
        for (int i = 0;i < n;++i)A[i] = A[i] * B[i] % mod;
        NTT(A, n, -1);
        Poly C;C.f.resize(m);
        for (int i = 0;i < m;++i)C.f[i] = A[i];
        clr(A, n);clr(B, n);
        return C;
    }
    void get_inv(Poly& ans, int n) {
        if (n == 1) {
            ans.f.push_back(ksm(f[0]));
        }
        else if (n & 1) {
            get_inv(ans, n - 1);
            ll sum = 0;
            for (int i = 0;i < n - 1;++i)sum = (sum + ans.f[i] * f[n - 1 - i]) % mod;
            ans.f.push_back(sum * ksm(mod - f[0]) % mod);
        }
        else {
            get_inv(ans, n / 2);
            Poly ls;ls.f.resize(n);
            for (int i = 0;i < n;++i)ls.f[i] = f[i];
            ans = ans * 2 - ans * ans * ls;
            ans.f.resize(n);
        }
    }
    Poly inv() {
        Poly ans;
        get_inv(ans, f.size());
        return ans;
    }
    Poly sqrt() {
        Poly g;
        g.f.push_back(1);
        Poly ls;
        while (g.f.size() < f.size()) {
            while (ls.f.size() < (g.f.size() << 1)) {
                if (ls.f.size() < f.size())ls.f.push_back(f[ls.f.size()]);
                else ls.f.push_back(0);
            }
            int tn = g.f.size() << 1;
            g.f.resize(tn);
            g = g * ((mod + 1) / 2) + g.inv() * ls * ((mod + 1) / 2);
            g.f.resize(tn);
        }
        return g;
    }
    Poly ln() {
        return (Dvt() * inv()).Its();
    }
    void get_exp(Poly& ans, int n) {
        if (n == 1)ans.f.push_back(1);
        else if (n & 1) {
            get_exp(ans, n - 1);
            ll sum = 0;
            for (int i = 0;i < n - 1;++i) {
                sum = (sum + (i + 1) * f[i + 1] % mod * ans.f[n - 2 - i]) % mod;
            }
            ans.f.push_back(sum * iinv[n - 1] % mod);
        }
        else {
            get_exp(ans, n / 2);
            Poly ls = ans;
            ls.f.resize(n);
            ls = ls.ln();
            for (int i = 0;i < ls.f.size();++i) {
                ls.f[i] = (f[i] - ls.f[i] + mod) % mod;
            }
            ls.f[0] = (ls.f[0] + 1) % mod;
            ans = ans * ls;
            ans.f.resize(n);
        }
    }
    Poly exp() {
        Poly ans;
        get_exp(ans, f.size());
        return ans;
    }
    Poly poly_ksm(ll k) {
        Poly ans = ln();
        ans.f.resize(n);
        for (int i = 0;i < f.size();++i)ans.f[i] = ans.f[i] * k % mod;
        ans = ans.exp();
        return ans;
    }
}F, G;
ll Poly::A[N], Poly::B[N], Poly::C[N];
int main() {
    Poly::init();
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    ll k = 0;
    string s;
    cin >> n >> s;
    for (char c : s) {
        k = (k * 10 + c - '0') % mod;
    }
    F.read(n);
    F = F.poly_ksm(k);
    for (int i = 0;i < n;++i) {
        cout << F.f[i] << ' ';
    }
    return 0;
}