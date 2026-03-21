#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e4+5;
const int mod=998244353;
ll jc[N*N/3];
ll p[N<<1],ip[N<<1];
int T;
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
    const int lim=N*N/3-3;
    jc[0]=1;
    for(int i=1;i<=lim;++i)jc[i]=jc[i-1]*i%mod;
    const int lm=N*2-5;
    p[0]=1;
    for(int i=1;i<=lm;++i)p[i]=p[i-1]*jc[i]%mod;
    for(int i=1;i<=lm;++i){
        ip[i]=ksm(p[i]);
    }
}
ll calc(int x,int y){
    if(!x||!y)return 1;
    return ip[x+y-1]*p[x-1]%mod*p[y-1]%mod;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    init();
    cin>>T;
    while(T--){
        int n,m;
        cin>>n>>m;
        if((n*m)%3!=0){
            cout<<"0\n";
            continue;
        }
        if(m%3==0)swap(n,m);
        int m1=m/3,m2=(m+1)/3,m3=m-m1-m2;
        ll an=jc[n*m/3]*calc(n/3,m1)%mod*calc(n/3,m2)%mod*calc(n/3,m3)%mod;
        cout<<an<<'\n';
    }
    return 0;
}