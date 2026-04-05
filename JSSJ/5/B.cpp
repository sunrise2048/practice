#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=505;
const int mod=998244353;
int n;
vector<int> e[N],son[N];
vector<int> nfd;
int si[N];
ll f0[N][N],f1[N][N],s0[N],s1[N];
ll jc[N],ny[N],inv[N];
ll val[N],ans[N];
ll ksm(ll x,int y=mod-2){
    ll an=1;
    while(y){
        if(y&1)an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
void dfs(int no,int fa){
    nfd.push_back(no);
    for(int to:e[no]){
        if(to==fa)continue;
        son[no].push_back(to);
        dfs(to,no);
    }
}
ll a[N],b[N],na[N],nb[N];
ll calc(int y){
    int x=y-1;
    if(x<0)x+=mod;
    for(int no:nfd){
        si[no]=1;
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        a[1]=b[1]=1;
        for(int to:son[no]){
            int lm=si[no]+si[to];
            for(int i=1;i<=lm;++i){
                na[i]=nb[i]=0;
            }
            ll bs=(s0[to]+s1[to])%mod;
            for(int i=1;i<=si[no];++i){
                na[i]=(na[i]+a[i]*bs)%mod;
                for(int j=1;j<=si[to];++j){
                    na[i+j]=(na[i+j]-a[i]*f1[to][j]%mod+mod)%mod;
                    nb[i+j]=(nb[i+j]+b[i]*f0[to][j])%mod;
                }
            }
            si[no]=lm;
            for(int i=1;i<=lm;++i){
                a[i]=na[i];
                b[i]=nb[i];
            }
        }
        s0[no]=s1[no]=0;
        for(int i=1;i<=si[no];++i){
            f0[no][i]=a[i]*inv[i]%mod;
            f1[no][i]=b[i]*x%mod*inv[i]%mod;
            s0[no]=(s0[no]+f0[no][i])%mod;
            s1[no]=(s1[no]+f1[no][i])%mod;
        }
    }
    return (s0[1]+s1[1])*jc[n]%mod;
}
ll poly[N],np[N];
ll gx[N];
void cz(){
    poly[0]=1;
    int de=0;
    for(int x=0;x<=n;++x){
        fill(np,np+de+2,0);
        for(int i=0;i<=de;++i){
            np[i]=(np[i]-x*poly[i]%mod+mod)%mod;
            np[i+1]=(np[i+1]+poly[i])%mod;
        }
        ++de;
        for(int i=0;i<=de;++i)poly[i]=np[i];
    }
    for(int x=0;x<=n;++x){
        gx[n]=poly[n+1];
        for(int i=n;i;--i){
            gx[i-1]=(poly[i]+x*gx[i])%mod;
        }
        ll bs=val[x]*ny[x]%mod*ny[n-x]%mod;
        if((n-x)&1)bs=(mod-bs)%mod;
        for(int i=0;i<=n;++i){
            ans[i]=(ans[i]+bs*gx[i])%mod;
        }
    }
}
int main(){
    freopen("particle.in","r",stdin);
    freopen("particle.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<n;++i){
        int u,v;
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    jc[0]=1;
    for(int i=1;i<=n;++i)jc[i]=jc[i-1]*i%mod;
    ny[n]=ksm(jc[n]);
    for(int i=n;i;--i)ny[i-1]=ny[i]*i%mod;
    for(int i=1;i<=n;++i)inv[i]=ny[i]*jc[i-1]%mod;
    dfs(1,0);
    reverse(nfd.begin(),nfd.end());
    for(int i=0;i<=n;++i){
        val[i]=calc(i);
    }
    cz();
    for(int i=1;i<=n;++i){
        cout<<ans[i]<<'\n';
    }
    return 0;
}