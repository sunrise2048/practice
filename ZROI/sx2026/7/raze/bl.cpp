#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=105;
const int mod=998244353;
int n,m;
ll f[N][N][N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    f[0][0][0]=1;
    for(int i=0;i<=n;++i){
        for(int j=0;j<m;++j){
            for(int k=0;i+k+2<=n;++k){
                for(int t=0;i+k+t+2<=n;++t){
                    for(int las=0;las<=n;++las){
                        f[i+k+t+2][j+1][las^t]=(f[i+k+t+2][j+1][las^t]+f[i][j][las])%mod;
                    }
                }
            }
        }
    }
    ll s=0;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j)s=(s+f[i][m][j])%mod;
    }
    cout<<s<<'\n';
    return 0;
}