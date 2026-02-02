#include<bits/stdc++.h>
using namespace std;
using ll=unsigned long long;
const int N=6e5+5;
const int W=20;
const int lm=1e9+7;
int n;
ll a[N];
bool fl[N];
int id[N];
int K;
ll bs[W];
ll f[1<<W],g[1<<W];
mt19937_64 mt(time(0));
void fwt(ll* f,int len){
    for(int k=1;k<len;k<<=1){
        for(int i=0;i<len;i+=(k<<1)){
            for(int j=0;j<k;++j){
                ll x=f[i+j],y=f[i+j+k];
                f[i+j]=x+y;
                f[i+j+k]=x-y;
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        fl[i]=1;
    }
    {
        ll nv=a[1];
        for(int i=1;i<=n;++i)a[i]^=nv;
    }
    while((1<<K)<n)++K;
    K=max(K,14);
    int T=4;
    while(T--){
        for(int i=0;i<(1<<K);++i)f[i]=mt()%lm,g[i]=0;
        for(int i=0;i<K;++i){
            bs[i]=mt()&((1ull<<63)-1);
        }
        for(int i=1;i<=n;++i){
            id[i]=0;
            for(int j=0;j<K;++j){
                if(__builtin_popcountll(a[i]&bs[j])&1)id[i]|=(1<<j);
            }
        }
        ll ns=0;
        for(int i=1;i<=n;++i){
            ns+=f[id[i]];
            g[id[i]]++;
        }
        fwt(f,1<<K);fwt(g,1<<K);
        for(int i=0;i<(1<<K);++i)f[i]=f[i]*g[i];
        fwt(f,1<<K);
        for(int i=1;i<=n;++i){
            fl[i]&=(f[id[i]]==(1<<K)*ns);
        }
    }
    vector<ll> as;
    for(int i=1;i<=n;++i){
        if(fl[i])as.push_back(a[i]);
    }
    sort(as.begin(),as.end());
    cout<<as.size()<<'\n';
    for(ll no:as)cout<<no<<' ';
    return 0;
}