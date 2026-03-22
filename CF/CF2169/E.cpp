#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3e5+5;
int T;
int n;
ll x[N],y[N],c[N];
ll f[N][16];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;++i){
            cin>>x[i];x[i]*=2;
        }
        for(int i=1;i<=n;++i){
            cin>>y[i];y[i]*=2;
        }
        for(int i=1;i<=n;++i){
            cin>>c[i];
        }
        for(int i=0;i<=n;++i){
            memset(f[i],~0x3f,sizeof(f[i]));
        }
        f[0][0]=0;
        for(int i=1;i<=n;++i){
            for(int j=0;j<16;++j){
                ll lf=max(f[i][j],f[i-1][j]);
                if(!(j&1)){
                    f[i][j|1]=max(f[i][j|1],lf+x[i]);
                }
                if(!(j&2)){
                    f[i][j|2]=max(f[i][j|2],lf-x[i]);
                }
                if(!(j&4)){
                    f[i][j|4]=max(f[i][j|4],lf+y[i]);
                }
                if(!(j&8)){
                    f[i][j|8]=max(f[i][j|8],lf-y[i]);
                }
                f[i][j]=max(f[i][j],f[i-1][j]+c[i]);
            }
        }
        cout<<f[n][15]<<'\n';
    }
    return 0;
}