#include <bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+5;
const int mod=998244353;
int n;
ll a[N],tag;
ll ny;
ll ksm(ll x,int y=mod-2) {
    ll an=1;
    while (y) {
        if (y&1) an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
int main() {
    freopen("fs.in","r",stdin);
    freopen("fs.out","w",stdout);
    scanf("%d",&n);
    for (int i=1;i<=n;++i) {
        scanf("%lld",&a[i]);
    }
    ny=ksm(n-1);
    for (int i=1;i<=n;++i) {
        ll la=(a[i]+tag)%mod;
        tag=(tag+la*ny)%mod;
        a[i]=(mod-tag)%mod;
    }
    for (int i=1;i<=n;++i) {
        printf("%lld ",(a[i]+tag)%mod);
    }
    return 0;
}