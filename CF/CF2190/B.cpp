#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=105;
const int mod=998244353;
int T;
int n;
char c[N];
ll f[N][N][4],g[N][N][4];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        memset(f,0,sizeof(f));
        memset(g,0,sizeof(g));
        cin>>n;
        for(int i=1;i<=n;++i){
            cin>>c[i];
        }
        f[n+1][0][0]=0;
        g[n+1][0][0]=1;
        for(int i=n;i;--i){
            memcpy(f[i],f[i+1],sizeof(f[i]));
            memcpy(g[i],g[i+1],sizeof(g[i]));
            if(c[i]==')'){
                for(int j=0;j<=n;++j){
                    f[i][j+1][0]=(f[i][j+1][0]+f[i+1][j][0]+g[i+1][j][0])%mod;
                    g[i][j+1][0]=(g[i][j+1][0]+g[i+1][j][0])%mod;
                    f[i][j+1][1]=(f[i][j+1][1]+f[i+1][j][1]+g[i+1][j][1])%mod;
                    g[i][j+1][1]=(g[i][j+1][1]+g[i+1][j][1])%mod;
                    f[i][j+1][3]=(f[i][j+1][3]+f[i+1][j][2]+g[i+1][j][2])%mod;
                    g[i][j+1][3]=(g[i][j+1][3]+g[i+1][j][2])%mod;
                    f[i][j+1][3]=(f[i][j+1][3]+f[i+1][j][3]+g[i+1][j][3])%mod;
                    g[i][j+1][3]=(g[i][j+1][3]+g[i+1][j][3])%mod;
                }
            }
            else{
                for(int j=1;j<=n;++j){
                    f[i][j-1][1]=(f[i][j-1][1]+f[i+1][j][0]+g[i+1][j][0])%mod;
                    g[i][j-1][1]=(g[i][j-1][1]+g[i+1][j][0])%mod;
                    f[i][j-1][2]=(f[i][j-1][2]+f[i+1][j][1]+g[i+1][j][1])%mod;
                    g[i][j-1][2]=(g[i][j-1][2]+g[i+1][j][1])%mod;
                    f[i][j-1][2]=(f[i][j-1][2]+f[i+1][j][2]+g[i+1][j][2])%mod;
                    g[i][j-1][2]=(g[i][j-1][2]+g[i+1][j][2])%mod;
                    f[i][j-1][3]=(f[i][j-1][3]+f[i+1][j][3]+g[i+1][j][3])%mod;
                    g[i][j-1][3]=(g[i][j-1][3]+g[i+1][j][3])%mod;
                }
            }
        }
        cout<<(f[1][0][3]-2*g[1][0][3]%mod+mod)%mod<<'\n';
    }
    return 0;
}