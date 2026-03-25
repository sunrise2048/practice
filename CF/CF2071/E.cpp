#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
const int mod=998244353;
int T;
int n;
ll p[N];
ll ny[N];
ll bs[N];
ll gx[N];
ll lgx[N];
ll lg1[N],lg2[N];
ll ksm(ll x,int y=mod-2){
    ll an=1;
    while(y){
        if(y&1)an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
vector<int> e[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;++i){
            e[i].clear();
            int q;
            cin>>p[i]>>q;
            p[i]=p[i]*ksm(q)%mod;
            ny[i]=ksm(p[i]);
        }
        for(int i=1;i<n;++i){
            int u,v;
            cin>>u>>v;
            e[u].push_back(v);
            e[v].push_back(u);
        }
        ll s=0;
        for(int i=1;i<=n;++i){
            ll ns=(1-p[i]+mod)%mod;
            for(int to:e[i]){
                ns=ns*p[to]%mod;
            }
            bs[i]=ns;
            gx[i]=0;
            for(int to:e[i]){
                gx[i]=(gx[i]+ns*ny[to]%mod*(1-p[to]+mod))%mod;
            }
            s=(s+gx[i])%mod;
        }
        for(int i=1;i<=n;++i){
            lg1[i]=lg2[i]=0;
            lgx[i]=gx[i];
            for(int to:e[i]){
                lgx[i]=(lgx[i]+gx[to])%mod;
                ll nf=bs[to]*ny[i]%mod*(1-p[i]+mod)%mod;
                lg1[i]=(lg1[i]+gx[to]-nf+mod)%mod;
                lg2[i]=(lg2[i]+nf)%mod;
            }
        }
        ll ans=0;
        for(int i=1;i<=n;++i){
            ll ts=(s-gx[i]+mod)%mod;
            for(int to:e[i]){
                ts=(ts-lgx[to]+gx[i]+mod)%mod;
                ans=(ans+bs[i]*bs[to]%mod*ny[i]%mod*ny[to])%mod;
                ll nf=bs[i]*ny[to]%mod*(1-p[to]+mod)%mod;
                ll ng=bs[i]*ny[to]%mod;
                ll tg1=(lg1[to]-gx[i]+nf+mod)%mod;
                ans=(ans+(gx[i]-nf+mod)%mod*tg1%mod*ny[to])%mod;
                ll tg2=(lg2[to]-nf+mod)%mod;
                ans=(ans+ng*tg2)%mod;
            }
            ans=(ans+gx[i]*ts)%mod;
        }
        cout<<(mod+1)/2*ans%mod<<'\n';
    }
    return 0;
}