#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
const int mod=998244353;
int n,k;
ll p[N];
ll sp[N];
ll ksm(ll x,int y=mod-2){
    ll an=1;
    while(y){
        if(y&1)an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
ll f[N];
int main(){
    ios::sync_with_stdio(0);
    cin>>n>>k;
    sp[0]=1;
    for(int i=1;i<=n;++i){
        cin>>p[i];
        int q;
        cin>>q;
        p[i]=p[i]*ksm(q)%mod;
        sp[i]=sp[i-1]*p[i]%mod;
    }
    f[k]=sp[k];
    for(int i=1;i<=n;++i){
        f[i]=(f[i]+f[i-1])%mod;
        if(i+k<=n){
            f[i+k]=(f[i+k]+(1-f[i-1]+mod)%mod*(1-p[i]+mod)%mod*sp[i+k]%mod*ksm(sp[i]))%mod;
        }
    }
    cout<<f[n]<<'\n';
    return 0;
}