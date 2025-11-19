#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+5;
const int M=1e7+5;
const int mod=19260817;
int n;
int ne[M];
ll ny[M];
ll ksm(ll x,int y=mod-2) {
    ll an=1;
    while(y) {
        if(y&1) an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
int main(){
    freopen("nd.in","r",stdin);
    freopen("nd.out","w",stdout);
    scanf("%d",&n);
    int mx=0;
    for (int i=1;i<=n;++i) {
        int a;
        scanf("%d",&a);
        ne[a]=a;
        mx=max(mx,a);
    }
    const int lm=1e7;
    ne[lm+1]=lm+1;
    for (int i=lm;i;--i) {
        if(!ne[i])ne[i]=ne[i+1];
    }
    ny[0]=1;
    for (int i=1;i<=mx;++i) {
        ny[i]=ny[i-1]*i%mod;
    }
    ny[mx]=ksm(ny[mx]);
    ll ans=0;
    for (int i=mx;i;--i) {
        ll nn=ny[i]*ny[i-1]%mod;
        ny[i-1]=ny[i]*i%mod;
        ans=(ans+nn*ne[mx-i+1])%mod;
    }
    printf("%lld\n",ans);
    return 0;
}