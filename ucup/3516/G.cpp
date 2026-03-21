#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5005;
const int mod=998244353;
int T;
int n,m;
ll f[N];
ll s1[N],s2[N],g[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>m;
        if(m==1){
            cout<<"1\n";
            continue;
        }
        ll ns=0;
        memset(f,0,sizeof(f));
        f[0]=1;
        for(int i=1;i<=n;++i){
            memset(s1,0,sizeof(ll)*(m+1));
            memset(s2,0,sizeof(ll)*(m+1));
            memset(g,0,sizeof(ll)*(m+1));
            for(int j=0;j<m-1;++j){
                if(j)s1[j]=s1[j-1],s2[j]=s2[j-1];
                s1[j]=(s1[j]+f[j])%mod;
                s2[j]=(s2[j]+f[j]*j)%mod;
            }
            ll ts=0,ss=0;
            for(int j=0;j<m-1;++j){
                const int fj=j/2;
                ll f1=s1[fj]*(m-j)%mod;
                ll f2=2*s2[fj]%mod;
                ll f3=(s1[j]-s1[fj]+mod)%mod*(m+j)%mod;
                ll f4=(s2[j]-s2[fj]+mod)%mod*2%mod;
                g[j]=(f1+f2+f3-f4+mod)%mod;
                ts=(ts+g[j])%mod;
            }
            for(int j=0;j<m-1;++j){
                ll xs=(1ll*m*m-1ll*(m-j)*(m-j-1)/2)%mod;
                ss=(ss+f[j]*xs)%mod;
            }
            ns=(ns*m%mod*m+ss-ts+mod)%mod;
            memcpy(f,g,sizeof(ll)*(m+1));
        }
        for(int i=0;i<m-1;++i)ns=(ns+f[i])%mod;
        cout<<ns<<'\n';
    }
    return 0;
}