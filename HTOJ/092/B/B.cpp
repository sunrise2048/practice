#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+5;
const int mod=998244353;
int n;
ll a[N];
vector<int> e[N];
ll ksm(ll x,int y=mod-2){
    ll an=1;
    while(y){
        if(y&1)an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
ll si[N],sm[N];
void dfs(int no,int fa){
    sm[no]=no;
    si[no]=1;
    for(int to:e[no]){
        if(to==fa)continue;
        dfs(to,no);
        si[no]+=si[to];
        sm[no]=(sm[no]+sm[to])%mod;
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    ll sa=0;
    for(int i=1;i<n;++i){
        cin>>a[i];
        sa=(sa+ksm(a[i]))%mod;
    }
    for(int i=1;i<n;++i){
        int u,v;
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1,0);
    ll sum=0;
    for(int i=2;i<=n;++i){
        sum=(sum+si[i]*sm[i])%mod;
    }
    sum=sum*sa%mod;
    cout<<sum*ksm(n-1)%mod<<'\n';
    return 0;
}