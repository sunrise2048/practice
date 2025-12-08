#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=205;
const int M=2e4+5;
const int mod=1e9+7;
int n;
int a[N],b[N];
ll f[N][M];
ll jc[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    for(int i=1;i<=n;++i){
        cin>>b[i];
    }
    jc[0]=1;
    for(int i=1;i<=n;++i){
        jc[i]=jc[i-1]*i%mod;
    }
    f[0][0]=1;
    int s=0;
    for(int i=1;i<=n;++i){
        s+=b[i];
        for(int j=i;j;--j){
            for(int k=b[i];k<=s;++k){
                f[j][k]=(f[j][k]+f[j-1][k-b[i]])%mod;
            }
        }
    }
    ll ans=0;
    for(int i=1;i<=n;++i){
        if(a[i]>s)continue;
        for(int j=1;j<n;++j){
            for(int k=b[i];k<=s;++k){
                f[j][k]=(f[j][k]-f[j-1][k-b[i]]+mod)%mod;
            }
            ll bs=f[j][a[i]];
            ans=(ans+bs*jc[j]%mod*jc[n-j-1])%mod;
        }
        for(int j=n-1;j;--j){
            for(int k=b[i];k<=s;++k){
                f[j][k]=(f[j][k]+f[j-1][k-b[i]])%mod;
            }
        }
    }
    cout<<ans<<'\n';
    return 0;
}