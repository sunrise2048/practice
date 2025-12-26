#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5005;
const int mod=1e9+7;
const ll ny2=(mod+1)/2;
const ll ny3=(mod+1)/3;
const ll ny4=(mod+1)/4;
int T;
int n,m;
int f[N][N][2][2];
int g[2][N];
int sum[N][N];
ll ksm(ll x,int y){
    ll an=1;
    while(y){
        if(y&1)an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
void init(){
    f[1][1][0][0]=ny4;
    f[1][1][0][1]=ny4*ny4*3%mod;
    g[1][1]=ny4*3%mod*ny4*3%mod;
    const int n=5000;
    for(int i=1;i<=n;++i){
        if(i!=1)memset(g[i&1],0,sizeof(g[i&1]));
        for(int j=1;j<=n;++j){
            if(i+j!=2){
                f[i][j][0][0]=(f[i][j][0][0]+f[i][j-1][0][0]*ny4*3%mod*ny4)%mod;
                f[i][j][0][1]=(f[i][j][0][1]+f[i][j-1][0][0]*ny4*3%mod*ny4*2%mod*ny4)%mod;
                f[i][j][0][1]=(f[i][j][0][1]+f[i][j-1][0][1]*ny4*3%mod*ny4)%mod;
                f[i][j][0][0]=(f[i][j][0][0]+f[i][j-1][1][0]*ny3*2%mod*ny4)%mod;
                f[i][j][0][1]=(f[i][j][0][1]+f[i][j-1][1][0]*ny3*2%mod*ny4*2%mod*ny4)%mod;
                f[i][j][0][1]=(f[i][j][0][1]+f[i][j-1][1][1]*ny3*2%mod*ny4)%mod;
                f[i][j][1][0]=(f[i][j][1][0]+g[(i-1)&1][j]*ny4)%mod;
                f[i][j][1][1]=(f[i][j][1][1]+g[(i-1)&1][j]*ny4%mod*ny4*3)%mod;
                g[i&1][j]=(g[i&1][j]+g[(i-1)&1][j]*ny4*3%mod*ny4*3)%mod;
                g[i&1][j]=(g[i&1][j]+f[i][j-1][0][0]*ny4*2%mod*ny4*3%mod*ny4*3)%mod;
                g[i&1][j]=(g[i&1][j]+f[i][j-1][0][1]*ny4*3%mod*ny4*3)%mod;
                g[i&1][j]=(g[i&1][j]+f[i][j-1][1][0]*ny4*2%mod*ny4*3%mod*ny3*2)%mod;
                g[i&1][j]=(g[i&1][j]+f[i][j-1][1][1]*ny4*3%mod*ny3*2)%mod;
            }
            sum[i][j]=(f[i][j][0][0]*ny4%mod*ny4%mod*7%mod+f[i][j][0][1]*ny4%mod+f[i][j][1][0]*ny3%mod*ny4%mod*6%mod+f[i][j][1][1]*ny3%mod)%mod;
            sum[i][j]=(1ll*sum[i][j]+sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+mod)%mod;
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    init();
    cin>>T;
    while(T--){
        int n,m;
        cin>>n>>m;
        cout<<sum[n][m]*ksm(4,(n+1)*(m+1))%mod<<'\n';
    }
    return 0;
}