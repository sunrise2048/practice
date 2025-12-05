#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using Complex = complex<long double>;
constexpr int N = 1 << 21;
const long double pi = acos(-1);
int rev[N];
void bit_reverse(Complex* f, int n) {
    for (int i = 1; i < n; ++i) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * (n >> 1));
        if (rev[i] < i) swap(f[i], f[rev[i]]);
    }
}
void FFT(Complex* f, int n, int op) {
    bit_reverse(f, n);
    for (int k = 1; k < n; k <<= 1) {
        Complex w(cos(pi / k), -op * sin(pi / k));
        for (int i = 0; i < n; i += (k << 1)) {
            Complex W(1, 0);
            for (int j = 0; j < k; ++j) {
                Complex x = f[i + j], y = f[i + j + k] * W;
                f[i + j] = x + y;
                f[i + j + k] = x - y;
                W = W * w;
            }
        }
    }
    if (op == -1) {
        for (int i = 0; i < n; ++i) {
            f[i] /= n;
        }
    }
}
int n;
class Poly {
public:
    vector<long double> f;
    void read(int n) {
        f.resize(n);
        for (int i = 0;i < n;++i) {
            cin >> f[i];
        }
    }
    Poly Dvt() {
        Poly A;A.f = f;
        for (int i = 1;i < f.size();++i) {
            A.f[i - 1] = A.f[i];
            A.f[i - 1] *= i;
        }
        A.f.pop_back();
        return A;
    }
    Poly Its() {
        Poly A;A.f = f;A.f.push_back(0);
        for (int i = f.size();i;--i) {
            A.f[i] = A.f[i - 1];
            A.f[i] /= i;
        }
        A.f[0] = 0;
        return A;
    }
    Poly operator + (const Poly& B)const {
        Poly C = B;
        C.f.resize(max(f.size(), B.f.size()));
        for (int i = 0; i < f.size(); ++i) {
            C.f[i] = C.f[i] + f[i];
        }
        return C;
    }
    Poly operator - (const Poly& B)const {
        Poly C = B;
        C.f.resize(max(f.size(), B.f.size()));
        for (int i = 0; i < f.size(); ++i) {
            C.f[i] = f[i] - C.f[i];
        }
        for (int i = f.size();i < B.f.size();++i) {
            C.f[i] = -C.f[i];
        }
        return C;
    }
    Poly operator*(const long double& c)const {
        Poly C;
        C.f = f;
        for (int i = 0;i < f.size();++i)C.f[i] *= c;
        return C;
    }
    static Complex A[N], B[N], C[N];
    static void init() {
        for (int i = 0;i < n;++i) {
            A[i] = B[i] = C[i] = Complex(0, 0);
        }
    }
    void clr(Complex* f, int n)const { for (int i = 0;i < n;++i)f[i] = Complex(0, 0); }
    Poly operator * (const Poly& y) const {
        int n = 1, m = f.size() + y.f.size() - 1;
        while (n < m)n <<= 1;
        for (int i = 0;i < f.size();++i)A[i].real(f[i]);
        for (int i = 0;i < y.f.size();++i)A[i].imag(y.f[i]);
        FFT(A, n, 1);
        for (int i = 0;i < n;++i)A[i] = A[i] * A[i];
        FFT(A, n, -1);
        Poly C;C.f.resize(m);
        for (int i = 0;i < m;++i)C.f[i] = A[i].imag() / 2;
        clr(A, n);
        return C;
    }
    void get_inv(Poly& ans, int n) {
        if (n == 1) {
            ans.f.push_back(1 / f[0]);
        }
        else if (n & 1) {
            get_inv(ans, n - 1);
            long double sum = 0;
            for (int i = 0;i < n - 1;++i)sum += ans.f[i] * f[n - 1 - i];
            ans.f.push_back(sum / (-f[0]));
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
            g = g * 0.5 + g.inv() * ls * 0.5;
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
            long double sum = 0;
            for (int i = 0;i < n - 1;++i) {
                sum += (i + 1) * f[i + 1] * ans.f[n - 2 - i];
            }
            ans.f.push_back(sum / (n - 1));
        }
        else {
            get_exp(ans, n / 2);
            Poly ls = ans;
            ls.f.resize(n);
            ls = ls.ln();
            for (int i = 0;i < ls.f.size();++i) {
                ls.f[i] = f[i] - ls.f[i];
            }
            ls.f[0] = ls.f[0] + 1;
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
        for (int i = 0;i < f.size();++i)ans.f[i] *= k;
        ans = ans.exp();
        return ans;
    }
}F, G;
Complex Poly::A[N], Poly::B[N], Poly::C[N];
int main() {
    Poly::init();
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int n, m;
    cin >> n >> m;
    F.read(n + 1);G.read(m + 1);
    F = F * G;
    for (int i = 0;i <= n + m;++i) {
        cout << (int)(F.f[i] + 0.5) << ' ';
    }
    return 0;
}