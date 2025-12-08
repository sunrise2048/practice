#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5;
const int mod = 1e4;
int n, t;
int a[N];
int kmp[N];
ll mi[N];
int main() {
    cin >> n >> t;
    mi[0] = 1;
    for (int i = 1;i <= 1e5;++i) {
        mi[i] = mi[i - 1] * n % mod;
    }
    while (t--) {
        int m;
        cin >> m;
        for (int i = 1;i <= m;++i) {
            cin >> a[i];
        }
        kmp[1] = 0;
        int j = 0;
        for (int i = 2;i <= m;++i) {
            while (j && a[j + 1] != a[i])j = kmp[j];
            if (a[j + 1] == a[i])++j;
            kmp[i] = j;
        }
        ll s = 0;
        int no = m;
        while (no) {
            s = (s + mi[no]) % mod;
            no = kmp[no];
        }
        printf("%04lld\n", s);
    }
    return 0;
}