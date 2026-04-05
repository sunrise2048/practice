#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=16;
const int inf=1e9;
int T;
int n,m;
int a[N][N];
int lf[1<<N][N];
int f[N][N],g[N][N];
int c[N][N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=0;i<n;++i){
            a[i][m]=0;
            for(int j=0;j<m;++j){
                cin>>a[i][j];
                a[i][m]^=a[i][j];
            }
        }
        for(int j=0;j<=m;++j){
            a[n][j]=0;
            for(int i=0;i<n;++i){
                a[n][j]^=a[i][j];
            }
        }
        ++n;++m;
        memset(f,0x3f,sizeof(f));memset(g,0x3f,sizeof(g));
        for(int qj=0;qj<m;++qj){
            for(int i=0;i<n;++i){
                for(int j=0;j<n;++j){
                    if(i==j)continue;
                    c[i][j]=0;
                    for(int k=0;k<m;++k){
                        if(k==qj)continue;
                        c[i][j]+=abs(a[i][k]-a[j][k]);
                    }
                }
            }
            for(int i=0;i<(1<<n);++i){
                memset(lf[i],0x3f,sizeof(int)*n);
            }
            for(int i=0;i<n;++i){
                lf[1<<i][i]=0;
            }
            for(int i=1;i<(1<<n);++i){
                for(int ls=0;ls<n;++ls){
                    if(!(i&(1<<ls)))continue;
                    for(int j=0;j<n;++j){
                        if(i&(1<<j))continue;
                        lf[i|(1<<j)][j]=min(lf[i|(1<<j)][j],lf[i][ls]+c[ls][j]);
                    }
                }
            }
            for(int i=0;i<(1<<n);++i){
                if(__builtin_popcount(i)!=n-1)continue;
                int qi=0,nf=inf;
                for(int j=0;j<n;++j){
                    if(i&(1<<j)){
                        nf=min(nf,lf[i][j]);
                        continue;
                    }
                    qi=j;
                }
                f[qi][qj]=nf;
            }
        }
        for(int qi=0;qi<n;++qi){
            for(int i=0;i<m;++i){
                for(int j=0;j<m;++j){
                    if(i==j)continue;
                    c[i][j]=0;
                    for(int k=0;k<n;++k){
                        if(k==qi)continue;
                        c[i][j]+=abs(a[k][i]-a[k][j]);
                    }
                }
            }
            for(int i=0;i<(1<<m);++i){
                memset(lf[i],0x3f,sizeof(int)*m);
            }
            for(int i=0;i<m;++i){
                lf[1<<i][i]=0;
            }
            for(int i=1;i<(1<<m);++i){
                for(int ls=0;ls<m;++ls){
                    if(!(i&(1<<ls)))continue;
                    for(int j=0;j<m;++j){
                        if(i&(1<<j))continue;
                        lf[i|(1<<j)][j]=min(lf[i|(1<<j)][j],lf[i][ls]+c[ls][j]);
                    }
                }
            }
            for(int i=0;i<(1<<m);++i){
                if(__builtin_popcount(i)!=m-1)continue;
                int qj=0,nf=inf;
                for(int j=0;j<m;++j){
                    if(i&(1<<j)){
                        nf=min(nf,lf[i][j]);
                        continue;
                    }
                    qj=j;
                }
                g[qi][qj]=nf;
            }
        }
        int ans=inf;
        for(int i=0;i<n;++i){
            for(int j=0;j<m;++j){
                ans=min(ans,f[i][j]+g[i][j]);
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}