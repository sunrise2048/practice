#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2005;
int T;
int n;
vector<int> e[N];
int nf[N];
int d[N];
int dz;
void dfs(int no,int fa){
    nf[no]=fa;
    d[no]=d[fa]+1;
    if(d[no]>d[dz])dz=no;
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
        for (int i=1;i<=n;++i) e[i].clear();
        for (int i=1;i<n;++i) {
            int u,v;
            cin>>u>>v;
            e[u].push_back(v);
            e[v].push_back(u);
        }
        dz=0;
        dfs(1,0);
        int rt=dz;
        dz=0;
        dfs(rt,0);
        vector<int> zz;
        int no=dz;
        while (no) {
            zz.push_back(no);
            no=nf[no];
        }
        if (zz.size()&1) {
            int zx=zz[zz.size()/2];
            cout<<(zz.size()+1)/2<<'\n';
            for (int i=0;i<=zz.size()/2;++i) {
                cout<<zx<<' '<<i<<'\n';
            }
            continue;
        }
        if (zz.size()%4==2) {
            int zx=zz[zz.size()/2];
            cout<<zz.size()/2+1<<'\n';
            for (int i=0;i<=zz.size()/2;++i) {
                cout<<zx<<' '<<i<<'\n';
            }
            continue;
        }
        int zx0=zz[zz.size()/2-1],zx1=zz[zz.size()/2];
        cout<<zz.size()/2<<'\n';
        for (int i=0;i<zz.size()/4;++i) {
            cout<<zx0<<' '<<2*i+1<<'\n';
            cout<<zx1<<' '<<2*i+1<<'\n';
        }
    }
    return 0;
}