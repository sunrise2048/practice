#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int mod=998244353;
ll ksm(ll x,ll y=mod-2){
    y%=(mod-1);
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
    ll n;
    cin>>n;
    ll ans=(ksm(2,n)-1)*(ksm(2,n)-1)%mod;
    ans=(ans-(ksm(3,n)-1-2*(ksm(2,n)-1)+2*mod)%mod+mod)%mod;
    ans=(ans-2*(ksm(3,n)-1-(ksm(2,n)-1)+mod)%mod+ksm(2,n)-1+mod)%mod;
    cout<<ans<<'\n';
    return 0;
}