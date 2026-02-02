#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=55;
const int mod=998244353;
int n,m;
ll a[N][N];
ll f[N][N][N];
ll ans[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            cin>>a[i][j];
        }
    }
    f[0][n][n]=1;
    for(int len=1;len<m;++len){
        for(int i=n-1;i;--i){
            f[len-1][i][i]=(f[len-1][i][i]+f[len-1][i+1][i+1])%mod;
        }
        for(int i=1;i<=n;++i){
            for(int j=i;j<=n;++j){
                for(int k=i;k<=n;++k){
                    f[len][i][k]=(f[len][i][k]+f[len-1][i][j]*a[j][k])%mod;
                }
            }
        }
    }
    for(int i=n-1;i;--i)f[m-1][i][i]=(f[m-1][i][i]+f[m-1][i+1][i+1])%mod;
    for(int i=1;i<=n;++i){
        for(int j=i;j<=n;++j){
            ans[j]=(ans[j]+f[m-1][i][j]*a[j][i])%mod;
        }
    }
    for(int i=1;i<=n;++i)cout<<ans[i]<<' ';
    return 0;
}