#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e6+5;
const int mod=676767677;
int T;
int n,m;
ll ksm(ll x,int y=mod-2){
    ll an=1;
    while(y){
        if(y&1)an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
ll jc[N],ny[N];
ll C(int x,int y){
    if(x<y||y<0)return 0;
    return jc[x]*ny[y]%mod*ny[x-y]%mod;
}
void init(){
    const int n=2e6;
    jc[0]=1;
    for(int i=1;i<=n;++i)jc[i]=jc[i-1]*i%mod;
    ny[n]=ksm(jc[n]);
    for(int i=n;i;--i)ny[i-1]=ny[i]*i%mod;
}
ll ans;
ll ps1[N],ps2[N];
ll qs[N];
ll calc(int a,int b){
    int x=min(a,b),y=max(a,b);
    ll sum=ps2[x+1]+(x+1)*(ps1[y+1]-ps1[x+1]+mod)%mod+(a+b+2)*(ps1[a+b+1]-ps1[y+1]+mod)%mod-(ps2[a+b+1]-ps2[y+1]+mod)%mod+mod;
    sum%=mod;
    return sum;
}
void solve(int l,int r,int d){
    if(l>r)return;
    const int mid=(l+r>>1);
    int sl=mid-l,sr=r-mid;
    ll bs=0;
    if(l!=1&&r!=n){
        bs=calc(sl,sr);
    }
    else if(r!=n){
        bs=(calc(sl-1,sr)+qs[sl+sr+1]-qs[sl]+mod)%mod;
    }
    else if(l!=1){
        bs=(calc(sl,sr-1)+qs[sl+sr+1]-qs[sr]+mod)%mod;
    }
    else{
        bs=(calc(sl-1,sr-1)+2*qs[sl+sr]-qs[sl]-qs[sr]+2*mod+m)%mod;
    }
    ans=(ans+bs*d)%mod;
    solve(l,mid-1,d+1);solve(mid+1,r,d+1);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    init();
    while(T--){
        cin>>n>>m;
        ans=0;
        for(int i=1;i<=n;++i){
            ll f0=0,f1=0;
            if(i<=n-2)f0=C(n+m-i-2,n-i+1);
            if(i<=n-1)f1=C(n+m-i-1,n-i+1);
            ps1[i]=(ps1[i-1]+f0)%mod;
            ps2[i]=(ps2[i-1]+f0*i)%mod;
            qs[i]=(qs[i-1]+f1)%mod;
        }
        solve(1,n,1);
        cout<<ans<<'\n';
    }
    return 0;
}