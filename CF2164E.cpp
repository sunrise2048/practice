#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+5;
const int inf=1e9+7;
int T;
int n,m;
struct edge{
    int u,v,w;
}e[N];
vector<int> te[N<<1];
int val[N<<1];
int fa[N<<1];
int si[N<<1];
int in[N];
ll ans;
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void dfs(int no,int nv){
    nv=min(nv,val[no]);
    if(no<=n){
        si[no]=(in[no]&1);
        return;
    }
    for (int to:te[no]) {
        dfs(to,nv);
        si[no]+=si[to];
    }
    if (si[no]==2) {
        ans+=nv;
        si[no]-=2;
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while (T--) {
        cin>>n>>m;
        ans=0;
        for (int i=1;i<=n+m;++i) {
            te[i].clear();
            val[i]=inf;
            si[i]=0;
            fa[i]=i;
        }
        memset(in,0,sizeof(int)*(n+1));
        for (int i=1;i<=m;++i) {
            cin>>e[i].u>>e[i].v>>e[i].w;
            in[e[i].u]++;
            in[e[i].v]++;
            ans+=e[i].w;
        }
        for (int i=1;i<=m;++i) {
            auto [u,v,w]=e[i];
            u=find(u);v=find(v);
            val[n+i]=w;
            if (u==v) {
                te[n+i].push_back(u);
                fa[u]=n+i;
            }
            else {
                te[n+i].push_back(u);
                te[n+i].push_back(v);
                fa[u]=fa[v]=n+i;
            }
        }
        dfs(n+m,inf);
        cout<<ans<<'\n';
    }
    return 0;
}