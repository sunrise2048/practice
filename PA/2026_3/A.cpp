#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+5;
const int mod=1e9+7;
int n,k,m;
ll px[N],ps[N];
ll lap[N],las[N];
ll tp[N];
ll nyk;
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
    cin>>n>>k>>m;
    nyk=ksm(k);
    px[0]=1;
    tp[0]=max(0,k-m+1)*nyk%mod;
    lap[0]=tp[0];
    ps[0]=1;
    for(int i=1;i<m;++i){
        px[i]=(ps[i-1]-(i>k?ps[i-k-1]:0)+mod)*nyk%mod;
        ps[i]=(ps[i-1]+px[i])%mod;
        tp[i]=max(0,i+k-m+1)*nyk%mod;
        lap[i]=tp[i]*px[i]%mod;
    }
    for(int i=m-1;i>=0;--i){
        las[i]=(las[i+1]+lap[i])%mod;
    }
    ll ans=0;
    for(int i=0;i<m;++i){
        if(!tp[i]){
            ans=(ans+px[i]*n)%mod;
        }
        else{
            ans=(ans+(ksm(las[i],n)-ksm(las[i+1],n)+mod)*ksm(tp[i]))%mod;
        }
    }
    cout<<ans<<'\n';
    return 0;
}