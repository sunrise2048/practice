#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=505;
const ll inf=1e16;
int n,m;
ll e[N][N];
ll dx[N],dy[N];
bool vis[N];
ll s[N];
int p[N];
int las[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    memset(e,~0x3f,sizeof(e));
    for(int i=1;i<=m;++i){
        int u,v,w;
        cin>>u>>v>>w;
        e[u][v]=w;
    }
    memset(dx,~0x3f,sizeof(dx));
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            dx[i]=max(dx[i],e[i][j]);
        }
    }
    for(int i=1;i<=n;++i){
        int x=0,y=0;
        int tid=0;
        p[0]=i;
        ll val=inf;
        memset(s,0x3f ,sizeof(s));
        memset(vis,0,sizeof(vis));
        memset(las,0,sizeof(las));
        while(p[y]){
            y=tid;
            x=p[tid];
            vis[y]=1;
            val=inf;
            for(int j=1;j<=n;++j){
                if(vis[j])continue;
                if(s[j]>dx[x]+dy[j]-e[x][j]){
                    s[j]=dx[x]+dy[j]-e[x][j];
                    las[j]=y;
                }
                if(s[j]<val){
                    val=s[j];
                    tid=j;
                }
            }
            for(int j=0;j<=n;++j){
                if(vis[j]){
                    dx[p[j]]-=val;
                    dy[j]+=val;
                }
                else s[j]-=val;
            }
        }
        while(y){
            p[y]=p[las[y]];
            y=las[y];
        }
    }
    ll ans=0;
    for(int i=1;i<=n;++i)ans+=dx[i]+dy[i];
    cout<<ans<<'\n';
    for(int i=1;i<=n;++i){
        cout<<p[i]<<' ';
    }
    cout<<'\n';
    return 0;
}