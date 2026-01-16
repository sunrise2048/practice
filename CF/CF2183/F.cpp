#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5005;
const int mod=998244353;
const int ny2=(mod+1)/2;
int T;
int n;
char c[N];
vector<int> e[N];
ll g[N][N];
ll f[N][N];
int dfn[N],cn_dfn,nfd[N];
void dfs(int no,int fa){
    dfn[no]=++cn_dfn;
    nfd[cn_dfn]=no;
    for(int to:e[no]){
        if(to==fa)continue;
        dfs(to,no);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        cn_dfn=0;
        for(int i=1;i<=n;++i){
            e[i].clear();
            memset(g,0,sizeof(ll)*(n+1));
            memset(f,0,sizeof(ll)*(n+1));
        }
        for(int i=1;i<=n;++i)cin>>c[i];
        for(int i=1;i<n;++i){
            int u,v;
            cin>>u>>v;
            e[u].push_back(v);
            e[v].push_back(u);
        }
        dfs(1,0);
        for(int ii=n;ii;--ii){
            for(int jj=n;jj>=ii;--jj){
                int x=nfd[ii],y=nfd[jj];
                ll s=0;
                ll ns=0;
                for(int to:e[y]){
                    if(dfn[to]<jj)continue;
                    ns=(ns+f[x][to])%mod;
                }
                for(int to:e[y]){
                    if(dfn[to]<jj)continue;
                    s=(s+g[x][to]+f[x][to])%mod;
                }
                for(int to:e[x]){
                    if(dfn[to]<ii)continue;
                    s=(s+g[to][y]+f[y][to])%mod;
                }
                s=s*ny2%mod;
                if(c[x]==c[y]){
                    ll ls=s;
                    for(int to:e[y]){
                        if(dfn[to]<jj)continue;
                        ls=(ls-f[x][to]+mod)%mod;
                    }
                    for(int to:e[x]){
                        if(dfn[to]<ii)continue;
                        ls=(ls-f[y][to]+mod)%mod;
                    }
                    s=(s+ls+1)%mod;
                    ns=s;
                    for(int to:e[x]){
                        if(dfn[to]<ii)continue;
                        ns=(ns-g[to][y]+mod)%mod;
                    }
                }
                g[y][x]=g[x][y]=s;
                f[x][y]=ns;
            }
            for(int jj=n;jj>ii;--jj){
                int x=nfd[ii],y=nfd[jj];
                if(c[x]==c[y]){
                    ll ns=g[y][x];
                    for(int to:e[y]){
                        if(dfn[to]<jj)continue;
                        ns=(ns-g[to][x]+mod)%mod;
                    }
                    f[y][x]=ns;
                }
                else{
                    ll ns=0;
                    for(int to:e[x]){
                        if(dfn[to]<ii)continue;
                        ns=(ns+f[y][to])%mod;
                    }
                    f[y][x]=ns;
                }
            }
        }
        for(int i=1;i<=n;++i){
            cout<<g[i][i]<<' ';
        }cout<<'\n';
    }
    return 0;
}