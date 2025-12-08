#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=16;
const int M=5000;
const ll inf=1e16;
int n,m,k;
ll a[N][M];
ll e[N+1][N+1];
ll f[1<<N][N+1];
ll g[1<<N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>k;
    for(int i=0;i<n;++i){
        for(int j=0;j<m;++j){
            cin>>a[i][j];
        }
    }
    for(int i=0;i<m;++i){
        vector<int> id(n);
        iota(id.begin(),id.end(),0);
        sort(id.begin(),id.end(),[&](const int& x,const int& y){
            return a[x][i]<a[y][i];
        });
        int z=0;
        ll la=0;
        for(int j=0;j<n;++j){
            g[z]+=a[id[j]][i]-la;
            la=a[id[j]][i];
            z|=(1<<id[j]);
        }
    }
    for(int k=1;k<(1<<n);k<<=1){
        for(int i=0;i<(1<<n);i+=(k<<1)){
            for(int j=0;j<k;++j){
                g[i+j+k]+=g[i+j];
            }
        }
    }
    memset(e,0x3f,sizeof(e));
    for(int i=0;i<=n;++i)e[i][i]=0;
    for(int i=0;i<k;++i){
        int u,v;
        ll w;
        cin>>u>>v>>w;
        --u;--v;
        e[u][v]=e[v][u]=min(e[u][v],w);
    }
    for(int k=0;k<=n;++k){
        for(int i=0;i<=n;++i){
            for(int j=0;j<=n;++j){
                e[i][j]=min(e[i][j],e[i][k]+e[k][j]);
            }
        }
    }
    memset(f,0x3f,sizeof(f));
    f[0][n]=0;
    for(int i=0;i<(1<<n);++i){
        for(int la=0;la<=n;++la){
            if(f[i][la]>inf)continue;
            for(int to=0;to<n;++to){
                if(i&(1<<to))continue;
                int j=i|(1<<to);
                f[j][to]=min(f[j][to],f[i][la]+e[la][to]);
            }
        }
    }
    ll ans=inf;
    for(int i=1;i<(1<<n);++i){
        ll mi=inf;
        for(int la=0;la<n;++la){
            mi=min(mi,f[i][la]+e[la][n]);
        }
        ans=min(ans,mi+g[(1<<n)-1-i]);
    }
    cout<<ans<<'\n';
    return 0;
}