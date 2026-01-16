#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
const int mod=998244353;
int T;
int a,b,c;
ll jc[N<<1],ny[N<<1];
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
    const int n=4e5+7;
    jc[0]=1;
    for(int i=1;i<=n;++i)jc[i]=jc[i-1]*i%mod;
    ny[n]=ksm(jc[n]);
    for(int i=n;i;--i)ny[i-1]=ny[i]*i%mod;
}
ll C(int x,int y){
    if(x<y||y<0)return 0;
    return jc[x]*ny[y]%mod*ny[x-y]%mod;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    init();
    cin>>T;
    while(T--){
        cin>>a>>b>>c;
        ll ans=0;
        for(int i=5;i<=min(a,c)+5;++i){
            ll bs=(C(2*i-6,i-1)-C(2*i-6,i)+mod)%mod;
            ans=(ans+bs*(C(a+5,5)-C(i,5)+mod)%mod*C(a+c+5-2*i+5,a+5-i)%mod*jc[5]%mod*jc[a]%mod*jc[c])%mod;
        }
        cout<<(1-ans*ny[a+c+5]%mod+mod)%mod<<'\n';
    }
    return 0;
}