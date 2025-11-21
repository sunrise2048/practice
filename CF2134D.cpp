#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n;
vector<int> e[N];
int d[N];
int mz;
int nf[N];
bool fl[N];
void find_ans(){
    for (int b=1;b<=n;++b) {
        if (!fl[b]) continue;
        int a=0,c=0;
        for (int to:e[b]) {
            if (fl[to]) a=to;
            else c=to;
        }
        if (a&&c) {
            cout<<a<<' '<<b<<' '<<c<<'\n';
            return;
        }
    }
}
bool ch(){
    for (int i=1;i<=n;++i) {
        if (e[i].size()>2) return 0;
    }
    return 1;
}
void dfs(int no,int fa){
    d[no]=d[fa]+1;
    nf[no]=fa;
    if (d[no]>d[mz]) mz=no;
    for (int to:e[no]) {
        if (to==fa) continue;
        dfs(to,no);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while (T--) {
        cin>>n;
        for (int i=1;i<=n;++i) {
            e[i].clear();
            fl[i]=0;
        }
        for (int i=1;i<n;++i) {
            int u,v;
            cin>>u>>v;
            e[u].push_back(v);
            e[v].push_back(u);
        }
        if (ch()) {
            cout<<"-1\n";
            continue;
        }
        mz=0;
        dfs(1,0);
        dfs(mz,0);
        int no=mz;
        while (no) {
            fl[no]=1;
            no=nf[no];
        }
        find_ans();
    }
    return 0;
}