#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int mod=998244353;
int n;
int m;
ll ksm(ll x,int y=mod-2){
    ll an=1;
    while(y){
        if(y&1)an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
ll jc(int x){
    ll an=1;
    for(int i=2;i<=x;++i)an=an*i%mod;
    return an;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        int a;
        cin>>a;
        m+=a;
    }
    cout<<jc(m)*ksm(m-n+1)%mod<<'\n';
    return 0;
}