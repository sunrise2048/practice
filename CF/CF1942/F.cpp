#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using I128=__int128;
const int N=2e5+5;
const int K=455;
const int kc=450;
const ll inf=1.5e18;
int n,q;
ll a[N];
int L[K],R[K];
int ks;
int kid[N];
ll f[K],g[K];
void cg(int k){
    f[k]=sqrtl(a[L[k]]);
    for(int i=L[k]+1;i<=R[k];++i){
        f[k]=sqrtl(f[k]+a[i]);
    }
    I128 ns=(I128)(f[k]+1)*(f[k]+1)-a[R[k]];
    if(ns>inf)ns=inf;
    for(int i=R[k]-1;i>=L[k];--i){
        ns=ns*ns-a[i];
        if(ns>inf)ns=inf;
    }
    g[k]=ns;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>q;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    ks=(n+kc-1)/kc;
    R[ks]=n;
    for(int i=ks;i;--i){
        L[i]=R[i]-kc+1;
        R[i-1]=L[i]-1;
    }
    L[1]=1;
    for(int i=1;i<=ks;++i){
        for(int j=L[i];j<=R[i];++j){
            kid[j]=i;
        }
        cg(i);
    }
    while(q--){
        int id;
        ll x;
        cin>>id>>x;
        a[id]=x;
        cg(kid[id]);
        ll val=0;
        for(int i=1;i<=ks;++i){
            if(val>=g[i])val=f[i]+1;
            else val=f[i];
        }
        cout<<val<<'\n';
    }
    return 0;
}