#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=21;
const int mod=998244353;
int n,m,p;
int e[N][N];
ll w[N];
ll ny[1<<N],s[1<<N];
ll f[N+1][1<<N],g[N+1][1<<N];
int fa[N];
ll ksm(ll x,int y=mod-2){
    ll an=1;
    while(y){
        if(y&1)an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>p;
    for(int i=1;i<=m;++i){
        int u,v;
        cin>>u>>v;
        --u;--v;
        e[u][v]=e[v][u]=e[u][v]+1;
    }
    for(int i=0;i<n;++i)cin>>w[i];
    for(int i=1;i<(1<<n);++i){
        vector<int> id;
        for(int j=0;j<n;++j){
            if(i&(1<<j)){
                s[i]+=w[j];
                id.push_back(j);
            }
        }
        s[i]=ksm(s[i],p);
        ny[i]=ksm(s[i]);
        bool fl=1;
        for(int no:id)fa[no]=no;
        for(int x:id){
            int cn=0;
            for(int y:id){
                cn+=e[x][y];
                if(e[x][y])fa[find(x)]=find(y);
            }
            if(cn&1){
                fl=0;
                break;
            }
        }
        for(int x:id){
            if(find(x)!=find(id[0])){
                fl=0;
                break;
            }
        }
        if(!fl)g[__builtin_popcount(i)][i]=s[i];
    }
    for(int op=0;op<=n;++op){
        for(int k=1;k<(1<<n);k<<=1){
            for(int i=0;i<(1<<n);i+=(k<<1)){
                for(int j=0;j<k;++j){
                    g[op][i+j+k]=(g[op][i+j+k]+g[op][i+j])%mod;
                }
            }
        }
    }
    for(int i=0;i<(1<<n);++i)f[0][i]=1;
    for(int cn=1;cn<=n;++cn){
        for(int lc=0;lc<cn;++lc){
            for(int i=0;i<(1<<n);++i){
                f[cn][i]=(f[cn][i]+f[lc][i]*g[cn-lc][i])%mod;
            }
        }
        for(int k=1;k<(1<<n);k<<=1){
            for(int i=0;i<(1<<n);i+=(k<<1)){
                for(int j=0;j<k;++j){
                    f[cn][i+j+k]=(f[cn][i+j+k]-f[cn][i+j]+mod)%mod;
                }
            }
        }
        for(int i=0;i<(1<<n);++i){
            if(__builtin_popcount(i)!=cn){
                f[cn][i]=0;
                continue;
            }
            f[cn][i]=f[cn][i]*ny[i]%mod;
        }
        if(cn!=n){
            for(int k=1;k<(1<<n);k<<=1){
                for(int i=0;i<(1<<n);i+=(k<<1)){
                    for(int j=0;j<k;++j){
                        f[cn][i+j+k]=(f[cn][i+j+k]+f[cn][i+j])%mod;
                    }
                }
            }
        }
    }
    cout<<f[n][(1<<n)-1]<<'\n';
    return 0;
}