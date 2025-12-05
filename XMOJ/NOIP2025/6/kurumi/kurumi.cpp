#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int mod=998244353;
const int N=15;
const int M=105;
int n,m;
int cnt[N][N];
ll jc[M],ny[M];
ll mip[M][N];
ll ksm(ll x,int y=mod-2){
    ll an=1;
    while(y){
        if(y&1)an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
void init(int lm){
    jc[0]=1;
    for(int i=1;i<=lm;++i)jc[i]=jc[i-1]*i%mod;
    ny[lm]=ksm(jc[lm]);
    for(int i=lm;i;--i)ny[i-1]=ny[i]*i%mod;
    for(int i=0;i<=lm;++i){
        mip[i][0]=1;
        for(int j=1;j<=n;++j){
            mip[i][j]=mip[i][j-1]*jc[i]%mod;
        }
    }
}
ll C(int x,int y){
    if(y<0||x<y)return 0;
    return jc[x]*ny[y]%mod*ny[x-y]%mod;
}
ll g0[N][M],g1[N][M];
int main(){
    freopen("kurumi.in","r",stdin);
    freopen("kurumi.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;++i){
        for(int j=1;j<=m;++j){
            int c;
            scanf("%1d",&c);
            cnt[i][c]++;
        }
    }
    init(m);
    for(int i=1;i<=n;++i){
        for(int j=0;j<=m;++j){
            g0[i][j]=ksm(mip[j][i-1]*ksm(C(m,j),i)%mod);
        }
    }
    ll ans=0;
    for(int z=1;z<(1<<n);++z){
        vector<int> id;
        for(int i=0;i<n;++i){
            if(z&(1<<i))id.push_back(i);
        }
        int siz=__builtin_popcount(z);
        vector<ll> f(m+1);
        f[0]=1;
        for(int di=0;di<10;++di){
            int mil=m;
            for(int no:id){
                mil=min(mil,cnt[no][di]);
            }
            if(mil==0)continue;
            vector<ll> nf(mil+1);
            nf[0]=1;
            for(int i=1;i<=mil;++i){
                nf[i]=mip[i][siz-1];
                for(int no:id){
                    nf[i]=nf[i]*C(cnt[no][di],i)%mod;
                }
            }
            for(int la=m;la>=0;--la){
                if(!f[la])continue;
                for(int i=1;i<=mil;++i){
                    f[la+i]=(f[la+i]+f[la]*nf[i])%mod;
                }
            }
        }
        ll sum=0;
        for(int i=0;i<=m;++i){
            sum=(sum+f[i]*g0[siz][i])%mod;
        }
        if(siz&1)ans=(ans+sum)%mod;
        else ans=(ans-sum+mod)%mod;
    }
    printf("%lld\n",ans);
    return 0;
}