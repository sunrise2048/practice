#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=305;
int T;
int n;
ll a[N];
vector<int> e[N];
vector<pair<ll,ll>> f[N][N];
int si[N],mxs[N];
int rt;
void find_rt(int no,int fa){
    si[no]=1;mxs[no]=0;
    for(int to:e[no]){
        if(to==fa)continue;
        find_rt(to,no);
        si[no]+=si[to];
        mxs[no]=max(mxs[no],si[to]);
    }
    mxs[no]=max(mxs[no],n-si[no]);
    if(mxs[rt]>mxs[no])rt=no;
}
vector<pair<ll,ll>> g[N];
void dfs(int no,int fa){
    f[no][1].emplace_back(a[no]*a[no],a[no]);
    si[no]=1;
    for(int to:e[no]){
        if(to==fa)continue;
        dfs(to,no);
        for(int i=1;i<=si[no]+si[to];++i)g[i].clear();
        for(int i=1;i<=si[no];++i){
            for(int j=1;j<=si[to];++j){
                for(auto [s0,vl0]:f[no][i]){
                    g[i+j].emplace_back(s0+f[to][j][0].first,vl0);
                    for(auto [s1,vl1]:f[to][j]){
                        g[i+j-1].emplace_back(s0+s1+2*vl0*vl1,vl0+vl1);
                    }
                }
            }
        }
        si[no]+=si[to];
        for(int i=1;i<=si[no];++i){
            sort(g[i].begin(),g[i].end());
            int m=0;
            for(int j=1;j<g[i].size();++j){
                if(g[i][j].second>=g[i][m].second)continue;
                g[i][++m]=g[i][j];
            }
            g[i].resize(m+1);
            swap(f[no][i],g[i]);
        }
    }
}
int main(){
    freopen("tree.in","r",stdin);
    freopen("tree.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;++i){
            e[i].clear();
            for(int j=1;j<=n;++j)f[i][j].clear();
        }
        for(int i=1;i<=n;++i){
            cin>>a[i];
        }
        for(int i=1;i<n;++i){
            int u,v;
            cin>>u>>v;
            e[u].push_back(v);
            e[v].push_back(u);
        }
        rt=0;
        mxs[0]=n+1;
        find_rt(1,0);
        dfs(rt,0);
        for(int i=1;i<=n;++i){
            cout<<f[rt][i][0].first<<' ';
        }cout<<'\n';
    }
    return 0;
}