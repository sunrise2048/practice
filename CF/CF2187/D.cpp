#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
const int mod=998244353;
int T;
int n,x,y;
bitset<N> f0,f1;
char c[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>x>>y;
        f0.reset();
        f1.reset();
        f0[0]=1;
        for(int i=1;i<=n;++i){
            cin>>c[i];
            if(c[i]=='0'){
                f1<<=1;
            }
            else if(c[i]=='1'){
                swap(f1,f0);
                f1<<=1;
            }
            else{
                f0|=f1;
                f1=f0<<1;
            }
        }
        vector<ll> as;
        f0|=f1;
        for(int i=0;i<=n;++i){
            if(f0[i]){
                ll d=n-2*i;
                as.push_back(1ll*y*i+1ll*d*(d+1)/2*x);
            }
        }
        sort(as.begin(),as.end());
        as.erase(unique(as.begin(),as.end()),as.end());
        ll ans=0;
        for(ll vl:as){
            ans=(ans+vl)%mod;
        }
        cout<<ans<<'\n';
    }
    return 0;
}