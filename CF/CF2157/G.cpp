#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=105;
const int K=30;
int T;
int n;
int fa[K][N<<1];
bool fl[N][N];
int find(int k,int x) {return fa[k][x]==x?x:fa[k][x]=find(k,fa[k][x]);}
void ask(int l,int r) {
    if (l > r) return;
    if (fl[l][r]) return;
    fl[l][r] = 1;
    cout << "? " << l << ' ' << r << endl;
    int lm;
    cin >> lm;
    for (int i = K - 1; i > lm; --i) {
        fa[i][find(i, l - 1)]=fa[i][find(i, r)];
        fa[i][find(i, l + n)]=fa[i][find(i, r + n + 1)];
    }
    if (lm > -1) {
        fa[lm][find(lm, l - 1)]=fa[lm][find(lm, r + n + 1)];
        fa[lm][find(lm, l + n)]=fa[lm][find(lm, r)];
    }
}
void sol(int k,vector<int>& id) {
    if (k==-1) return;
    if (id.empty()) return;
    vector<int> id0, id1;
    ask(id[0]+1,id.back());
    for (int no:id) {
        if (no - id[0] >= id.back() - no) ask(id[0] + 1, no);
        else ask(no + 1, id.back());
    }
    for (int no:id) {
        if (find(k, id[0]) == find(k, no)) id0.push_back(no);
        else id1.push_back(no);
    }
    sol(k - 1, id0);sol(k - 1, id1);
}
int main(){
    cin >> T;
    while (T--) {
        cin >> n;
        memset(fl, 0, sizeof(fl));
        for (int i = 0; i < K; ++i) iota(fa[i], fa[i] + 2 * n + 2, 0);
        vector<int> id(n+1);
        iota(id.begin(),id.end(),0);
        sol(K-1,id);
        cout<<"!"<<endl;
        for (int i = 1; i <= n; ++i) {
            for (int j = i; j <= n; ++j) {
                int as=K-1;
                while(as >= 0 && find(as, i - 1) == find(as, j)) --as;
                cout<<as<<' ';
            }cout<<endl;
        }
    }
    return 0;
}