#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e7+5;
const int mod=998244353;
ll k1,k2,n,a,b;
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
ll C(int x,int y){
    if(x<y||y<0)return 0;
    return jc[x]*ny[y]%mod*ny[x-y]%mod;
}
int main(){
    cin>>k1>>k2>>n>>a>>b;
    jc[0]=1;
    for(int i=1;i<=n;++i){
        jc[i]=jc[i-1]*i%mod;
    }
    ny[n]=ksm(jc[n]);
    for(int i=n;i;--i){
        ny[i-1]=ny[i]*i%mod;
    }
    ll ans=0,cn=0;
    for(int k=0;k<=n;++k){
        if(k*(k1-k2)>n-1)continue;
        if((n-1-k*(k1-k2))%k2)continue;
        ll i=(n-1-k*(k1-k2))/k2;
        if(i<k)continue;
        ans=(ans+(k*a+(i-k)*b)%mod*C(n,i)%mod*C(i,k))%mod;
        cn=(cn+C(n,i)*C(i,k))%mod;
    }
    cout<<ans*ksm(cn)%mod<<'\n';
    return 0;
}