#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=4e5+5;
const int mod=998244353;
int T;
int n;
ll s[N];
ll jc[N],ny[N];
ll ksm(ll x,int y=mod-2){
    ll an=1;
    while (y) {
        if (y&1) an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
void init(){
    const int lm=4e5;
    jc[0]=1;
    for (int i=1;i<=lm;++i) jc[i]=jc[i-1]*i%mod;
    ny[lm]=ksm(jc[lm]);
    for (int i=lm;i;--i) ny[i-1]=ny[i]*i%mod;
}
ll C(int x,int y){
    if(x<y||y<0)return 0;
    return jc[x]*ny[y]%mod*ny[x-y]%mod;
}
ll gn(int x){
    return ny[x]*jc[x-1]%mod;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    init();
    cin>>T;
    while (T--) {
        cin>>n;
        for (int i=1;i<=n;++i) {
            cin>>s[i];
            s[i]+=s[i-1];
            s[i]%=mod;
        }
        ll ans=s[n]*n%mod;
        ll nsum=s[n];
        for (int len=2;len<=n;++len) {
            nsum=(nsum+s[n-len+1]-s[len-1]+mod)%mod;
            for (int opl:{0,1}) {
                for (int opr:{0,1}) {
                    if ((n-opl-opr-len)%2!=0) continue;
                    if (opl+opr+len>n) continue;
                    ll cn=C((n-opl-opr-len)/2+len-1,len-1);
                    ans=(ans+cn*opl*s[n-len+1])%mod;
                    ans=(ans+cn*opr*(s[n]-s[len-1]+mod))%mod;
                    ans=(ans+cn*nsum)%mod;
                    ll fre=(n-opl-opr-len)/2*gn(len)%mod;
                    ans=(ans+cn*2%mod*fre%mod*nsum)%mod;
                }
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}