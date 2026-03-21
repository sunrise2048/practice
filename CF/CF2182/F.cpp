#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=6e5+5;
const int mod=998244353;
int n,m;
int t[61];
int ts[61];
int scn;
ll jc[N],ny[N];
ll er[N];
ll ksm(ll x,int y=mod-2){
    ll an=1;
    while(y){
        if(y&1)an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
void init(){
    const int n=6e5;
    er[0]=1;
    for(int i=1;i<=n;++i)er[i]=er[i-1]*2%mod;
    jc[0]=1;
    for(int i=1;i<=n;++i)jc[i]=jc[i-1]*i%mod;
    ny[n]=ksm(jc[n]);
    for(int i=n;i;--i)ny[i-1]=ny[i]*i%mod;
}
ll C(int x,int y){
    if(x<y||y<0)return 0;
    return jc[x]*ny[y]%mod*ny[x-y]%mod;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    init();
    for(int i=1;i<=n;++i){
        int x;
        cin>>x;t[x]++;
    }
    scn=n;
    while(m--){
        int op;
        ll x;
        cin>>op>>x;
        if(op==1)t[x]++,scn++;
        else if(op==2)t[x]--,scn--;
        else{
            ts[0]=t[0];
            for(int i=1;i<60;++i)ts[i]=ts[i-1]+t[i];
            ll ans=er[scn],bs=1;
            int cn=0;
            int ed=59;
            while(ed>=0){
                if(!(x&(1ll<<ed))){
                    --ed;
                    continue;
                }
                int ls=ed;
                while(ls>0&&(x&(1ll<<(ls-1))))--ls;
                int id=ed+cn;
                for(int i=ed;i>=ls;--i){
                    ll nbs=bs*C(t[id],ed-i)%mod;
                    if(id)nbs=nbs*er[ts[id-1]]%mod;
                    ans=(ans-nbs+mod)%mod;
                }
                bs=bs*C(t[id],ed-ls+1)%mod;
                cn+=ed-ls+1;
                ed=ls-1;
            }
            cout<<ans<<'\n';
        }
    }
    return 0;
}