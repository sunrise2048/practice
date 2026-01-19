#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=55;
int n,x,y,nx,mod;
int z;
int f[N*N*N/8][N*N];
int id[N][N][N];
int C[N][N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>x>>y>>nx>>mod;
    nx-=n*(n-1)/2;
    C[0][0]=1;
    for(int i=1;i<=n;++i){
        C[i][0]=1;
        for(int j=1;j<=i;++j){
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
        }
    }
    z=n-x-y;
    int cn_id=0;
    for(int i=0;i<=x;++i){
        for(int j=0;j<=y;++j){
            for(int k=0;k<=z;++k){
                id[i][j][k]=++cn_id;
            }
        }
    }
    f[id[0][0][0]][0]=1;
    for(int i=0;i<=x;++i){
        for(int j=0;j<=y;++j){
            for(int k=0;k<=z;++k){
                const int lm=(i+j+k)*(i+j+k);
                const int np=i+j+k;
                for(int ns=0;ns<=lm;++ns){
                    const int nf=f[id[i][j][k]][ns];
                    if(!nf)continue;
                    if(i!=x)f[id[i+1][j][k]][ns+np-i+j]=(f[id[i+1][j][k]][ns+np-i+j]+nf)%mod;
                    if(j!=y)f[id[i][j+1][k]][ns+np-j+k]=(f[id[i][j+1][k]][ns+np-j+k]+nf)%mod;
                    if(k!=z)f[id[i][j][k+1]][ns+np-k+i]=(f[id[i][j][k+1]][ns+np-k+i]+nf)%mod;
                }
            }
        }
    }
    ll ans=0;
    for(int i=0;i<=x;++i){
        for(int j=0;j<=y;++j){
            for(int k=0;k<=z;++k){
                const int lm=(i+j+k)*(i+j+k);
                const int tlm=(n-i-j-k)*(n-i-j-k);
                const int np=(i+j+k)*(i+j+k-1)/2;
                const int tp=(n-i-j-k)*(n-i-j-k-1)/2;
                for(int ns=0;ns<=lm;++ns){
                    const int nf=f[id[i][j][k]][ns];
                    if(!nf)continue;
                    const int ts=nx-(ns-np)+tp;
                    if(ts<0||ts>tlm)continue;
                    ans=(ans+1ll*C[n][i+j+k]*nf%mod*f[id[x-i][y-j][z-k]][ts])%mod;
                }
            }
        }
    }
    cout<<ans<<'\n';
    return 0;
}