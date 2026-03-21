#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e4+5;
const int mod=998244353;
ll jc[N*N/3],ny[N*N/3];
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
    ny[lim]=ksm(jc[lim]);
    for(int i=lim;i;--i){
        ny[i-1]=ny[i]*i%mod;
        ny[i]=ny[i]*jc[i-1]%mod;
    }
}
int main(){
    freopen("trominoes.in","r",stdin);
    freopen("trominoes.out","w",stdout);
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
        ll an=jc[n*m/3];
        for(int i=3;i<=n+m-1;i+=3){
            an=an*ksm(ny[i/3],min({i,n+m-i,n,m}))%mod;
        }
        cout<<an<<'\n';
    }
    return 0;
}