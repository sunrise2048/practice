#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
const int K=55;
const int mod=1e9+7;
int n;
ll ksm(ll x,int y=mod-2){
    ll an=1;
    while(y){
        if(y&1)an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
ll ans;
ll f[K][N];
int main(){
    cin>>n;
    for(int )
    cout<<ans<<'\n';
    return 0;
}