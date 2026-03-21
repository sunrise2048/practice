#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n,m,mod;
ll imi[N],ps[N],pp[N];
ll ksm(ll x,int y=mod-2){
    ll an=1;
    while(y){
        if(y&1)an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>m>>mod;
        imi[0]=1;
        imi[1]=ksm(m);
        for(int i=2;i<=n;++i)imi[i]=imi[i-1]*imi[1]%mod;
        ps[0]=1;
        pp[0]=1;
        for(int i=1;i<=n;++i){
            ps[i]=(ps[i-1]+imi[i])%mod;
            pp[i]=(pp[i-1]+imi[i]*(2*i+1))%mod;
        }
        ll ans=0;
        ll ss=0;
        for(int i=1;i<=n;++i){
            ll ns=ps[min(i-1,n-i)];
            ans=(ans+2*ns*ss)%mod;
            ss=(ss+ns)%mod;
            ans=(ans+pp[min(i-1,n-i)])%mod;
        }
        for(int i=1;i<n;++i){
            ll ns=(ps[min(i,n-i)]-1+mod)%mod;
            ans=(ans+2*ns*ss)%mod;
            ss=(ss+ns)%mod;
            ans=(ans+pp[min(i,n-i)]-2*ps[min(i,n-i)]%mod+1+mod)%mod;
        }
        cout<<ans<<'\n';
    }
    return 0;
}