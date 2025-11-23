#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=25;
const int M=4005;
const int V=405;
int T;
int n,m;
int h[N];
double p;
double f[M][V][N],g[M];
int main(){
    cin>>T;
    while (T--) {
        cin>>n>>m>>p;
        p/=100;
        int mi=V,ns=0;
        for (int i=1;i<=n;++i) {
            cin>>h[i];
            ns+=h[i];
            mi=min(mi,h[i]);
        }
        ns-=mi*n;
        for (int i=0;i<=m;++i) {
            f[i][1][0]=1;
        }
        for (int i=1;i<=m;++i) {
            for (int j=1;j<=mi;++j) {
                if (j!=1) {
                    f[i][j][0]=p*f[i-1][j-1][0]+(1-p)*max(f[i-1][j-1][n-1],f[i-1][j][0]);
                }
                for (int k=1;k<n;++k) {
                    f[i][j][k]=p*f[i-1][j-(j!=1)][k]+(1-p)*f[i-1][j][k-1];
                }
            }
        }
        if (ns<n) {
            printf("%.15f\n",f[m][mi][ns]);
            continue;
        }
        for (int i=0;i<=ns+1;++i) g[i]=0;
        g[ns]=1;
        double ans=0;
        for (int i=1;i<=m;++i) {
            if (i>=ns) ans+=(1-p)*g[1]*f[m-i][max(1,mi-(i-ns))][0];
            for (int j=1;j<=ns;++j) {
                g[j]=p*g[j]+(1-p)*g[j+1];
            }
        }
        printf("%.15f\n",ans);
    }
    return 0;
}