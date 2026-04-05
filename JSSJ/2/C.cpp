#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=105;
const int mod=998244353;
int T;
int n;
int t[N],cn;
int f[N][N][N];
ll C[N][N];
void init(){
    const int n=100;
    C[0][0]=1;
    for(int i=1;i<=n;++i){
        C[i][0]=1;
        for(int j=1;j<=i;++j){
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
        }
    }
}
int main(){
    freopen("graph.in","r",stdin);
    freopen("graph.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    init();
    cin>>T;
    while(T--){
        cin>>n;
        memset(t,0,sizeof(t));cn=0;
        int mx=0;
        for(int i=1;i<=n;++i){
            int a;
            cin>>a;
            mx=max(mx,a);
            if(a==-1)++cn;
            else t[a]++;
        }
        for(int i=1;i<=n;++i)memset(f[i],0,sizeof(f[i]));
        f[n][0][0]=1;
        for(int i=n;i>1;--i){
            for(int j=0;j<=cn;++j){
                for(int k=(i>mx?0:1);k<n;++k){
                    if(!f[i][j][k])continue;
                    const ll nf=f[i][j][k];
                    for(int nc=0;nc+j<=cn;++nc){
                        int tc=nc+t[i-1];
                        if(i>mx&&!j&&nc+t[i-1]){
                            if(nc+t[i-1]<2)continue;
                            f[i-1][j+nc][tc/2]=(f[i-1][j+nc][tc/2]+nf*C[cn][nc])%mod;
                            continue;
                        }
                        if(tc){
                            if(!k)continue;
                            f[i-1][j+nc][(k+tc)/2]=(f[i-1][j+nc][(k+tc)/2]+nf*C[cn-j][nc])%mod;
                            continue;
                        }
                        f[i-1][j][k/2]=(f[i-1][j][k/2]+nf)%mod;
                    }
                }
            }
        }
        ll ans=0;
        for(int i=1;i<=n;++i)ans=(ans+f[1][cn][i])%mod;
        cout<<ans<<'\n';
    }
    return 0;
}