#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=305;
const int mod=1e9+7;
int T;
int n,k;
int mi;
int s[N];
ll f[N];
ll C[N][N];
void init(){
    const int lm=300;
    C[0][0]=1;
    for(int i=1;i<=lm;++i){
        C[i][0]=1;
        for(int j=1;j<=i;++j){
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
        }
    }
}
int main(){
    freopen("inv.in","r",stdin);
    freopen("inv.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    init();
    cin>>T;
    while(T--){
        cin>>n>>k;
        memset(s,0,sizeof(s));
        memset(f,0,sizeof(f));
        f[0]=1;
        s[0]=1;
        for(int i=1;i<n;++i){
            mi=1;
            for(int j=0;j<=k;++j){
                s[j]=(s[j]+mi)%mod;
                mi=1ll*mi*i%mod;
            }
            for(int j=k;j>=0;--j){
                f[j]=f[j]*s[0]%mod;
                for(int t=1;t<=j;++t){
                    f[j]=(f[j]+s[t]*f[j-t]%mod*C[j][t])%mod;
                }
            }
        }
        cout<<f[k]<<'\n';
    }
    return 0;
}