#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=55;
int n,m;
int a[N][N];
int s[N][N];
int f[N][N][N][N];
int main(){
    freopen("cut.in","r",stdin);
    freopen("cut.out","w",stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &a[i][j]);
            s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + a[i][j];
        }
    }
    for(int lx=1;lx<=n;++lx){
        for(int ly=1;ly<=m;++ly){
            if(lx+ly==2)continue;
            for (int xl = 1; xl <= n; ++xl) {
                for (int yl = 1; yl <= m; ++yl) {
                    int xr=xl+lx-1;
                    int yr=yl+ly-1;
                    int ans=2e9;
                    for(int k=xl;k<xr;++k)ans=min(ans,f[xl][yl][k][yr]+f[k+1][yl][xr][yr]);
                    for(int k=yl;k<yr;++k)ans=min(ans,f[xl][yl][xr][k]+f[xl][k+1][xr][yr]);
                    ans+=s[xr][yr]-s[xl-1][yr]-s[xr][yl-1]+s[xl-1][yl-1];
                    f[xl][yl][xr][yr]=ans;
                }
            }
        }
    }
    printf("%d\n",f[1][1][n][m]);
    return 0;
}