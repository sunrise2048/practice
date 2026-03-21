#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
const int mod=998244353;
int n,m;
ll jc[N],ny[N];
ll ksm(ll x,int y=mod-2){
    ll an=1;
    while(y){
        if(y&1)an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
int fa[N],si[N];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
vector<int> e[N][2];
int cn[N];
int main(){
    freopen("data4.in","r",stdin);
    freopen("purchase.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    jc[0]=1;
    for(int i=1;i<=m;++i)jc[i]=jc[i-1]*i%mod;
    ny[m]=ksm(jc[n]);
    for(int i=m;i;--i){
        ny[i-1]=ny[i]*i%mod;
        ny[i]=ny[i]*jc[i-1]%mod;
    }
    iota(fa+1,fa+n+1,1);
    for(int i=1;i<=m;++i){
        int a,b;
        cin>>a>>b;
    }
    return 0;
}