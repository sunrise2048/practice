#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=505;
const int mod=1e9+7;
int n,m;
int p[N][N];
int np[N][N];
int f[N][N],g[N][N];
bool fl[N][N],flf[N][N];
int mi[N],mx[N],mxlen;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;++i){
        for(int j=1;j<=n;++j){
            cin>>p[i][j];
            np[i][p[i][j]]=j;
        }
    }
    for(int i=1;i<=n;++i){
        f[i][i]=g[i][i]=1;
    }
    for(int i=1;i<=n;++i){
        memset(mi,0x3f,sizeof(mi));
        memset(mx,0,sizeof(mx));
        mxlen=0;
        bool nf=1;
        const int fi=p[1][i];
        for(int j=i;j<=n;++j){
            int no=p[1][j];
            for(int k=2;k<=m;++k){
                mi[k]=min(mi[k],np[k][no]);
                if(mi[k]<np[k][fi])nf=0;
                mx[k]=max(mx[k],np[k][no]);
                mxlen=max(mxlen,mx[k]-mi[k]+1);
            }
            if(mxlen<=j-i+1){
                fl[i][j]=1;
                flf[i][j]=nf;
            }
        }
    }
    for(int len=2;len<=n;++len){
        for(int l=1;l+len-1<=n;++l){
            int r=l+len-1;
            for(int t=l;t<r;++t){
                g[l][r]=(g[l][r]+1ll*f[l][t]*g[t+1][r])%mod;
            }
            if(!fl[l][r])continue;
            if(flf[l][r])f[l][r]=g[l+1][r];
            g[l][r]=(g[l][r]+f[l][r])%mod;
        }
    }
    cout<<f[1][n]<<'\n';
    return 0;
}