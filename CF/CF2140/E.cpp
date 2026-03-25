#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=20;
const int M=1e6+5;
const int mod=1e9+7;
int T;
int n,m,k;
int zs;
int f[N][1<<N];
int t[N+1];
int dfs(int len,int z){
    if(len==0)return z;
    if(f[len][z]!=-1)return f[len][z];
    if((n-len)&1){
        f[len][z]=0;
        for(int i=0;i<=len;++i){
            if(!(zs&(1<<i)))continue;
            if(dfs(len-1,(z&((1<<i)-1))|((z>>(i+1))<<i))){
                f[len][z]=1;
                break;
            }
        }
    }
    else{
        f[len][z]=1;
        for(int i=0;i<=len;++i){
            if(!(zs&(1<<i)))continue;
            if(!dfs(len-1,(z&((1<<i)-1))|((z>>(i+1))<<i))){
                f[len][z]=0;
                break;
            }
        }
    }
    return f[len][z];
}
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
    cin>>T;
    while(T--){
        cin>>n>>m>>k;
        zs=0;
        for(int i=1;i<=k;++i){
            int z;
            cin>>z;--z;
            zs|=(1<<z);
        }
        memset(t,0,sizeof(t));
        for(int i=0;i<n;++i){
            memset(f[i],-1,sizeof(int)*(1<<i+1));
        }
        for(int i=0;i<(1<<n);++i){
            if(dfs(n-1,i))t[__builtin_popcount(i)]++;
        }
        ll ans=ksm(m,n);
        for(int i=2;i<=m;++i){
            ll bs=1;
            for(int j=1;j<=n;++j)bs=bs*(i-1)%mod;
            ll ny=ksm(i-1);
            for(int j=0;j<=n;++j){
                ans=(ans+bs*t[j])%mod;
                bs=bs*ny%mod*(m-i+1)%mod;
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}