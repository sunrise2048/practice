#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3e5+5;
const int mod=998244353;
int T;
int n;
pair<int,int> op[N];
int p[N<<1];
ll g[N];
ll ig[N];
ll ksm(ll x,int y=mod-2){
    ll an=1;
    while(y){
        if(y&1)an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
void init(){
    const int n=3e5;
    g[0]=1;
    ig[0]=1;
    for(int i=1;i<=n;++i){
        g[i]=g[i-1]*(4*i-2)%mod*ksm(i+1)%mod;
        ig[i]=ksm(g[i]);
    }
}
ll ans;
ll as[N];
int fp[N<<1];
int fa[N<<1];
int si[N<<1];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void dfs(int x){
    si[x]=0;
    int y=x+1;
    while(y<p[x]){
        fp[y]=x;
        dfs(y);
        y=p[y]+1;
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    init();
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;++i){
            cin>>op[i].first>>op[i].second;
            p[op[i].first]=op[i].second;
        }
        ans=1;
        iota(fa,fa+2*n+1,0);
        p[0]=2*n+1;
        dfs(0);
        for(int i=n;i>=0;--i){
            as[i]=ans;
            if(!i)break;
            int x=op[i].first;
            ans=ans*ig[si[x]]%mod;
            int f=find(fp[x]);
            ans=ans*ig[si[f]]%mod;
            si[f]+=si[x]+1;
            ans=ans*g[si[f]]%mod;
            fa[find(x)]=f;
        }
        for(int i=0;i<=n;++i){
            cout<<as[i]<<' ';
        }
        cout<<'\n';
    }
    return 0;
}