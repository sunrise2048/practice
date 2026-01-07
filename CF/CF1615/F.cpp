#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e3+5;
const int mod=1e9+7;
int T;
int n;
char a[N],b[N];
int a1[N],b1[N];
int aw[N],bw[N];
ll jc[N],ny[N];
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
    const int n=2000;
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
    init();
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;++i){
            cin>>a[i];
            aw[i]=aw[i-1];
            a1[i]=a1[i-1];
            if(a[i]=='?'){
                aw[i]++;
            }
            else if((a[i]=='1')^(i&1)){
                a1[i]++;
            }
        }
        for(int i=1;i<=n;++i){
            cin>>b[i];
            bw[i]=bw[i-1];
            b1[i]=b1[i-1];
            if(b[i]=='?'){
                bw[i]++;
            }
            else if((b[i]=='1')^(i&1)){
                b1[i]++;
            }
        }
        ll ans=0;
        for(int i=1;i<=n;++i){
            if(a[i]!='?'&&((a[i]=='1')^(i&1))==0)continue;
            for(int j=1;j<=n;++j){
                if(b[j]!='?'&&((b[j]=='1')^(j&1))==0)continue;
                ll bs=C(aw[i-1]+bw[j-1],aw[i-1]+a1[i-1]-b1[j-1])*C(aw[n]+bw[n]-aw[i]-bw[j],aw[n]-aw[i]+a1[n]-a1[i]-(b1[n]-b1[j]))%mod;
                ans=(ans+bs*abs(i-j))%mod;
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}