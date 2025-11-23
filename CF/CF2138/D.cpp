#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5005;
const int mod=1e9+7;
int T;
int n,m,q;
int a[N];
pair<int,int> op[N];
ll jc[N],ny[N];
ll ksm(ll x,int y=mod-2){
    ll an=1;
    while (y) {
        if (y&1) an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
void init(){
    const int lm=5000;
    jc[0]=1;
    for (int i=1;i<=lm;++i) jc[i]=jc[i-1]*i%mod;
    ny[lm]=ksm(jc[lm]);
    for (int i=lm;i;--i) ny[i-1]=ny[i]*i%mod;
}
ll C(int x,int y){
    return jc[x]*ny[y]%mod*ny[x-y]%mod;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    init();
    cin>>T;
    while (T--) {
        cin>>n>>m>>q;
        for (int i=1;i<=n;++i) {
            cin>>a[i];
        }
        for (int i=1;i<=q;++i) {
            cin>>op[i].first>>op[i].second;
        }
        for (int i=1;i<=n;++i) {
            ll ans=0;
            vector<pair<int,int>> ve;
            int A=0,B=0,s=0;
            for (int j=1;j<=q;++j) {
                if (op[j].first==i) {
                    ve.emplace_back(op[j].second,1);
                    ++A;
                }
                else if(op[j].first<i) {
                    ve.emplace_back(op[j].second+i-op[j].first,2);
                    ++A;
                }
                else {
                    ve.emplace_back(op[j].second-(op[j].first-i),0);
                    ++s;
                }
            }
            sort(ve.begin(),ve.end());
            for (int j=0;j<ve.size();++j) {
                ll ds=ve[j].first;
                if (j) ds-=ve[j-1].first;
                if (!A) {
                    if (!B) {
                        if (!j||a[i]>=ve[j-1].first) ds=min(ve[j].first,a[i])-(j?ve[j-1].first:0);
                        else ds=0;
                        ans=(ans+ds*jc[q])%mod;
                    }
                }
                else {
                    ans=(ans+ds*C(A+B-1,B)%mod*jc[A]%mod*jc[B]%mod*C(A+B+s,s)%mod*jc[s])%mod;
                }
                if (ve[j].second==0) {
                    --s;++B;
                }
                else if (ve[j].second==1) {
                    --A;++B;
                }
                else {
                    --A;++s;
                }
            }
            if (B==0&&a[i]>ve.back().first) {
                ans=(ans+(a[i]-ve.back().first)*jc[q])%mod;
            }
            cout<<ans<<' ';
        }
        cout<<'\n';
    }
    return 0;
}