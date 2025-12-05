#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int K=10;
const int mod=1e9+7;
int T;
ll n;
int f[65][8];
ll g[1<<K][8][8];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    for(int z=0;z<(1<<10);++z){
        for(int la=0;la<8;++la){
            memset(f,0,sizeof(f));
            f[0][la]=1;
            for(int i=0;i<10;++i){
                for(int j=0;j<8;++j){
                    int op=(z>>i)&1;
                    for(int k=0;k<8;++k){
                        if(((j+k)&1)!=op)continue;
                        f[i+1][(j+k)/2]=(f[i+1][(j+k)/2]+f[i][j])%mod;
                    }
                }
            }
            for(int i=0;i<8;++i){
                g[z][la][i]=f[10][i];
            }
        }
    }
    cin>>T;
    while(T--){
        cin>>n;
        memset(f,0,sizeof(f));
        f[0][0]=1;
        for(int i=0;i<60;i+=10){
            for(int j=0;j<8;++j){
                if(f[i][j]==0)continue;
                int op=(n>>i)&((1<<10)-1);
                for(int k=0;k<8;++k){
                    f[i+10][k]=(f[i+10][k]+f[i][j]*g[op][j][k])%mod;
                }
            }
        }
        cout<<f[60][0]<<'\n';
    }
    return 0;
}