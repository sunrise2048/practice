#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+5;
int T;
int n,m;
vector<int> e[N],ee[N];
bool vis[N];
int fa[N];
struct edge{
    int u,v;
}E[N];
int d[N];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int cn11,cn00;
int c[N];
void dfs(int no,int fa){
    d[no]=d[fa]+1;
    for(int to:e[no]){
        if(to==fa)continue;
        dfs(to,no);
    }
}
int z;
void dfs1(int no,int fa){
    for(int to:e[no]){
        if(to==fa)continue;
        dfs1(to,no);
        c[no]+=c[to];
    }
}
void dfs2(int no){
    for(int to:e[no]){
        if(d[to]<d[no])continue;
        dfs2(to);
    }
    d[no]++;
}
void prt(){
    cout<<"YES\n";
    for(int i=1;i<=n;++i){
        cout<<(d[i]&1);
    }cout<<'\n';
}
bool solve(){
    cn00=cn11=0;
    for(int i=1;i<=m;++i){
        auto [u,v]=E[i];
        if(d[u]>d[v])swap(u,v);
        if(d[u]+1==d[v])continue;
        if((d[u]&1)==(d[v]&1)){
            if(d[u]&1)++cn11;
            else ++cn00;
            c[v]++;
            c[u]--;
        }
        else{
            c[v]--;
            c[u]++;
        }
    }
    if(cn11==1&&cn00==0){
        prt();
        return 1;
    }
    dfs1(1,0);
    z=0;
    for(int i=1;i<=n;++i){
        if(d[i]&1)continue;
        if(c[z]<c[i])z=i;
    }
    if(c[z]==cn11+cn00){
        dfs2(z);prt();
        return 1;
    }
    return 0;
}
void dfs0(int no){
    vis[no]=1;
    for(int to:ee[no]){
        if(vis[to])continue;
        e[no].push_back(to);
        dfs0(to);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=n;++i){
            vis[i]=0;
            ee[i].clear();
            e[i].clear();
            fa[i]=i;
            c[i]=0;
        }
        for(int i=1;i<=m;++i){
            cin>>E[i].u>>E[i].v;
            ee[E[i].u].push_back(E[i].v);
            ee[E[i].v].push_back(E[i].u);
        }
        dfs0(1);
        dfs(1,0);
        if(solve()){
            continue;
        }
        for(int i=1;i<=n;++i){
            c[i]=0;
            d[i]++;
        }
        if(solve())continue;
        cout<<"NO\n";
    }
    return 0;
}