#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int K = 16;
const int M = 1e4 + 5;
int T;
int m;
int cn;
int g[K];
int eid[M];
int ask(int ed, int x) {
    cout << "? " << g[ed] << ' ' << x << endl;
    int op;
    cin >> op;
    ++cn;
    return op;
}
int ans[M];
int main() {
    cin >> T;
    while (T--) {
        cin >> m;
        cn = 0;
        for (int i = 0;i < K;++i)g[i] = 0;
        for (int i = 1;i <= m;++i) {
            int l = 0, r = 16;
            int gid = 0;
            while (l < r - 1) {
                int mid = (l + r) / 2;
                if (ask(mid, i))r = mid, gid = cn;
                else l = mid;
            }
            eid[i] = r;
            if (r == 16) {
                continue;
            }
            else {
                g[r] = gid;
            }
        }
        for (int i = 1;i <= m;++i) {
            if (eid[i] == 16) {
                cout << "? 0 " << i << endl;
                int op;
                cin >> op;
                if (op)ans[i] = 0;
                else ans[i] = -1;
                continue;
            }
            int l = eid[i], r = 16;
            while (l < r - 1) {
                int mid = (l + r) / 2;
                if (ask(mid, i))r = mid;
                else l = mid;
            }
            if (l == 15) {
                ans[i] = 0;
            }
            else ans[i] = l;
        }
        cout << "! ";
        for (int i = 1;i <= m;++i) {
            cout << ans[i] << ' ';
        }cout << endl;
        int op;
        cin >> op;
    }
    return 0;
}