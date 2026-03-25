#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
const ll inf=1e16;
int T;
int n;
ll a[N],b[N];
ll c[N],lc[N];
ll f[N][31];
ll as;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<n;++i)cin>>a[i];
        for(int i=1;i<=n;++i)cin>>b[i];
        for(int i=1;i<=n;++i){
            memset(f[i],0x3f,sizeof(f[i]));
        }
        as=0;
        for(int i=1;i<=n;++i){
            c[i]=0;
            if(i!=n)c[i]|=a[i];
            if(i!=1)c[i]|=a[i-1];
            lc[i]=c[i];
            for(int j=28;j>=0;--j){
                if(b[i]&(1<<j)){
                    c[i]|=(1<<j);
                }
                else if(c[i]&(1<<j))break;
            }
            lc[i]^=c[i];
            as+=c[i]-b[i];
        }
        for(int i=0;i<31;++i){
            if(i)f[1][i]=(1<<i)-(((1<<i)-1)&lc[1]);
            else f[1][i]=0;
        }
        for(int i=2;i<=n;++i){
            for(int j=0;j<31;++j){
                if(j&&(c[i]&(1<<j)))continue;
                ll nc=c[i]+(1<<j)-(((1<<j)-1)&lc[i]);
                ll ns=(1<<j)-(((1<<j)-1)&lc[i]);
                if(j==0){
                    nc=c[i];ns=0;
                }
                for(int k=0;k<31;++k){
                    ll la=c[i-1]+(1<<k)-(((1<<k)-1)&lc[i-1]);
                    if(k==0)la=c[i-1];
                    if((la&nc)!=a[i-1])continue;
                    f[i][j]=min(f[i][j],f[i-1][k]+ns);
                }
            }
        }
        ll ans=f[n][0];
        for(int i=1;i<31;++i)ans=min(ans,f[n][i]);
        ans+=as;
        if(ans>inf)ans=-1;
        cout<<ans<<'\n';
    }
    return 0;
}