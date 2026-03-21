#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e7+5;
int n,k,mod;
ll f[N],ny[N];
int main(){
    freopen("perm.in","r",stdin);
    freopen("perm.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>k>>mod;
    f[1]=1;
    f[2]=2;
    ny[0]=ny[1]=1;
    ny[2]=(mod+1)/2;
    ll s=0;
    for(int i=3;i<=n;++i){
        ny[i]=(mod-mod/i)*ny[mod%i]%mod;
        f[i]=(3ll*(2*i-3)%mod*f[i-1]-(i-3)*f[i-2]%mod+mod)%mod*ny[i]%mod;
    }
    for(int i=1;i<=n;++i){
        s+=f[i]^(i+2);
    }
    cout<<f[n]<<' '<<s;
    return 0;
}