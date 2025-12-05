#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using Complex = complex<long double>;
constexpr int N = 1 << 17;
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
}F[4];
Complex Poly::A[N], Poly::B[N], Poly::C[N];
int main() {
    Poly::init();
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int n, m, cn;
    while (cin >> n >> m >> cn) {
        if (!n)break;
        for (int op : {0, 1, 2, 3}) {
            F[op].f.clear();
            F[op].f.resize(m + 1, 1);
        }
        for (int i = 0;i <= m;++i) {
            bool fl = 1;
            for (int j = 2;j * j <= i;++j) {
                if (i % j == 0) {
                    fl = 0;
                    break;
                }
            }
            if (fl) {
                for (int op : {0, 1, 2, 3}) {
                    F[op].f[i] = 0;
                }
            }
        }
        while (cn--) {
            string c;
            cin >> c;
            char op = c.back();
            c.pop_back();
            ll id = 0;
            for (char ca : c) {
                id = id * 10 + ca - '0';
            }
            if (id > m)continue;
            if (op == 'S') {
                F[0].f[id] = 0;
            }
            else if (op == 'H') {
                F[1].f[id] = 0;
            }
            else if (op == 'C') {
                F[2].f[id] = 0;
            }
            else F[3].f[id] = 0;
        }
        for (int op : {1, 2, 3}) {
            F[0] = F[0] * F[op];
            if (F[0].f.size() > m)F[0].f.resize(m + 1);
        }
        for (int i = n;i <= m;++i) {
            cout << (ll)(F[0].f[i] + 0.5) << '\n';
        }
    }
    return 0;
}