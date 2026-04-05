#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5005;
const int mod=998244353;
int n,k;
vector<int> e[N];
int f[N][N];
const int lm=3002;
void dfs(int no,int fa){
    for(int i=0;i<=lm;++i)f[no][i]=1;
    for(int to:e[no]){
        if(to==fa)continue;
        dfs(to,no);
        ll bs=0;
        for(int i=0;i<=lm;++i){
            bs=(bs+f[to][i])%mod;
            f[no][i]=f[no][i]*bs%mod;
        }
    }
}
ll ksm(ll x,int y=mod-2){
    ll an=1;
    while(y){
        if(y&1)an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
ll ny[N];
ll gny(ll x){
    if(x<0)return mod-ny[-x];
    return ny[x];
}
ll cz(ll x){
    if(x<=lm)return f[1][x];
    ll ans=0;
    for(int i=0;i<=lm;++i){
        ll bs=f[1][i];
        for(int j=0;j<=lm;++j){
            if(i==j)continue;
            bs=bs*(x-j+mod)%mod*gny(i-j)%mod;
        }
        ans=(ans+bs)%mod;
    }
    return ans;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>k;
    for(int i=1;i<n;++i){
        int u,v;
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1,0);
    for(int i=1;i<=lm;++i)ny[i]=ksm(i);
    cout<<cz(k)<<'\n';
    return 0;
}