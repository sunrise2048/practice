#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
const int mod=998244353;
int T;
vector<int> pr;
bool isp[N];
int mu[N];
int w[N];
int n,k;
int a[N];
ll t[N][7];
ll s[N][13];
void init(){
    const int n=2e5;
    mu[1]=1;
    for(int i=2;i<=n;++i){
        if(!isp[i]){
            mu[i]=-1;
            pr.push_back(i);
            for(int j=i;j<=n;j+=i)w[j]++;
        }
        for(int p:pr){
            if(i*p>n)break;
            isp[i*p]=1;
            if(i%p==0){
                break;
            }
            mu[i*p]=-mu[i];
        }
    }
}
ll ksm(ll x,int y=mod-2){
    ll an=1;
    while(y){
        if(y&1)an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    init();
    while(T--){
        cin>>n>>k;
        for(int i=1;i<=n;++i){
            memset(t[i],0,sizeof(t[i]));
            memset(s[i],0,sizeof(s[i]));
        }
        for(int i=1;i<=n;++i){
            cin>>a[i];
            t[a[i]][w[a[i]]]++;
        }
        for(int i=1;i<=n;++i){
            for(int j=i*2;j<=n;j+=i){
                for(int c=0;c<7;++c){
                    t[i][c]=(t[i][c]+t[j][c])%mod;
                }
            }
        }
        for(int i=1;i<=n;++i){
            for(int j=0;j<7;++j){
                s[i][j+j]=(s[i][j+j]+t[i][j]*(t[i][j]-1)/2)%mod;
                for(int k=0;k<j;++k){
                    s[i][j+k]=(s[i][j+k]+t[i][j]*t[i][k])%mod;
                }
            }
        }
        for(int i=1;i<=n;++i){
            for(int k=0;k<13;++k){
                for(int j=2;i*j<=n;++j){
                    s[i][k]=(s[i][k]+s[i*j][k]*mu[j]+mod)%mod;
                }
            }
        }
        ll ans=0;
        for(int i=1;i<=n;++i){
            for(int j=0;j<13;++j){
                if(!s[i][j])continue;
                ans=(ans+s[i][j]*ksm(j-w[i],k))%mod;
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}