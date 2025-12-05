#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int mod = 1e9 + 7;
const ll sq2 = 59713600;
ll ksm(ll x, ll y = mod - 2) {
    ll an = 1;
    while (y) {
        if (y & 1)an = an * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return an;
}
ll n;
int main() {
    char c = getchar();
    while (!isdigit(c))c = getchar();
    while (isdigit(c)) {
        n = (n * 10 + c - '0') % (mod - 1);
        c = getchar();
    }
    n = (n - 1 + mod - 1) % (mod - 1);
    cout << ((sq2 - 1) * ksm(2 * sq2 % mod) % mod * ksm((1 - sq2 + mod) % mod, n) + (sq2 + 1) * ksm(2 * sq2 % mod) % mod * ksm((sq2 + 1) % mod, n)) % mod << '\n';
    return 0;
}