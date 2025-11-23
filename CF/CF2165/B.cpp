#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5005;
const int mod=998244353;
int T;
int n;
int a[N];
int t[N];
int f[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;++i)t[i]=0;
        for(int i=1;i<=n;++i){
            cin>>a[i];
            t[a[i]]++;
        }
        memset(f,0,sizeof(int)*(n+1));
        f[0]=1;
        for(int i=1;i<=n;++i){
            for(int j=n;j>=0;--j){
                if(!f[j])continue;
                f[j+t[i]]=(f[j+t[i]]+(ll)f[j]*t[i])%mod;
            }
        }
        ll bs=1;
        sort(t+1,t+n+1,[](const int& x,const int& y){
            return x>y;
        });
        t[n+1]=0;
        int lsum=0;
        ll ans=0;
        for(int i=1;i<=n+1;++i){
            for(int j=0;j<=n;++j){
                if(!f[j])continue;
                f[j+t[i]]=(f[j+t[i]]-(ll)f[j]*t[i]%mod+mod)%mod;
            }
            ll ns=0;
            for(int j=0;j<=n;++j){
                if(j+lsum>=t[i]){
                    ns=(ns+f[j])%mod;
                }
            }
            ans=(ans+ns*bs)%mod;
            bs=bs*t[i]%mod;
            lsum+=t[i];
        }
        cout<<ans<<'\n';
    }
    return 0;
}