#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+5;
const int M=1e7+5;
const int mod=1e9+7;
int n,m;
int a[N];
ll jc[M],ny[M],mi[M],mi1[M];
ll ksm(ll x,int y=mod-2) {
    ll an=1;
    while (y) {
        if (y&1) an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
ll C(int x,int y) {
    return jc[x]*ny[y]%mod*ny[x-y]%mod;
}
void init(){
    const int lm=1e7;
    jc[0]=1;
    for (int i=1;i<=lm;++i) jc[i]=jc[i-1]*i%mod;
    ny[lm]=ksm(jc[lm]);
    for (int i=lm;i;--i) ny[i-1]=ny[i]*i%mod;
    mi[0]=1;
    for (int i=1;i<=lm;++i) mi[i]=mi[i-1]*m%mod;
    mi1[0]=1;
    for (int i=1;i<=lm;++i) mi1[i]=mi1[i-1]*(m-1)%mod;
}
int main(){
    freopen("ct.in","r",stdin);
    freopen("ct.out","w",stdout);
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;++i) {
        scanf("%d",&a[i]);
    }
    init();
    ll s=ksm(m,a[n]);
    for (int i=n;i>1;--i) {
        ll bs=0;
        const int la=a[i-1],no=a[i];
        for (int j=la-no;j>=0;--j) {
            bs=(bs+C(la-j-1,no-1)*mi[j]%mod*mi1[la-j-no])%mod;
        }
        s=s*bs%mod;
    }
    printf("%lld\n",s);
    return 0;
}